#include <Zelta/Core/Clock.hpp>

namespace zt {
    Clock::Clock(){
        paused = false;
    }
    
    sf::Time Clock::getElapsedTime() const{
        return sf::Clock::getElapsedTime() - pausedTime - (paused ? pausedClock.getElapsedTime() : sf::Time());
    }
    
    void Clock::pause(){
        paused = true;
        
        pausedClock.restart();
    }
    
    void Clock::resume(){
        paused = false;
        
        pausedTime += pausedClock.restart();
    }
    
    sf::Time Clock::restart(){
        sf::Time t = getElapsedTime();
        sf::Clock::restart();
        pausedClock.restart();
        pausedTime = sf::Time::Zero;
        
        return t;
    }
    
    bool Clock::isPaused() const{
        return paused;
    }
}