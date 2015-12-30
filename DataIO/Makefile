ROOT_CONFIG = `root-config --cflags --glibs`
FLAGS = -std=c++11 -fPIC
IDIR = -Iinclude
	
SRC = $(wildcard src/*.cpp)
DEPS = $(wildcard include/*.h)
OBJ = $(patsubst src/%.cpp, obj/%.o, ${SRC})

lib/libdataio.so : ${OBJ} ${DEPS}
	g++ --shared -o $@ $^ ${FLAGS}
	
obj/%.o : src/%.cpp
	g++ -o $@ -c $^ ${FLAGS} ${IDIR}
	
ParseTree: ParseTree.cpp
	g++ -o $@ $^ -Wl,--no-as-needed -I./include -L./lib  ${ROOT_CONFIG} -ldataio -lboost_program_options
	
%.o : %.cpp
	g++ -o $@ -c $^
	
.PHONY: 
	clean
clean :
	rm -f obj/*
	rm -f lib/*
