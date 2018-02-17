/* 
 * File:   Animatable.hpp
 * Author: Rafa
 *
 * Created on February 1, 2015, 10:56 AM
 */

#ifndef ZELTALIB_ANIMATABLE_HPP
#define	ZELTALIB_ANIMATABLE_HPP

namespace zt {

    /**
     * @brief Animatable is a interface used to represent something that changes over
     * time (that's the reason its advanceTime() method takes the delta time as parameter).
     */
    class Animatable {
    public:
        virtual void advanceTime(float deltaTime) = 0;
    };

}

#endif	/* ANIMATABLE_HPP */

