#include <ESE/Core/Clock.hpp>

namespace ESE{
    Clock::Clock(){
        elapsedTime = 0;
        paused = false;
    }
    float Clock::getElapsedTime() const{
        return elapsedTime;
    }
    void Clock::advanceTime(float deltaTime){
        if (!paused){
            elapsedTime+=deltaTime;
        }
    }
    void Clock::pause(){
        paused = true;
    }
    void Clock::reset(){
        elapsedTime = 0;
    }
    void Clock::resume(){
        paused = false;
    }
    bool Clock::isPaused() const{
        return paused;
    }
}