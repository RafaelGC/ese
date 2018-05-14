cmake_minimum_required (VERSION 2.6)
project(ZeltaLib DESCRIPTION "Game development library based on SFML.")

# Set the folder to store .lib and .dll
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}" )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}" )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}" )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}" )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}" )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}" )

set(SFML_DIR "" CACHE STRING "SFML folder path.")

# SFML
include_directories("${SFML_DIR}/include")
link_directories("${SFML_DIR}/lib")

# ZeltaLib includes.
include_directories("${PROJECT_BINARY_DIR}/include")

add_library(zeltalib SHARED
src/Zelta/Core/Application.cpp
src/Zelta/Core/Argument.cpp
src/Zelta/Core/Arguments.cpp
src/Zelta/Core/Scene.cpp
src/Zelta/Core/SceneManager.cpp
src/Zelta/Core/Clock.cpp
src/Zelta/Core/NestableClock.cpp
src/Zelta/Core/AnimatableContainer.cpp
src/Zelta/Core/Log.cpp
src/Zelta/Core/ConsoleLog.cpp
src/Zelta/Core/FileLog.cpp
src/Zelta/Core/NestableClock.cpp
src/Zelta/Core/Package.cpp
src/Zelta/Core/RenderLayer.cpp
src/Zelta/Core/ScreenDimensions.cpp

src/Zelta/Math/Vector2f.cpp
src/Zelta/Math/Vector3f.cpp
	
src/Zelta/Concurrency/Task.cpp
src/Zelta/Concurrency/Worker.cpp
src/Zelta/Concurrency/TaskPool.cpp

src/Zelta/Internationalization/Text.cpp
src/Zelta/Internationalization/TextContainer.cpp
src/Zelta/Internationalization/AutoLang.cpp

src/Zelta/TileEngine/Tileset.cpp
src/Zelta/TileEngine/TiledLoader/Layer.cpp
src/Zelta/TileEngine/TiledLoader/Map.cpp
src/Zelta/TileEngine/TiledLoader/Object.cpp
src/Zelta/TileEngine/TiledLoader/ObjectLayer.cpp
src/Zelta/TileEngine/TiledLoader/Tile.cpp
src/Zelta/TileEngine/TiledLoader/TiledLoader.cpp

src/Zelta/External/pugixml.cpp
)

target_link_libraries(zeltalib sfml-system sfml-window sfml-graphics sfml-audio)