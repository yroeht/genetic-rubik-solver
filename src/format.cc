#include <format.hh>

#include <ostream>

namespace Format
{
  std::ostream& operator<<(std::ostream& os, const Code color)
    {
      return os << "\033[38;5;" << static_cast<int>(color) << "m";
    }
}
