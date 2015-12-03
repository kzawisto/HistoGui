ROOT_CONFIG = `../root/bin/root-config --cflags --glibs`
FLAGS = -std=c++11 -g -fPIC
IDIR = -Iinclude
	
SRC = $(wildcard src/*.cpp)
DEPS = $(wildcard include/*.h)
OBJ = $(patsubst src/%.cpp, obj/%.o, ${SRC})

lib/libdataio.so : ${OBJ} ${DEPS}
	g++ --shared -o $@ $^ ${ROOT_CONFIG} ${FLAGS}
	$(shell cp lib/libdataio ../HistogramGui/)
obj/%.o : src/%.cpp
	g++ -o $@ -c $^ ${FLAGS} ${IDIR} ${ROOT_CONFIG}
	
ParseTree: ParseTree.cpp HistoConfig.o
	g++ -o $@ $^ -Wl,--no-as-needed  ${ROOT_CONFIG} -lboost_program_options
	
%.o : %.cpp
	g++ -o $@ -c $^
	
.PHONY: 
	clean
clean :
	rm -f obj/*
	rm -f lib/*