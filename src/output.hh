#ifndef OUTPUT_HH
# define OUTPUT_HH

# include <cube.hh>
# include <types.hh>

# include <ostream>
# include <string>

std::ostream& operator<<(std::ostream& os, const Color c);
std::ostream& operator<<(std::ostream& os, const Face f);
std::ostream& operator<<(std::ostream& os, const Move m);
std::ostream& operator<<(std::ostream& os, const Sequence s);

#endif /* OUTPUT_HH */
