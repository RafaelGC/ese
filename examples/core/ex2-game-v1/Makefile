CCC = g++

ex2-game-v1 : main.o
	$(CCC) $< -o $@ -std=c++11 -L../../../lib -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lzeltalib
	
main.o : main.cpp
	$(CCC) -c -ISFML -I../../../include $< -std=c++11
