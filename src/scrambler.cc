#include <scrambler.hh>

#include <algorithm>
#include <chrono>
#include <functional>
#include <random>

Move
Scrambler::invert(Move m)
{
  /* Even rotation values are direct (e.g. U). */
  auto i = static_cast<int>(m);
  if (i % 2 == 0)
    /* Direct rotation, return an inverse one (e.g. Ui). */
    return static_cast<Move>(i + 1);
  else
    /* Inverse rotation, return a direct one (e.g. U). */
    return static_cast<Move>(i - 1);
}

Sequence
Scrambler::scramble(unsigned length)
{
  std::vector<Move> p;
  p.push_back(ROT_UP);
  p.push_back(ROT_UP_I);
  p.push_back(ROT_FRONT);
  p.push_back(ROT_FRONT_I);
  p.push_back(ROT_RIGHT);
  p.push_back(ROT_RIGHT_I);

  long seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine e (seed);
  std::uniform_int_distribution<> d(0, static_cast<int>(p.size()) - 1);
  std::function<unsigned()> rnd = std::bind(d, e);

  Sequence s;
  Move r = ROT_UP;
  Move forb1 = ROT_UP, forb2 = ROT_UP;
  while (s.size() < length)
    {
      do {
          r = p[rnd()];
      } while (r == forb1 || r == forb2);
      if (r == ROT_UP || r == ROT_UP_I)
        {
          forb1 = ROT_UP;
          forb2 = ROT_UP_I;
        }
      else if (r == ROT_FRONT || r == ROT_FRONT_I)
        {
          forb1 = ROT_FRONT;
          forb2 = ROT_FRONT_I;
        }
      else // if (r == ROT_RIGHT)
        {
          forb1 = ROT_RIGHT;
          forb2 = ROT_RIGHT_I;
        }
      s.push_back(r);
    }
  return s;
}

Sequence
Scrambler::reduce(const Sequence s)
{
  Sequence ret;

  for (auto rotation : s)
    {
      /* There is nothing to reduce the first rotation with, yet. */
      if (ret.empty())
        ret.push_back(rotation);
      else
        {
          auto last = ret.back();
          if (static_cast<int>(last) == static_cast<int>(invert(rotation)))
            /* The previous rotation is cancelled by the current one, so cancel
            ** that previous one and go on. */
            ret.pop_back();
          else if (ret.size() > 1
                   && rotation == *std::prev(ret.end(), 1)
                   && rotation == *std::prev(ret.end(), 2))
            /* The current rotation is the third of its kind. A single inverse
            ** one would be better. */
            {
              ret.pop_back();
              ret.pop_back();
              ret.push_back(invert(rotation));
            }
          else
            /* The current rotation does not cancel the previous rotation. So
            ** keep it. */
            ret.push_back(rotation);
        }
    }
  return ret;
}
