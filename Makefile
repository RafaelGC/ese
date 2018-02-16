CCC = g++
CXX = g++
CFLAGS = -Iinclude -ISFML -std=c++11 -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

OBJECTS = build/Zelta/TileEngine/Tileset.o build/Zelta/TileEngine/TiledLoader/Layer.o build/Zelta/TileEngine/TiledLoader/Map.o build/Zelta/TileEngine/TiledLoader/Object.o build/Zelta/TileEngine/TiledLoader/ObjectLayer.o build/Zelta/TileEngine/TiledLoader/Tile.o build/Zelta/TileEngine/TiledLoader/TiledLoader.o build/Zelta/Core/AnimatableContainer.o build/Zelta/Core/Application.o build/Zelta/Core/Argument.o build/Zelta/Core/Arguments.o build/Zelta/Core/Clock.o build/Zelta/Core/ConsoleLog.o build/Zelta/Core/FileLog.o build/Zelta/Core/Log.o build/Zelta/Core/Package.o build/Zelta/Core/RenderLayer.o build/Zelta/Core/RenderManager.o build/Zelta/Core/ResourceLoader.o build/Zelta/Core/Scene.o build/Zelta/Core/SceneManager.o build/Zelta/Core/ScreenDimensions.o build/Zelta/External/pugixml.o build/Zelta/Math/Vector2f.o build/Zelta/Math/Vector3f.o build/Zelta/Concurrency/Task.o build/Zelta/Concurrency/TaskPool.o build/Zelta/Concurrency/Worker.o

lib/zeltalib.a: $(OBJECTS)
	ar rvs $@ build/Zelta/TileEngine/Tileset.o build/Zelta/TileEngine/TiledLoader/Layer.o build/Zelta/TileEngine/TiledLoader/Map.o build/Zelta/TileEngine/TiledLoader/Object.o build/Zelta/TileEngine/TiledLoader/ObjectLayer.o build/Zelta/TileEngine/TiledLoader/Tile.o build/Zelta/TileEngine/TiledLoader/TiledLoader.o build/Zelta/Core/AnimatableContainer.o build/Zelta/Core/Application.o build/Zelta/Core/Argument.o build/Zelta/Core/Arguments.o build/Zelta/Core/Clock.o build/Zelta/Core/ConsoleLog.o build/Zelta/Core/FileLog.o build/Zelta/Core/Log.o build/Zelta/Core/Package.o build/Zelta/Core/RenderLayer.o build/Zelta/Core/RenderManager.o build/Zelta/Core/ResourceLoader.o build/Zelta/Core/Scene.o build/Zelta/Core/SceneManager.o build/Zelta/Core/ScreenDimensions.o build/Zelta/External/pugixml.o build/Zelta/Math/Vector2f.o build/Zelta/Math/Vector3f.o build/Zelta/Concurrency/Task.o build/Zelta/Concurrency/TaskPool.o build/Zelta/Concurrency/Worker.o

build/Zelta/TileEngine/Tileset.o: src/Zelta/TileEngine/Tileset.cpp
	$(CCC) $(CFLAGS) -c $< -o $@

build/Zelta/TileEngine/TiledLoader/Layer.o: src/Zelta/TileEngine/TiledLoader/Layer.cpp
	$(CCC) $(CFLAGS) -c $< -o $@

build/Zelta/TileEngine/TiledLoader/Map.o: src/Zelta/TileEngine/TiledLoader/Map.cpp
	$(CCC) $(CFLAGS) -c $< -o $@

build/Zelta/TileEngine/TiledLoader/Object.o: src/Zelta/TileEngine/TiledLoader/Object.cpp
	$(CCC) $(CFLAGS) -c $< -o $@

build/Zelta/TileEngine/TiledLoader/ObjectLayer.o: src/Zelta/TileEngine/TiledLoader/ObjectLayer.cpp
	$(CCC) $(CFLAGS) -c $< -o $@

build/Zelta/TileEngine/TiledLoader/Tile.o: src/Zelta/TileEngine/TiledLoader/Tile.cpp
	$(CCC) $(CFLAGS) -c $< -o $@

build/Zelta/TileEngine/TiledLoader/TiledLoader.o: src/Zelta/TileEngine/TiledLoader/TiledLoader.cpp
	$(CCC) $(CFLAGS) -c $< -o $@

build/Zelta/Core/AnimatableContainer.o: src/Zelta/Core/AnimatableContainer.cpp
	$(CCC) $(CFLAGS) -c $< -o $@

build/Zelta/Core/Application.o: src/Zelta/Core/Application.cpp
	$(CCC) $(CFLAGS) -c $< -o $@

build/Zelta/Core/Argument.o: src/Zelta/Core/Argument.cpp
	$(CCC) $(CFLAGS) -c $< -o $@

build/Zelta/Core/Arguments.o: src/Zelta/Core/Arguments.cpp
	$(CCC) $(CFLAGS) -c $< -o $@

build/Zelta/Core/Clock.o: src/Zelta/Core/Clock.cpp
	$(CCC) $(CFLAGS) -c $< -o $@

build/Zelta/Core/ConsoleLog.o: src/Zelta/Core/ConsoleLog.cpp
	$(CCC) $(CFLAGS) -c $< -o $@

build/Zelta/Core/FileLog.o: src/Zelta/Core/FileLog.cpp
	$(CCC) $(CFLAGS) -c $< -o $@

build/Zelta/Core/Log.o: src/Zelta/Core/Log.cpp
	$(CCC) $(CFLAGS) -c $< -o $@

build/Zelta/Core/Package.o: src/Zelta/Core/Package.cpp
	$(CCC) $(CFLAGS) -c $< -o $@

build/Zelta/Core/RenderLayer.o: src/Zelta/Core/RenderLayer.cpp
	$(CCC) $(CFLAGS) -c $< -o $@

build/Zelta/Core/RenderManager.o: src/Zelta/Core/RenderManager.cpp
	$(CCC) $(CFLAGS) -c $< -o $@

build/Zelta/Core/ResourceLoader.o: src/Zelta/Core/ResourceLoader.cpp
	$(CCC) $(CFLAGS) -c $< -o $@

build/Zelta/Core/Scene.o: src/Zelta/Core/Scene.cpp
	$(CCC) $(CFLAGS) -c $< -o $@

build/Zelta/Core/SceneManager.o: src/Zelta/Core/SceneManager.cpp
	$(CCC) $(CFLAGS) -c $< -o $@

build/Zelta/Core/ScreenDimensions.o: src/Zelta/Core/ScreenDimensions.cpp
	$(CCC) $(CFLAGS) -c $< -o $@

build/Zelta/External/pugixml.o: src/Zelta/External/pugixml.cpp
	$(CCC) $(CFLAGS) -c $< -o $@

build/Zelta/Math/Vector2f.o: src/Zelta/Math/Vector2f.cpp
	$(CCC) $(CFLAGS) -c $< -o $@

build/Zelta/Math/Vector3f.o: src/Zelta/Math/Vector3f.cpp
	$(CCC) $(CFLAGS) -c $< -o $@

build/Zelta/Concurrency/Task.o: src/Zelta/Concurrency/Task.cpp
	$(CCC) $(CFLAGS) -c $< -o $@

build/Zelta/Concurrency/TaskPool.o: src/Zelta/Concurrency/TaskPool.cpp
	$(CCC) $(CFLAGS) -c $< -o $@

build/Zelta/Concurrency/Worker.o: src/Zelta/Concurrency/Worker.cpp
	$(CCC) $(CFLAGS) -c $< -o $@
