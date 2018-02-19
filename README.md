ZeltaLib
==========

ZeltaLib is a game development oriented library written in C++. It uses SFML to deal with multimedia stuff. ZeltaLib adds some utilities for game development: scene management, resource management, asset packaging, tilemapping, etc.

ZeltaLib consists of these modules:

-**Core**: is the heart of the library. It deals with the scene and resource managment. It also has some rendering and logging tools.

-**Concurrency**: includes the TaskPool and Task classes to implement a [thread pool](https://en.wikipedia.org/wiki/Thread_pool).

-**AI**: implements an A* search algorithm (Pathfinding class). It is flexible enough to support different neighborhood criterion that must be defined by the user by inheriting from IMesh.

-**TileEngine**: it's a set of classes to build tile based maps. The module comes with a very basic parser to load [Tiled TMX](http://www.mapeditor.org/) files.

-**CLI**: a command line interface is bundled with ZeltaLib. It is in an early stage, at the moment it just helps to package assets.

ZeltaLib includes two more modules that must be revised (they need a refactory):

-**Text**: a first attempt to add some internacionalization/localization support.

-**Mesh**: module for creating graphs.

Documentation
--------------

I use Doxygen to document the library. It is not complete and it's not translated to English yet.

Building
--------------

I've only built ZeltaLib in Debian. Keep in mind that it's written in C++11. It just depends on SFML and pugixml. pugixml is bundled with the library so you should not care about it but you will need SFML to be installed in your system before compiling.

If you are in Linux just run `configure.sh`. The script just creates some folders, then run `make`. That will generate the file `zeltalib.a` in the `lib` directory. You can also run `make -f Makefile.CLI` to build the CLI (it will be generated in the `bin` directory). There is a Python script called `generate_makefile.py`, you should not need it.

Configuring ZeltaLib in your project is as easy as configuring SFML. Just add the `include` directory and add the `zeltalib.a` to the linker.

License
-------------

ZeltaLib is licensed under the terms of MIT License. Read the LICENSE file.