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
      std::cout << Format::CLEAR;
      Cube c;

      /* Scramble */
        {
          auto scramble = Scrambler::scramble(scramble_length);
          scramble = Scrambler::reduce(scramble);
          std::cout << std::endl << "Scramble: " << scramble;
          std::cout << std::endl;

          c.rotate(scramble);

          std::cout << "** Applying scramble **" << std::endl
            << c << std::endl
            << "Fitness: " << Fitness::evaluate(*new Sequence, c)
            << std::endl << std::endl;
        }

      /* Solve */
      Sequence best_move;
        {
          double duration;
          auto generator = [&]() -> Sequence
            { return Scrambler::scramble(solution_length); };

          auto scorer = [c](const Sequence s) -> unsigned
            { static Cube cc (c); return Fitness::evaluate(s, cc); };

          PrintableBreeder<Sequence, unsigned> b(generator, scorer,
                                                 200000, 1.0);

          std::clock_t start = std::clock();
          best_move = b.pick(300, 48, std::cout);
          duration = (std::clock() - start ) / (double) CLOCKS_PER_SEC;

          std::cout << "best move: " << best_move << std::endl;
          std::cout << "operation length: " << duration << std::endl;
        }

      /* Show */
        {
          auto bak(c);
          c.rotate(best_move);
          std::cout << "** Applying best sequence **" << std::endl
            << c << std::endl
            << "Fitness: " << Fitness::evaluate(*new Sequence, c) << std::endl
            << std::endl << std::endl;
        }
  } while (false);
}

