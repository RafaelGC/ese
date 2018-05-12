# ZeltaLib


ZeltaLib is a game development oriented library written in C++. It uses [SFML](https://www.sfml-dev.org/) to deal with multimedia stuff. ZeltaLib adds some utilities for game development: scene management, resource management, asset packaging, tilemapping, etc.

ZeltaLib consists of these modules:

- **Core**: is the heart of the library. It deals with the scene and resource managment. It also has some rendering and logging tools.

- **Concurrency**: includes the TaskPool and Task classes to implement a [thread pool](https://en.wikipedia.org/wiki/Thread_pool).

- **AI**: implements an A* search algorithm (Pathfinding class). It is flexible enough to support different neighborhood criterion that must be defined by the user by inheriting from IMesh.

- **TileEngine**: it's a set of classes to build tile based maps. The module comes with a very basic parser to load [Tiled TMX](http://www.mapeditor.org/) files.

- **Internationalization**: this module will help you to translate your application.
- **CLI**: a command line interface is bundled with ZeltaLib. It is in an early stage, at the moment it just helps to package assets.

## Documentation

You can read the documentation in the `docs` folder. You can also read the [Getting started](https://github.com/rafaelgc/ZeltaLib/wiki/Getting-started) guide.

## Building
### Linux (Debian)
I've only built ZeltaLib in Debian. Keep in mind that it's written in C++11. It just depends on SFML and pugixml. pugixml is bundled with the library so you should not care about it but you will need SFML to be installed in your system before compiling.

If you are in Linux just run `configure.sh`. The script just creates some folders, then run `make`. That will generate the file `zeltalib.a` in the `lib` directory. You can also run `make -f Makefile.CLI` to build the CLI (it will be generated in the `bin` directory).

Configuring ZeltaLib in your project is as easy as configuring SFML. Just add the `include` directory and add the `zeltalib.a` to the linker.

### Windows (Visual Studio 2017)
You will need `cmake` before compiling ZeltaLib. Run `cmake` passing your SFML instalation folder like this:
```
cmake . -DSFML_DIR:STRING=<YOUR_SFML_FOLDER>
```

`cmake` will generate a Visual Studio solution called ZeltaLib.sln. Open and compile it.
Two important files will be generated after the compilation:
- `zeltalib.lib` in the `lib` folder.
- `zeltalib.dll` in the `bin` folder.

Now you can create a new VS project. Add SFML and ZeltaLib libraries (`.lib`), setup the additional include directories and copy the DLLs to your executable folder.

Do not forget to be consistent when using Release/Debug modes. For example, if you're compiling your project in Release mode you'll need the Release version of both SFML and ZeltaLib.

## License


ZeltaLib is licensed under the terms of MIT License. Read the LICENSE file.