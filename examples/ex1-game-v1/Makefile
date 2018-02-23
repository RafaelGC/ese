CCC = g++
CXX = g++
CFLAGS = -I../../include -L../../lib -std=c++11 -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lzeltalib

ex1-game-v1 : main.o
	$(CCC) $< -o $@ -std=c++11 -L../../lib -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lzeltalib
	
main.o : main.cpp
	$(CCC) -c -ISFML -I../../include $< -std=c++11
