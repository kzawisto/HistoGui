IDIR = -Iinclude -I../DataIO/include `wx-config --cppflags`
ROOT_LIBS = `../root/bin/root-config --glibs`
SRC = $(wildcard src/*.cpp)
LINKER = `wx-config --libs` -L../DataIO/lib -ldataio -lboost_program_options
FLAGS = -std=c++11 -g
OBJ = $(patsubst src/%.cpp, obj/%.o, ${SRC})

myApp : ${OBJ}
	g++ -o $@ $^ -Wl,--no-as-needed ${LINKER} ${ROOT_LIBS}
	@echo ${__SRC}

obj/%.o : src/%.cpp
	g++ -o $@ -c $^  ${FLAGS} ${IDIR}

.PHONY: 
	clean
clean :
	rm -f obj/*.o