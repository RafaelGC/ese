ZeltaLib es una **librería** orientada al **desarrollo de videojuegos** en C++. Se apoya sobre la librería [SFML](http://www.sfml-dev.org/) para trabajar con elementos multimedia. A esto, ZeltaLib añade ciertas utilidades para el desarrollo de juegos, como la gestión de escenas, gestión de recursos, etc.

ZeltaLib está compuesta de varios módulos:

-**Core**: es el núcleo de la librería, tiene clases para crear y gestionar escenas (Scene y SceneManager), para gestionar recursos (ResourceManager), entre otras cosas.

-**Concurrency**: incluye las clases TaskPool y Task para implementar un [thread pool](https://en.wikipedia.org/wiki/Thread_pool).

-**AI**: implementa el algoritmo de búsqueda A* en la clase Pathfinding. Es lo suficientemente flexible como para soportar diversos criterios de vecindad que deberán ser definidos por el usuario heredando de IMesh.

-**TileEngine**: herramienta para crear escenarios basados en casillas. El módulo incluye un parser que permite cargar archivos [TMX de Tiled](http://www.mapeditor.org/), no obstante, el soporte de estos archivos es muy básico.

ZeltaLib incluye otros módulos que deben ser revisados:

-**Text**: intento de soporte de internacionalización.

-**Mesh**: para crear grafos.