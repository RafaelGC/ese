CCC = g++
CXX = g++
CFLAGS = -I../ZeltaLib/include -L../ZeltaLib/lib -std=c++11 -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lzeltalib

<<PROJECT_NAME>> : main.o
	$(CCC) $(CFLAGS) $< -o $@
	
main.o : main.cpp
	$(CCC) -c $(CFLAGS) $<
