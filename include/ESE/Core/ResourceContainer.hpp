#ifndef RESOURCETYPE_HPP
#define RESOURCETYPE_HPP

#include <map>
#include <string>

#include <SFML/Graphics.hpp>

#include <ESE/Core/Config.hpp>

namespace ESE
{
template <class T>
class ResourceContainer{
	/*ResourceType es una clase pensada para ser la clase padre de algún tipo de recurso. Esta clase
	 * se encarga de almacenar en un map un conjunto de recursos específicos como podrían ser una serie
	 * de imágenes. Es decir, la idea es que el usuario herede de esta clase para crear sus propios
	 * contenedores de recuros, cada uno de ellos dedicados a almacenar un tipo específico: imágenes o
	 * sonidos o, incluso, tipos de datos como enteros. Entonces, una vez tenga sus propios contenedores
	 * puede crear un nuevo gestor de recursos que herede de todos ellos para unificar todo ello.
	 * */
	protected:
	std::map <std::string, T> resources;
	virtual void loadFromFile(std::string name, std::string path)=0;
public:
	ResourceContainer(){
		
	}
	virtual ~ResourceContainer(){
		
	}
	virtual T* getResource(std::string name, bool testIfExists=true){
		if (testIfExists){
			if (resources.find(name)!=resources.end()){
				return nullptr;
			}
		}
		
		return &resources[name];
	}
	

};

}

#endif // RESOURCETYPE_HPP
