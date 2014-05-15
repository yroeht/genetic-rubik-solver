CXX=clang++
CXXOPTS=-Wall -Wextra -Weverything --std=c++11 -Wno-c++98-compat -ggdb
PRG=toy

SOURCE = $(addprefix src/,	\
	 cube.cc 		\
	 format.cc 		\
	 main.cc 		\
	 output.cc 		\
	 scrambler.cc 		\
	 )
OBJ = $(patsubst %.cc, %.o, $(SOURCE))

$(PRG): $(OBJ)
	$(CXX) -o $@ $^ $(CXXOPTS)

clean: mostlyclean
	find . -name $(PRG) -delete

mostlyclean:
	find . -name *.o -delete

%.o: %.cc $(DEPS)
	$(CXX) -c -o $@ $< $(CXXOPTS) -I src

