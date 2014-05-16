CXX=clang++
CXXOPTS=-Wall -Wextra -Weverything --std=c++11 -Wno-c++98-compat -ggdb -pthread
PRG=toy

SOURCE = $(addprefix src/,	\
	 breeder.cc		\
	 cube.cc 		\
	 fitness.cc		\
	 format.cc 		\
	 main.cc 		\
	 output.cc 		\
	 scrambler.cc 		\
	 )
OBJ = $(patsubst %.cc, %.o, $(SOURCE))

$(PRG): $(OBJ)
	$(CXX) -o $@ $^ $(CXXOPTS)

run: $(PRG)
	./$(PRG)

clean: mostlyclean
	find . -name $(PRG) -delete

mostlyclean:
	find . -name *.o -delete

%.o: %.cc $(DEPS)
	$(CXX) -c -o $@ $< $(CXXOPTS) -I src

