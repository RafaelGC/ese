/* 
 * File:   AnimatableContainer.hpp
 * Author: Rafa
 *
 * Created on February 1, 2015, 10:43 PM
 */

#ifndef ANIMATABLECONTAINER_HPP
#define	ANIMATABLECONTAINER_HPP

#include <ESE/Core/Animatable.hpp>

#include <vector>

namespace ESE{

    /**
     * @brief Esta clase permite reunir una serie de Animatable para llamar a todos
     * sus métodos advanceTime a la vez.
     */
    class AnimatableContainer : public Animatable{
        private:
            std::vector<Animatable*>animatables;
            bool paused;
        public:
            AnimatableContainer();
            /**
             * @brief Añade un Animatable a la lista.
             * @param animatable Animatable que se desea añadir.
             */
            void add(Animatable* animatable);
            /**
             * @brief Elimina un Animatable de la lista.
             * @param animatable Animatable que se desea eliminar.
             */
            void remove(Animatable *animatable);
            void advanceTime(float deltaTime);
            
            /**
             * @return Devuelve true si está pausado.
             */
            bool isPaused() const;
            /**
             * @brief Permite evitar que se llame a cualquier advanceTime().
             */
            void pause();
            /**
             * @brief Continua con la ejecución de advanceTime().
             */
            void resume();
    };

}

#endif	/* ANIMATABLECONTAINER_HPP */

