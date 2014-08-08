#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <vector>
#include <iostream>

namespace ESE{
	template <class T>
	class System; //Forward declaration
	
	class Entity{
		private:
		int id;
		/**
		 * @brief Identificadores de todos los sistemas a los que pertenece esta entidad.
		 * */
		std::vector<int>systemsId;
		/**
		 * @brief Añade un nuevo sistema a esta entidad, método utilizado por System.
		 * */
		void addSystem(int systemId);
		void removeSystem(int systemId);
	public:
		/**
		 * @brief Construye una entidad cuyo identificador es nulo e inválido.
		 * */
		Entity();
		/**
		 * @brief Construye una entidad con el identificador especificado. Se puede generar
		 * con la función EntityGenerator::registerId().
		 * @see EntityGenerator::registerId()
		 * */
		Entity(int id);
		int getAmountOfComponents();
		void setId(int id);
		int getId();
		/**
		 * @param id Indentificador del sistema que se quiere comprobar.
		 * @return True si esta entidad está vinculada al sistema que se indica.
		 * */
		bool is(int systemId);
		
		template <class T>
		/**
		 * @param system Sistema que se quiere comprobar.
		 * @return True si esta entidad está vinculada al sistema que se indica.
		 * */
		bool is(System<T>& system){
			/*for (unsigned int i=0; i<systemsId.size(); i++){
				std::cout << systemsId[i];
			}
			std::cout << std::endl;*/
			return is(system.getId());
		}
		template <class T>
		//Declaramos la clase System como amiga para que pueda acceder al método addSystem()
		friend class System;
		
		template <class T>
		/**
		 * @brief Vincula un sistema a esta entidad.
		 * @param Sistema que se quiere vincular a la entidad.
		 * */
		void attach(System<T> &system){
			system.attachTo(*this);
		}
		template <class T>
		/**
		 * @brief Desvincula esta entidad de un sistema.
		 * @param system Sistema del que se desvinculará la entidad.
		 * */
		void deattach(System<T> &system){
			system.deattachOf(*this);
		}
	};

	namespace EntityGenerator{
		/**
		 * @brief Devuelve un identificador único para una entidad.
		 * */
		int registerId();
	}
}
#endif