/* 
 * File:   Entity.hpp
 * Author: Rafa
 *
 * Created on 31 de agosto de 2014, 12:44
 */
#ifndef SYSTEM_HPP
//#include <ESE/EntitySystem/System.hpp>
#endif
#ifndef ENTITY_HPP
#define	ENTITY_HPP

#include <iostream>

#include "System.hpp"

namespace ESE{
    
    namespace EntityIdGenerator{
        unsigned int generateId(){
            static unsigned int nextId = 0;
            return ++nextId;
        }
    }
    
    class Entity {
        private:
            std::vector<unsigned int> components;
            /*El vector guarda un puntero a void que representa el identificador de los
            sistemas a los que está vinculada la entidad. Usar un puntero a void no supone
            ningún problema de inseguridad porque no se utiliza con el fin de acceder al
            sistema, sino que se almacena para conocer a qué sistemas estamos vinculados.
             (Esto puede cambiar más adelante)*/
            unsigned int id; 
            /*El identificador de este componente, será, normalmente, la dirección
             * del objeto (por eso es un puntero), no obstante, esto no está asegurado porque el
             * objeto podría estar construido a partir del constructor copia. No hay peligro
             * en usar un puntero a void porque no se usará para nada más que almacenar un id.
             * */
        public:
            Entity(){
                id = EntityIdGenerator::generateId();
            }
            virtual ~Entity(){
                //TODO: Si se destruye una entidad lo correcto sería que se le notificara
                //al sistema para que pudiera eliminar los componentes enlazados a la entidad.
            }

            template <class T>
            /**
             * @brief Nos permite conocer si la entidad está vinculada a un sistema.
             * @param system Sistema del que queremos conocer el vínculo.
             * @return True si la entidad está vinculada al sistema. False en caso contrario.
             */
            bool is(const System<T> &system) const{
                for (auto it = components.begin(); it!=components.end(); it++){
                    if (*it==system.getId()){
                        return true;
                    }
                }
                return false;
            }
            /**
             * 
             * @brief Alias de is(). 
             * @see is()
             * @return Bool si la entidad está vinculada a cierto sistema.
             */
            template <class T>
            bool has(System<T> &system) const{
                return is(system);
            }
            /**
             * @brief Une cierto sistema a esta entidad. Desde este momento, la entidad
             * podrá acceder al componente del sistema.
             * @param system Sistema al que se quiere vincular.
             */
            template <class T>
            void attach(System<T> &system){
                system.attachTo(id);
                components.push_back(system.getId());
            }
            template <class T>
            /**
             * @brief Desvincula el sistema de la entidad.
             * @param system Sistema del que se desvinculará la entidad.
             */
            void detach(System<T> &system){
                system.detachOf(id);
                for (auto it = components.begin(); it!=components.end(); it++){
                    if (*it==system.getId()){
                        components.erase(it);
                        break; /*Damos por hecho que el componente sólo se añadió una
                        vez a la entidad, hacerlo más de una vez carece de sentido,
                        luego salimos del bucle.*/
                    }
                }
            }

            template <class T>
            /**
             * @brief Permite acceder al componente del sistema que corresponde a esta entidad.
             * Antes de llamar a este método es importante estar seguro de que la entidad y el
             * sistema están vinculados. Esto se puede lograr con el método is() o has().
             * @param system Sistema del que queremos obtener el componente.
             * @return Puntero al componente.
             */
            T* getComponent(System<T> &system){
                return system.getComponentOf(id);
            }

            template <class T>
            /**
             * @brief Alias de getComponent que permite acceder con mayor facilidad al componente
             * que nos interese.
             * @param system Sistema del cual queremos obtener el componente.
             * @return Puntero al componente.
             */
            T* operator()(System<T>&system){
                return getComponent(system);
            }
            
            unsigned int getId(){
                return id;
            }
            
            void printSystems(){
                std::cout << "My Entity Id is " << id << std::endl;
                std::cout << "Systems attached to this entity:" << std::endl;
                for (auto it = components.begin(); it!=components.end(); it++){
                    std::cout << *it << std::endl;
                }
            }
            
    };
    
}
#endif	/* ENTITY_HPP */

