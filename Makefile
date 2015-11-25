SOURCES=myShell.cpp split.cpp find.cpp dir.cpp
OBJS=$(patsubst %.cpp, %.o, $(SOURCES))
CPPFLAGS=-ggdb3 -Wall -pedantic -std=gnu++98

compress: $(OBJS)
	g++ $(CPPFLAGS) -o myShell $(OBJS)
%.o: %.cpp split.h find.h dir.h
	g++ $(CPPFLAGS) -c $<

clean:
	rm compress *~ *.o


