#include <breeder.hh>
#include <cube.hh>
#include <fitness.hh>
#include <format.hh>
#include <output.hh>
#include <scrambler.hh>

#include <iostream>
#include <chrono>
#include <thread>

int main()
{
  unsigned scramble_length = 10;
  unsigned solution_length = 10;
  do {
      //std::cout << Format::CLEAR;
      Cube c;
      Breeder b(1000, solution_length, c);
      auto s = Scrambler::scramble(scramble_length);

      /* Scramble */
        {
          std::cout << std::endl
            << "Scramble (2-GEN): " << s;
          s = Scrambler::reduce(s);
          std::cout << std::endl;

          c.rotate(s);

          std::cout << "** Applying scramble **"
            << std::endl
            << c
            << std::endl
            << "Fitness: " << Fitness::evaluate(*new Sequence, c)
            << std::endl
            << std::endl;
        }

      b.initial_populate();
      b.score();

      unsigned fit = 0;
      do
        {
          double duration;

          b.evolve();
          /* Scoring */
            {
              std::clock_t start = std::clock();
              b.score();
              duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
            }

          Cube c2(c);
          c2.rotate(b.best_move());

          if (b.iteration % 10 == 0 || fit == 48)
            {
             // std::cout << Format::CLEAR;
              std::cout << std::endl
                << "Scramble (2-GEN): " << s
                << std::endl
                << "Fitness: " << Fitness::evaluate(*new Sequence, c) * 100 / 48 << "%"
                << std::endl
                << c
                << std::endl;

              fit = Fitness::evaluate(b.best_move(), c);

              b.dump(std::cout);
              std::cout
                << "Scoring duration: " << duration
                << std::endl
                << "Applying best solution results in:" << std::endl
                << c2;
            }
        } while (fit < 48);
      b.stop_workers();
  } while (std::cin.ignore());
}

