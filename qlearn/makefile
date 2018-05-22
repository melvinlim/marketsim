CXX =						g++
CXXFLAGS =			-O3 -std=c++11 -Wall -Wextra -pedantic -g -c
LFLAGS =				-O3 -std=c++11 -Wall -Wextra -pedantic -g -o qlearn
OBJECTS =				main.o gamecontroller.o player.o world.o object.o qfunction.o
OTHEROBJECTS =	mynn/layer.o mynn/net.o mynn/idx.o
qlearn:		$(OBJECTS) $(OTHEROBJECTS)
	$(CXX) $(LFLAGS) $(OBJECTS) $(OTHEROBJECTS)
main:						main.cpp defs.h
	$(CXX) $(CXXFLAGS) main.cpp
gamecontroller:	gamecontroller.cpp defs.h
	$(CXX) $(CXXFLAGS) gamecontroller.cpp
player:					player.cpp defs.h
	$(CXX) $(CXXFLAGS) player.cpp
world:					world.cpp defs.h
	$(CXX) $(CXXFLAGS) world.cpp
object:					object.cpp defs.h
	$(CXX) $(CXXFLAGS) object.cpp
qfunction:			qfunction.cpp defs.h
	$(CXX) $(CXXFLAGS) qfunction.cpp
mynn/layer:		layer.cpp
	$(CXX) $(CXXFLAGS) layer.cpp
mynn/net:			net.cpp
	$(CXX) $(CXXFLAGS) net.cpp
mynn/idx:			idx.cpp
	$(CXX) $(CXXFLAGS) idx.cpp
clean:
	rm -f qlearn *.o mynn/*.o
