/* 
 * File:   Clock.hpp
 * Author: Rafa
 *
 * Created on February 1, 2015, 10:33 PM
 */

#ifndef ZELTALIB_CLOCK_HPP
#define	ZELTALIB_CLOCK_HPP

#include <Zelta/Core/Animatable.hpp>
#include <SFML/System/Clock.hpp>

namespace zt{
    /**
     * @brief Class that measures time. Unlike sf::Clock, this one can be paused.
     */
    class Clock : sf::Clock {
        private:
            bool paused;
            sf::Clock pausedClock;
            sf::Time pausedTime;
        public:
            Clock();
            /**
             * @return Returns the elapsed time.
             */
            sf::Time getElapsedTime() const;
            
            /**
             * @brief Pauses the clock.
             */
            void pause();
            
            /**
             * @brief Restarts the clock.
             * @return Returns the elapsed time.
             */
            sf::Time restart();
            
            /**
             * @brief Resumes the clock.
             */
            void resume();
            
            /**
             * @return True if the clock is paused.
             */
            bool isPaused() const;

    };
}
#endif	/* CLOCK_HPP */

