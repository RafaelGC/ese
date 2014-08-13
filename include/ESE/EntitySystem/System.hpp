#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <vector>
#include <iostream>

namespace ESE{
	template <class T>
	/**
	 * @brief System es el nexo entre las entidades (Entity) y los componentes. Un sistema no es más
	 * que un contenedor de componentes que están relacionados con cierta entidad. A través del sistema
	 * seremos capaces de acceder al componente de una entidad.
	 * */
	class System{
		private:
		int id;
		std::vector<std::pair<int,T>> components;
		
		/**
		 * @brief Con este método relacionamos cierta entidad (la especificada en el id) con el componente
		 * del sistema.
		 * @param id Identificador de la entidad.
		 * @see entity()
		 * */
		 /* Este método es privado porque es imprescindible obligar al usuario a utilizar el otro método
		  * attachTo(Entity) porque es ese método el encargado de notificar a la entidad de que ha sido
		  * vinculada a cierto sistema.*/
		void attachTo(int id){
			if (id){
				components.push_back(std::make_pair(id,T()));
			}
		}
		/**
		 * @brief Desvincula una entidad de este sistema.
		 * @param id Identificador de la entidad que se quiere desvincular.
		 * */
		 /*Este método es privado por las mismas razones que attachTo(int)*/
		void deattachOf(int id){
			for (unsigned int i = 0; i<components.size(); i++){
				if (components[i].first==id){
					components.erase(components.begin()+i);
					return;
				}
			}
		}
		public:
		/**
		 * @brief Crea un System con un id nulo (=0). Será un sistema inutilizable, para que el sistema
		 * tenga alguna utilidad, su identificador debe ser distinto de cero.
		 * */
		System(){
			setId(0);
		}
		/**
		 * @brief Crea un System con un id especificado. Un id nulo inutilizará el sistema. Para obtener
		 * un identificador usa SystemGenerator::registerId() .
		 * @see SystemGenerator::registerId()
		 * */
		System(int id){
			setId(id);
		}
		/**
		 * @brief Con este método relacionamos una cierta entidad (la que se pasa como parámetro) con el
		 * componente del sistema.
		 * @param entity Entidad que quieres relacionar con el componente de este sistema.
		 * */
		void attachTo(Entity& entity){
			entity.addSystem(this->id);
			attachTo(entity.getId());
		}
		/**
		 * @brief Desvincula la entidad de este sistema.
		 * @param entity Entidad que se quiere desvincular.
		 * */
		void deattachOf(Entity& entity){
			entity.removeSystem(this->id);
			deattachOf(entity.getId());
		}
		/**
		 * @brief Con este método obtenemos el componente de cierta entidad.
		 * @param id Identificador de la entidad de la que quieres obtener el componente.
		 * */
		T* entity(int id){
			for (unsigned int i=0; i<components.size(); i++){
				if (components[i].first==id){
					return &(components[i].second);
				}
			}
			return nullptr;
		}
		/**
		 * @brief Con este método obtenemos el componente de cierta entidad.
		 * @param entity Entidad de la que quieres obtener el componente.
		 * */
		T* entity(Entity &entity){
			return this->entity(entity.getId());
		}
		/**
		 * @param id Identificador de la entidad que quieres estudiar.
		 * @return true: Si la entidad pertenece a este sistema. false: La entidad
		 * no pertenece a este sistema.
		 * */
		bool isOwnerOf(int id){
			if (entity(id)==nullptr){
				return false;
			}
			return true;
		}
		/**
		 * @param entity La entidad que quieres estudiar.
		 * @return true: Si la entidad pertenece a este sistema. false: La entidad
		 * no pertenece a este sistema.
		 * */
		bool isOwnerOf(Entity &entity){
			return isOwnerOf(entity.getId());
		}
		
		void setId(int id){
			this->id = id;
		}
		int getId(){
			return id;
		}
		int getAmountOfEntities(){
			return components.size();
		}
                void printEntitiesId(){
                    for (unsigned int i = 0; i<components.size(); i++){
                        std::cout << components[i].first << std::endl;
                    }
                }
	};
	namespace SystemGenerator{
		/**
		 * @brief Devuelve un identificador único para un sistema.
		 * */
		int registerId();
	}

}

#endif