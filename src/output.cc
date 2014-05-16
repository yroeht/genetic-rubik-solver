#include <ascii.hh>
#include <breeder.hh>
#include <format.hh>
#include <output.hh>
#include <scrambler.hh>

#include <algorithm>
#include <iterator>
#include <string>
#include <sstream>

std::string Format::CubePrinter3D(const Cube c)
{
  std::string cube3D (Ascii::cube3D);
#define X(letter, face, i, j) do {                      \
    std::stringstream ss;                               \
    ss << c.face[i][j];                                 \
    cube3D.replace(cube3D.find(#letter), 1, ss.str());  \
} while (0);
# include <3D.xm>
#undef X
  return cube3D;
}

std::ostream& operator<<(std::ostream& os, const Color c)
{
  switch(c)
    {
    case CUB_WHITE:     os << Format::WHITE         << "W"; break;
    case CUB_YELLOW:    os << Format::YELLOW        << "Y"; break;
    case CUB_BLUE:      os << Format::BLUE          << "B"; break;
    case CUB_GREEN:     os << Format::GREEN         << "G"; break;
    case CUB_RED:       os << Format::RED           << "R"; break;
    case CUB_ORANGE:    os << Format::ORANGE        << "O"; break;
    }
  os << Format::DEFAULT;
  return os;
}

std::ostream& operator<<(std::ostream& os, const Face f)
{
  for (const auto& v : f)
    {
      for (const auto c : v)
        os << c << " ";
      os << std::endl;
    }
  return os;
}

std::ostream& operator<<(std::ostream& os, const Cube cu)
{
#if 1
  os << Format::CubePrinter3D(cu);
#else // Noobish display
  os << "Top face:"     << std::endl << cu.top      << std::endl;
  os << "Bottom face:"  << std::endl << cu.bottom   << std::endl;
  os << "Left face:"    << std::endl << cu.left     << std::endl;
  os << "Right face:"   << std::endl << cu.right    << std::endl;
  os << "Front face:"   << std::endl << cu.front    << std::endl;
  os << "Back face:"    << std::endl << cu.back     << std::endl;
#endif
  return os;
}

std::ostream& operator<<(std::ostream& os, const Sequence s)
{
  std::copy(s.begin(), s.end(),
            std::ostream_iterator<Move>(os, ""));
  return os;
}

std::ostream& operator<<(std::ostream& os, const Move m)
{
  switch (m)
    {
    case ROT_UP:        os << "U"; break;
    case ROT_DOWN:      os << "D"; break;
    case ROT_LEFT:      os << "L"; break;
    case ROT_RIGHT:     os << "R"; break;
    case ROT_FRONT:     os << "F"; break;
    case ROT_BACK:      os << "B"; break;
    case ROT_UP_I:      os << "Ui"; break;
    case ROT_DOWN_I:    os << "Di"; break;
    case ROT_LEFT_I:    os << "Li"; break;
    case ROT_RIGHT_I:   os << "Ri"; break;
    case ROT_FRONT_I:   os << "Fi"; break;
    case ROT_BACK_I:    os << "Bi"; break;
    }
  return os;
}

void Breeder::dump(std::ostream& os)
{
  auto first = population.front();
  os << "Breeder iteration " << iteration
    << ", population count " << population.size()
    << ", average fitness " << average() * 100 / 48 << "%"
    << "."
    << std::endl;
  os << "Fittest individual is " << Scrambler::reduce(first.first)
    << ", scored " << first.second * 100 / 48 << "%"
    << std::endl;
}
