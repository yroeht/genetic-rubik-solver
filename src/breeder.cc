#include <breeder.hh>
#include <fitness.hh>
#include <output.hh>
#include <scrambler.hh>

#include <algorithm>
#include <chrono>
#include <functional>
#include <iterator>

#include <cassert>

Breeder::Breeder(const unsigned count_, const unsigned length_, const Cube& cu)
: population(count_)
, length(length_)
, seed(std::chrono::system_clock::now().time_since_epoch().count())
, e(seed)
, scramble(cu)
, work_todo(-1)
  , iteration(0)
{
  /* evolution */
  to_breed = population.size() / 4;
  to_spawn = population.size() / 10;
  to_mutate = population.size() / 10;

  parents = std::uniform_int_distribution<>(0, static_cast<int>(to_breed) / 2);
  loci = std::uniform_int_distribution<>(0, static_cast<int>(length));

  random_parent = std::bind(parents, e);
  crossing_point = std::bind(loci, e);
}

Breeder::~Breeder()
{
  assert(false);
}

void
Breeder::stop_workers()
{
    {
      std::unique_lock<std::mutex> lck (mtx_work_todo);
      work_todo = -2;
    }
  std::this_thread::sleep_for (std::chrono::milliseconds(100));
  for (auto &t : workers)
    if (t.joinable())
      t.join();
}

void
Breeder::start_workers()
{
  workers.resize(4);
  auto thread_func = [&,this] () -> void
    {
      while (true)
        {
          unsigned idx = 0;
            {
              std::unique_lock<std::mutex> lck (mtx_work_todo);
              if (-1 == work_todo)
                {
                  if (-2 == work_todo)
                    break;
                  else
                    continue;
                }
              idx = static_cast<unsigned>(work_todo--);
            }
          Individual* i;
            {
              std::unique_lock<std::mutex> lck (mtx_population);
              i = &this->population[idx];
            }
          auto tmp = Fitness::evaluate(i->first, scramble);
            {
              std::unique_lock<std::mutex> lck (mtx_population);
              i->second = tmp;
            }
        }
    };

  std::generate(workers.begin(),
                workers.end(),
                [&](){ return std::thread(thread_func); });
}

Individual
Breeder::generate_individual()
{
  Sequence s;
  do {
      Sequence ss = Scrambler::scramble(this->length);
      s = Scrambler::reduce(ss);
  } while (s.size() < length);
  return Individual(s, 0);
}

void
Breeder::initial_populate()
{
  std::generate(population.begin(), population.end(),
                [this]() { return generate_individual(); });
}

void
Breeder::score()
{
#if 1 // Threaded.
  static bool workers_started = false;
  if (not workers_started)
    {
      start_workers();
      workers_started = true;
    }
  /* Give some work to the workers. */
    {
      std::unique_lock<std::mutex> lck1 (mtx_work_todo);
      std::unique_lock<std::mutex> lck2 (mtx_population);
      work_todo = static_cast<int>(population.size() - 1);
    }

  for (;;)
    {
        {
          std::unique_lock<std::mutex> lck (mtx_work_todo);
          if (-1 == work_todo)
            break;
        }
    }

#else // Monothreaded.
  std::for_each(population.begin(), population.end(), [&cu](Individual& i)
                { i.second = Fitness::evaluate(i.first, cu); });
#endif

  /* Fixme: the last task is still running. */
  std::this_thread::sleep_for (std::chrono::milliseconds(10));

  std::random_shuffle(population.begin(), population.end());
  std::sort(population.begin(), population.end(),
            [](const Individual& lhs,
               const Individual& rhs) { return lhs.second > rhs.second; });

}

Score
Breeder::average() const
{
  Score ret = 0;
  for (auto i : population)
    ret += i.second;
  return ret / population.size();
}

Sequence
Breeder::best_move() const
{
  return population.front().first;
}

Children
Breeder::cross_chromosomes(const Sequence first_parent_,
                           const Sequence second_parent_,
                           unsigned crossing_point_)
{
  Sequence first_parent(first_parent_);
  Sequence second_parent(second_parent_);
  Sequence first_child, second_child;

  first_child.splice(first_child.end(),
                     first_parent,
                     first_parent.begin(),
                     std::next(first_parent.begin(), crossing_point_));

  second_child.splice(second_child.end(),
                     second_parent,
                     second_parent.begin(),
                     std::next(second_parent.begin(), crossing_point_));

  first_child.splice(first_child.end(),
                     first_parent,
                     first_parent.begin(),
                     first_parent.end());

  second_child.splice(second_child.end(),
                     second_parent,
                     second_parent.begin(),
                     second_parent.end());

  return Children(first_child, second_child);
}

void
Breeder::cross()
{
  for (unsigned i = 0; i < to_breed; ++i)
    {
      auto first_parent = random_parent();
      auto second_parent = random_parent();
      Children children = cross_chromosomes(population[first_parent].first,
                                            population[second_parent].first,
                                            crossing_point());
      if (i % 4 == 0)
        {
          auto tmp = children.first.back();
          children.first.back() = Scrambler::invert(tmp);
        }
      population[first_parent] = Individual(children.first, 0);
      population[second_parent] = Individual(children.second, 0);
    }
}

void
Breeder::spawn()
{
  std::generate(std::prev(population.end(), to_spawn),
                population.end(),
                [&]() { return generate_individual(); });
}

void
Breeder::evolve()
{
  /* Cross existing fit parents. */
  cross();
  /* Replace the least fit inidividuals. */
  spawn();
  ++iteration;
}

