//#define X(ff, sf, fi, fj, si, sj, fii, fjj, sii, sjj)

/* Define full left and right sides, then define the four remaining
 * top-front-bottom-back pairs. */

/* *************** */
/* Left side pairs */
/* *************** */

/* Top pairs */
X(top, left, 1, 0, 0, 1, 0, 0, 0, 0)
X(top, left, 1, 0, 0, 1, 2, 0, 0, 2)

/* Front pairs */
X(front, left, 1, 0, 1, 2, 0, 0, 0, 2)
X(front, left, 1, 0, 1, 2, 2, 0, 2, 2)

/* Bottom pairs */
X(bottom, left, 1, 0, 2, 1, 2, 0, 2, 0)
X(bottom, left, 1, 0, 2, 1, 0, 0, 2, 2)

/* Back pairs */
X(back, left, 1, 0, 1, 0, 2, 2, 0, 0)
X(back, left, 1, 0, 1, 0, 0, 0, 2, 0)

/* **************** */
/* Right side pairs */
/* **************** */

/* Top pairs */
X(top, right, 1, 2, 0, 1, 2, 2, 0, 0)
X(top, right, 1, 2, 0, 1, 0, 2, 0, 2)

/* Front pairs */
X(front, right, 1, 2, 1, 0, 0, 2, 0, 0)
X(front, right, 1, 2, 1, 0, 2, 2, 2, 0)

/* Bottom pairs */
X(bottom, right, 1, 2, 2, 1, 0, 2, 2, 0)
X(bottom, right, 1, 2, 2, 1, 2, 2, 2, 2)

/* Back pairs */
X(back, right, 1, 2, 1, 2, 2, 2, 0, 2)
X(back, right, 1, 2, 1, 2, 0, 2, 2, 2)

/* **************** */
/* Top front pairs */
/* **************** */

X(front, top, 0, 1, 2, 1, 0, 0, 2, 0)
X(front, top, 0, 1, 2, 1, 0, 2, 2, 2)

/* ****************** */
/* Front bottom pairs */
/* ****************** */

X(bottom, front, 0, 1, 2, 1, 0, 0, 2, 0)
X(bottom, front, 0, 1, 2, 1, 0, 2, 2, 2)

/* ***************** */
/* Bottom back pairs */
/* ***************** */

X(back, bottom, 0, 1, 2, 1, 0, 0, 2, 0)
X(back, bottom, 0, 1, 2, 1, 0, 2, 2, 2)

/* ************** */
/* Back top pairs */
/* ************** */

X(top, back, 0, 1, 2, 1, 0, 0, 2, 0)
X(top, back, 0, 1, 2, 1, 0, 2, 2, 2)

/* *************** */
/* Center matching */
/* *************** */
Y(left)
Y(right)
Y(top)
Y(front)
Y(bottom)
Y(back)

