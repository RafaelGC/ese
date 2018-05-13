# ZeltaLib


ZeltaLib is a game development oriented library written in C++. It uses [SFML](https://www.sfml-dev.org/) to deal with multimedia stuff. ZeltaLib adds some utilities for game development: scene management, resource management, asset packaging, tilemapping, etc.

ZeltaLib consists of these modules:

- **Core**: is the heart of the library. It deals with the scene and resource managment. It also has some rendering and logging tools.

- **Concurrency**: includes the TaskPool and Task classes to implement a [thread pool](https://en.wikipedia.org/wiki/Thread_pool).

- **AI**: implements an A* search algorithm (Pathfinding class). It is flexible enough to support different neighborhood criterion.

- **TileEngine**: it's a set of classes to build tile based maps. The module comes with a very basic parser to load [Tiled TMX](http://www.mapeditor.org/) files.

- **Internationalization**: this module will help you to translate your application.
- **CLI**: a command line interface is bundled with ZeltaLib. It is in an early stage, at the moment it just helps to package assets.

## Documentation

You can read the documentation in the `docs` folder. You can also read the [Getting started](https://github.com/rafaelgc/ZeltaLib/wiki/Getting-started) guide.

## Building
### Linux
I've only built ZeltaLib in Debian. Keep in mind that it's written in C++11. It just depends on SFML and pugixml. pugixml is bundled with the library so you should not care about it but you will need SFML to be installed in your system before compiling.

If you are in Linux just run `configure.sh`. The script just creates some folders, then run `make`. That will generate the file `zeltalib.a` in the `lib` directory. You can also run `make -f Makefile.CLI` to build the CLI (it will be generated in the `bin` directory).

Configuring ZeltaLib in your project is as easy as configuring SFML. Just add the `include` directory and add the `zeltalib.a` to the linker.

## License


ZeltaLib is licensed under the terms of MIT License. Read the LICENSE file.