/* 
 * File:   System.hpp
 * Author: Rafa
 *
 * Created on 31 de agosto de 2014, 12:40
 */

#ifndef SYSTEM_HPP
#define	SYSTEM_HPP

#include <vector>
#include <iostream>

namespace ESE{
    /*************GENERADOR DE IDENTIFICADORES*************/
    namespace SystemIdGenerator{
        unsigned int generateId(){
            static unsigned int nextId = 0;
            return ++nextId;
        }
    }
    
    class Entity;//Forward declaration.
    
    template <class T>
    /**
     * @brief Un sistema es la unión entre componentes y entidades. A un cierto tipo de componente,
     * que es definido por el usuario, le corresponde un sistema. Dicho sistema enlaza la entidad
     * con el componente.
     */
    class System {
        private:
            std::vector<std::pair<unsigned int,T>> components;
            //El puntero a Entity es usado como identificador, T es el componente. Inicialmente
            //se utilizaba un entero como identificador único de entidades y sistemas, sin embargo,
            //utilizando las direcciones (que son únicas), se logra el mismo fenómeno. No obstante,
            //quizá haga falta cambiarlo en el futuro. Podría no lograrse el efecto deseado si, por
            //cualquier motivo, la dirección de la entidad cambia.
            
            unsigned int id;
            
            /**
             * @brief Método usado por Entity para enlazar dicha Entity con este sistema.
             * @param entity Entidad que se quiere enlazar con este sistema.
             */
            void attachTo(unsigned int entityId){
                components.push_back(std::make_pair(entityId,T()));
            }
            /**
             * @brief Rompe el vínculo sistema-entidad. Desde ese momento, la entidad no tendrá
             * disponible el componente del sistema.
             * @param entity Entidad que se quiere desvincular del sistema.
             */
            void detachOf(const unsigned int entityId){
                for (auto it = components.begin(); it!=components.end(); it++){
                    if (entityId==it->first){
                        components.erase(it);
                        break;
                    }
                }
            }
            /**
             * @brief Devuelve el componente vinculado a cierta entidad.
             * @param entity Entidad de la que se quiere obtener el componente.
             * @return Componente vinculado a la entidad.
             */
            T* getComponentOf(const unsigned int entityId){
                for (auto it = components.begin(); it!=components.end(); it++){
                    if (it->first==entityId){
                        return &(it->second);
                    }
                }
                return nullptr;
            }
        public:

            System(){
                id = SystemIdGenerator::generateId();
                std::cout << "Sistema creado con id= " << id << std::endl;
            }
            virtual ~System(){

            }
            void printEntities(){
                std::cout << "My system id is " << id << std::endl; 
                std::cout << "Entities attached to this system:" << std::endl;
                for (auto it = components.begin(); it!=components.end(); it++){
                    std::cout << it->first << std::endl;
                }
            }
            
            inline unsigned int getId() const{
                return id;
            }
            
            
        private:
            //NOPE System(const System& orig); //Suprimo el constructor copia, por el momento.
            friend class Entity; //Para que Entity tenga acceso a los métodos attachTo y detachOf.

    };
    
}
#endif	/* SYSTEM_HPP */

