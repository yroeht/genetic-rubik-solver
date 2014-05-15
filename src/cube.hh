#ifndef CUBE_HH
# define CUBE_HH

# include <types.hh>

# include <ostream>
# include <string>

class Cube;
namespace Format
{
  std::string CubePrinter3D(const Cube c);
}

class Cube
{
private:
  Face top, bottom;
  Face left, right;
  Face front, back;

public:
  Cube();

public:
  void rotate(Move m);
  void rotate(Sequence s);

public:
  void show_face(std::ostream& os, Side s);
  friend std::ostream& operator<<(std::ostream& os, const Cube c);
  friend std::string Format::CubePrinter3D(const Cube c);
};

#endif /* CUBE_HH */
