#include <scrambler.hh>

#include <algorithm>
#include <cassert>
#include <chrono>
#include <functional>
#include <random>

Sequence
Scrambler::scramble(unsigned length)
{
  Sequence* ret = new Sequence(length);
  long seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine e (seed);
  std::uniform_int_distribution<> d(0, 12);
  std::function<int()> rnd = std::bind(d, e);

  std::generate(ret->begin(), ret->end(),
#if 0 // Uses all moves
                [rnd]() -> Move { return static_cast<Move>(rnd()); });
#else // Uses only U, Ui, R, and Ri, which are implemented.
                [rnd]() -> Move {
                    auto r = rnd();
                    while (r != static_cast<int>(ROT_UP)
                           && r != static_cast<int>(ROT_UP_I)
                           && r != static_cast<int>(ROT_RIGHT)
                           && r != static_cast<int>(ROT_RIGHT_I)
                           && r != static_cast<int>(ROT_FRONT)
                           && r != static_cast<int>(ROT_FRONT_I))
                      r = rnd();
                    return static_cast<Move>(r);
                });
#endif
  return *ret;
}

Sequence
Scrambler::reduce(const Sequence s)
{
  Sequence ret;
  assert(!s.empty());

  for (auto rotation : s)
    {
      /* There is nothing to reduce the first rotation with, yet. */
      if (ret.empty())
        ret.push_back(rotation);
      else
        {
          auto last = ret.back();
          if ((static_cast<int>(last) % 2 == 0
               && static_cast<int>(rotation) == static_cast<int>(last) + 1)
              || (static_cast<int>(last) % 2 == 1
                  && static_cast<int>(rotation) == static_cast<int>(last) - 1))
            /* The previous rotation is cancelled by the current one, so cancel
            ** that previous one and go on. */
            ret.pop_back();
          else if (ret.size() > 1
                   && last == *std::prev(ret.end(), 1)
                   && last == *std::prev(ret.end(), 2))
            /* The current rotation is the third of its kind. A single inverse
            ** one would be better. */
            {
              ret.pop_back();
              ret.pop_back();
              if (static_cast<int>(last) % 2 == 0)
                ret.push_back(static_cast<Move>(last + 1));
              else
                ret.push_back(static_cast<Move>(last - 1));
            }
          else
            /* The current rotation does not cancel the previous rotation. So
            ** keep it. */
            ret.push_back(rotation);
        }
    }
  return ret;
}
