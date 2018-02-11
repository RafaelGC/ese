CCC = g++
CXX = g++
CFLAGS = -Iinclude -std=c++11
OBJECTS =   build/Zelta/CLI/ZeltaCLI.o build/Zelta/Core/Arguments.o build/Zelta/Core/Argument.o build/Zelta/Core/Package.o
OBJECTS +=  build/Zelta/Core/ConsoleLog.o build/Zelta/Core/Log.o

bin/zelta: $(OBJECTS)
	$(CCC) $(CFLAGS) $(OBJECTS) -o bin/zelta

build/Zelta/CLI/ZeltaCLI.o: src/Zelta/CLI/ZeltaCLI.cpp
	$(CCC) $(CFLAGS) -c $< -o $@

build/Zelta/Core/Arguments.o: src/Zelta/Core/Arguments.cpp
	$(CCC) $(CFLAGS) -c $< -o $@

build/Zelta/Core/Argument.o: src/Zelta/Core/Argument.cpp
	$(CCC) $(CFLAGS) -c $< -o $@

build/Zelta/Core/Package.o: src/Zelta/Core/Package.cpp
	$(CCC) $(CFLAGS) -c $< -o $@

build/Zelta/Core/ConsoleLog.o: src/Zelta/Core/ConsoleLog.cpp
	$(CCC) $(CFLAGS) -c $< -o $@

build/Zelta/Core/Log.o: src/Zelta/Core/Log.cpp
	$(CCC) $(CFLAGS) -c $< -o $@

#bin/zelta: $(OBJECTS)
#	$(CCC) $(CFLAGS) $(OBJECTS) -o bin/zelta
	
#%.o : %/%.cpp
#	$(CCC) $(CFLAGS) -c $<
