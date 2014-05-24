#include <fitness.hh>

/* The fitness of a sequence of moves is the number of solved pairs on the cube
** after application of said sequence. */
Score
Fitness::evaluate(const Sequence seq, const Cube& c)
{
  Cube cu(c);
  cu.rotate(seq);
  Score sc = 0;

/* Corner-edge pairing */
#define X(ff, sf, fi, fj, si, sj, fii, fjj, sii, sjj)   \
  do {                                                  \
      if (cu.ff[fi][fj] == cu.ff[fii][fjj]              \
          && cu.sf[si][sj] == cu.sf[sii][sjj])          \
      ++sc;                                             \
  } while (0);

/* Center matching */
#define Y(f)                        \
  do {                              \
    if (cu.f[1][1] == cu.f[0][1])   \
      ++sc;                         \
    if (cu.f[1][1] == cu.f[1][2])   \
      ++sc;                         \
    if (cu.f[1][1] == cu.f[2][1])   \
      ++sc;                         \
    if (cu.f[1][1] == cu.f[1][0])   \
      ++sc;                         \
  } while (0);
# include <pairs.xm>
#undef X
#undef Y

  return sc;
}
