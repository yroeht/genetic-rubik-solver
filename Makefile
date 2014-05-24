CXX=clang++
CXXOPTS=-Wall -Wextra -Weverything -Wno-c++98-compat 	\
	--std=c++11 					\
	-pthread -O2
PRG=toy
CPUS?=0

SOURCE = $(addprefix src/,	\
	 cube.cc 		\
	 fitness.cc		\
	 format.cc 		\
	 main.cc 		\
	 output.cc 		\
	 scrambler.cc 		\
	 )
OBJ = $(patsubst %.cc, %.o, $(SOURCE))

all: $(PRG)

$(PRG): $(OBJ)
	$(CXX) -o $@ $^ $(CXXOPTS)

run: $(PRG)
	./$(PRG)

clean: mostlyclean
	find . -name $(PRG) -delete

mostlyclean:
	find . -name *.o -delete

%.o: %.cc $(DEPS)
	$(CXX) -c -o $@ $< $(CXXOPTS) -I src -DCPUS=$(CPUS)

