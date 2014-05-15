#ifndef TYPES_HH
# define TYPES_HH

# include <list>
# include <vector>

enum Color
{
  CUB_WHITE,    CUB_YELLOW,
  CUB_BLUE,     CUB_GREEN,
  CUB_RED,      CUB_ORANGE
};

enum Side
{
  TOP,      BOTTOM,
  LEFT,     RIGHT,
  FRONT,    BACK
};

enum Move
{
  ROT_UP,       ROT_UP_I,
  ROT_DOWN,     ROT_DOWN_I,
  ROT_LEFT,     ROT_LEFT_I,
  ROT_RIGHT,    ROT_RIGHT_I,
  ROT_FRONT,    ROT_FRONT_I,
  ROT_BACK,     ROT_BACK_I
};

typedef std::vector<std::vector<Color>> Face;

typedef std::list<Move> Sequence;

typedef unsigned Score;

#endif /* TYPES_HH */
