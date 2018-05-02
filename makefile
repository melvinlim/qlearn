CXX =				g++
CXXFLAGS =	-std=c++11 -Wall -Wextra -pedantic -g -c
LFLAGS =		-std=c++11 -Wall -Wextra -pedantic -g -o qlearn
OBJECTS =		main.o game.o player.o map.o object.o qfunction.o
qlearn:		$(OBJECTS)
	$(CXX) $(LFLAGS) $(OBJECTS)
main:				main.cpp defs.h
	$(CXX) $(CXXFLAGS) main.cpp
game:				game.cpp defs.h
	$(CXX) $(CXXFLAGS) game.cpp
player:			player.cpp defs.h
	$(CXX) $(CXXFLAGS) player.cpp
map:				map.cpp defs.h
	$(CXX) $(CXXFLAGS) map.cpp
object:			object.cpp defs.h
	$(CXX) $(CXXFLAGS) object.cpp
qfunction:	qfunction.cpp defs.h
	$(CXX) $(CXXFLAGS) qfunction.cpp
clean:
	rm -f mynn *.o a.out
