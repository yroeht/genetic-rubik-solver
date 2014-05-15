#ifndef SCRAMBLER_HH
# define SCRAMBLER_HH

# include <cube.hh>

class Scrambler
{
public:
  static Sequence scramble(unsigned length);
  static Sequence reduce(const Sequence s);
};

#endif /* SCRAMBLER_HH */
