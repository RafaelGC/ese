file = open("Makefile","w") 


modules = {
	'Core': ['AnimatableContainer', 'Application', 'Argument', 'Arguments', 'Clock',
						'ConsoleLog', 'FileLog', 'Log', 'Package', 'RenderLayer', 'RenderManager',
						'ResourceLoader', 'Scene', 'SceneManager', 'ScreenDimensions'],
						
	'TileEngine': ['Tileset', 'TiledLoader/Layer', 'TiledLoader/Map', 'TiledLoader/Object',
								 'TiledLoader/ObjectLayer', 'TiledLoader/Tile', 'TiledLoader/TiledLoader'],
								 
	'Math': ['Vector2f', 'Vector3f'],
	'External': ['pugixml'],
	'Concurrency': ['Task', 'TaskPool', 'Worker']
	
	
						
}

buildObjects = []

for module in modules:
	
	for theFile in modules[module]:
		buildObjects += ['build/Zelta/' + module + '/' + theFile + '.o']	


rules = []

for module in modules:
	
	for theFile in modules[module]:
		rules += ['build/Zelta/' + module + '/' + theFile + '.o: src/Zelta/' + module + '/' + theFile + '.cpp\n\t$(CCC) $(CFLAGS) -c $< -o $@'] 

file.write(
"""CCC = g++
CXX = g++
CFLAGS = -Iinclude -ISFML -std=c++11 -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

OBJECTS = """ + ' '.join(buildObjects) + """

bin/libzeltalib.a: $(OBJECTS)
	ar rvs $@ """ + ' '.join(buildObjects) + """

""" + '\n\n'.join(rules)) 
 
file.close()
