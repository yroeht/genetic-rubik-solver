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
  std::vector<Move> p {
      ROT_UP, ROT_UP_I,
      ROT_DOWN, ROT_DOWN_I,
      ROT_FRONT, ROT_FRONT_I,
      ROT_RIGHT, ROT_RIGHT_I,
      ROT_LEFT, ROT_LEFT_I
  };

  long seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine e (seed);
  std::uniform_int_distribution<> d(0, static_cast<int>(p.size()) - 1);
  std::function<unsigned()> rnd = std::bind(d, e);

  Sequence s;
  Move r = ROT_UP;
  while (s.size() < length)
    {
      /* Forbid repeating or canceling the previous move. This implies the
      ** generated sequences will always be in a canonical form, and calling
      ** Scrambler::reduce should be useless. */
      Move forbidden = ROT_UP;
      do {
          r = p[rnd()];
      } while (r == forbidden || r == invert(forbidden));
      forbidden = r;
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
