OUTPUT=bin/exe
IDIR=-Iinclude -Iinclude/math -Iinclude/rasterizer -Iinclude/scene -Iinclude/renderer
CXXFLAGS= -g -O0 -Wall -Werror -Wno-unknown-pragmas $(IDIR)
VFLAG=--leak-check=full --show-leak-kinds=all
#LIBSGL=-lGL -lGLU -ldl
LIBSDL2=-lSDL2 -lSDL2_image -lSDL2_ttf
LDLIBS=$(LIBSDL2) #$(LIBSGL)
SRCS=$(wildcard src/*.cpp)
OBJS=$(SRCS:.cpp=.o)

all: $(OUTPUT)

multi :
	make -j all

-include $(OBJS:.o=.d)

%.o: %.cpp
	g++ -c $(CXXFLAGS) $< -o $@
%.o: %.c
	gcc -c $(CXXFLAGS) $< -o $@

$(OUTPUT): $(OBJS)
	g++ $(LDLIBS) $^ -o $@

run : $(OUTPUT)
	./$(OUTPUT)

leak : 
	valgrind $(OUTPUT)

leakFull : 
	valgrind $(VFLAG) $(OUTPUT)

cleanAll:
	rm -rf $(OBJS) $(OBJS:.o=.d) $(OUTPUT)

clean :
	rm -rf $(OBJS) $(OBJS:.o=.d)

re : clean all

med : 
	find ./media -name "*" > ./media.txt
	g++ -Wall -Werror mediaCreator.cpp -o mediaCreator && ./mediaCreator
	rm ./media.txt && rm ./mediaCreator
