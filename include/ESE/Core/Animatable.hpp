/* 
 * File:   Animatable.hpp
 * Author: Rafa
 *
 * Created on February 1, 2015, 10:56 AM
 */

#ifndef ANIMATABLE_HPP
#define	ANIMATABLE_HPP

namespace ESE {

    class Animatable {
    public:
        virtual void advanceTime(float deltaTime) = 0;
    };

}

#endif	/* ANIMATABLE_HPP */

