#ifndef BREEDER_HH
# define BREEDER_HH

# include <cube.hh>
# include <types.hh>

# include <functional>
# include <mutex>
# include <ostream>
# include <random>
# include <thread>

typedef std::pair<Sequence, Sequence> Children;

class Breeder
{
public:
  Breeder(const unsigned count_, const unsigned length_, const Cube& cu);
  ~Breeder() __attribute__ ((noreturn));

  void initial_populate();
  void score();
  void evolve();

  Score average() const;
  Sequence best_move() const;
  void stop_workers();

private:
  Individual generate_individual();
  Children cross_chromosomes(const Sequence first_parent,
                             const Sequence second_parent,
                             unsigned crossing_point);
  void cross();
  void mutate();
  void spawn();
  void start_workers();

private:
  /* The chromosomes. */
  Population population;
  /* The size of a chromosome. */
  const unsigned length;

  int dummy : 32;

  long to_breed;
  long to_mutate;
  long to_spawn;

  std::uniform_int_distribution<> parents;
  std::uniform_int_distribution<> loci;
  std::function<size_t()> random_parent;
  std::function<unsigned()> crossing_point;

  long seed;
  std::default_random_engine e;

  std::vector<std::thread> workers;
  std::mutex mtx_work_todo;
  std::mutex mtx_population;

  const Cube& scramble;
  int work_todo;

public:
  unsigned iteration;

public:
  void dump(std::ostream& os);
};

#endif /* BREEDER_HH */
