#include <cube.hh>
#include <format.hh>
#include <output.hh>
#include <scrambler.hh>

#include <iostream>
#include <chrono>
#include <thread>

int main()
{
  Cube c;
  do {
      std::cout << Format::CLEAR;

      unsigned scramble_length = 20;

      std::cout << "** Generating "
        << scramble_length
        << " scrambling moves at random. **"
        << std::endl;

      auto s = Scrambler::scramble(scramble_length);
      std::cout << std::endl
        << "Scramble (2-GEN): " << s;
      s = Scrambler::reduce(s);
      std::cout << std::endl
        << "Scramble (2-GEN - reduced): " << s
        << std::endl
        << std::endl
        << std::endl;

      c.rotate(s);

      std::cout << "** Applying scramble **"
        << std::endl
        << std::endl
        << std::endl
        << c
        << std::endl;

#if 0
      std::chrono::milliseconds duration (500);
      std::this_thread::sleep_for(duration);
  } while (true);
#else
  } while (std::cin.ignore());
#endif
}

