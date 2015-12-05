CC = g++ -std=c++11
FLAGS = -g -Wall -Wno-reorder
IPATH = 
DEPEND =
SRCS = 

#ifdef MAKECMDGOALS
	SRCS = $(MAKECMDGOALS).cpp
	MAKECMDGOALS := $(MAKECMDGOALS).o 
	DEPEND = $(MAKECMDGOALS:.o=.d)

#else
#	SRCS = *.cpp src/*.cpp
#	DEPEND = $(SRCS:.cpp=.d)
#endif


Zork:main.cpp
	$(CC) $(IPATH) $(FLAGS) -o Zork $(SRCS)

%.o:
	$(CC) $(IPATH) $(FLAGS) -c $< -o $@

%.d:%.cpp
	@set -e;\
	rm -f $@;\
	$(CC) $(IPATH) $(FLAGS) -MM  $< > $@.$$$$;\
	sed 's,\($*\)\.o[ :]*,\1.o $@ :,g' < $@.$$$$ >$@;\
	rm -f $@.$$$$;



include $(DEPEND)


.PHONY:clean

clean:
	rm *.o *.d
