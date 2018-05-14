/* 
 * File:   AnimatableContainer.hpp
 * Author: Rafa
 *
 * Created on February 1, 2015, 10:43 PM
 */

#ifndef ANIMATABLECONTAINER_HPP
#define	ANIMATABLECONTAINER_HPP

#include <Zelta/Export.hpp>
#include <Zelta/Core/Animatable.hpp>

#include <vector>

namespace zt{

    /**
     * @brief Container of Animatable objects.
     */
    class EXPORT AnimatableContainer : public Animatable {
        private:
            std::vector<Animatable*>animatables;
            bool paused;
        public:
            AnimatableContainer();
            /**
             * @brief Adds an Animatable to the container.
             * @param animatable Animatable.
             */
            void add(Animatable& animatable);
            /**
             * @brief Removes an Animatable from the container.
             * @param animatable Animatable.
             */
            void remove(Animatable &animatable);
            
            void advanceTime(float deltaTime);
            
            /**
             * @return Devuelve true si está pausado.
             */
            bool isPaused() const;
            
            /**
             * @brief Pauses all child animatable objects.
             * 
             * When the container is paused, advanceTime() of child objects are
             * not called.
             * 
             */
            void pause();
            
            /**
             * @brief Resumes all child animatable objects.
             */
            void resume();
    };

}

#endif	/* ANIMATABLECONTAINER_HPP */

