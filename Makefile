CC = g++ -std=c++11
FLAGS = -g -Wall
IPATH = -Isrc
DEPENDS =
SRCS = 

ifdef MAKECMDGOALS
	SRCS = $(MAKECMDGOALS).cpp
	DEPENDS = $(MAKECMDGOALS).d
	MAKECMDGOALS = src/$(MAKECMDGOALS).o
else
	SRCS = *.cpp src/*.cpp
	DEPENDS = $(SRCS:.cpp=.d)
endif

Zork:main.cpp
	$(CC) $(IPATH) $(FLAGS) -o Zork $(SRCS)

src/%.o:src/%.cpp
	$(CC) $(IPATH) $(FLAGS) -o $@ -c $<

src/%.d:src/%.cpp
	rm -f $@
	$(CC) $(IPATH) -MM $<  > $@

Zork_Def.o:src/Zork_Def.cpp 
	$(CC) $(FLAGS) $(IPATH) -o Zork_Def.o $< 

-include $(DEPENDS)


.PHONY:clean

clean:
	rm *.o *.d
