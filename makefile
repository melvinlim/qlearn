CXX =				g++
CXXFLAGS =	-O3 -std=c++11 -Wall -Wextra -pedantic -g -c
LFLAGS =		-O3 -std=c++11 -Wall -Wextra -pedantic -g -o qlearn
OBJECTS =		main.o game.o player.o map.o object.o qfunction.o
OTHEROBJECTS =		mynn/layer.o mynn/net.o mynn/data.o mynn/idx.o mynn/mnist.o mynn/xor.o
qlearn:		$(OBJECTS) $(OTHEROBJECTS)
	cd mynn;make
	$(CXX) $(LFLAGS) $(OBJECTS) $(OTHEROBJECTS)
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
	rm -f qlearn *.o a.out mynn/mynn mynn/*.o mynn/a.out
