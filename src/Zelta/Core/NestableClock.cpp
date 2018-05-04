/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <Zelta/Core/NestableClock.hpp>

namespace zt {

    NestableClock::NestableClock() {
        locked = false;
    }
    
    void NestableClock::addClock(zt::NestableClock& clock) {
        this->clocks.push_back(&clock);

        // The added clock inherits its state
        // from the parent (unless it's locked).
        if (!clock.isLocked()) {
            if (this->isPaused()) {
                clock.pause();
            }
            else {
                clock.resume();
            }
        }
        
    }

    void NestableClock::pause() {
        zt::Clock::pause();

        for (auto& clock : clocks) {
            if (clock->isLocked()) continue;
            
            clock->pause();
        }
    }

    void NestableClock::resume() {
        zt::Clock::resume();

        for (auto& clock : clocks) {
            if (clock->isLocked()) continue;
            
            clock->resume();
        }
    }
    
    bool NestableClock::isLocked() const {
        return this->locked;
    }
    NestableClock& NestableClock::lock() {
        this->locked = true;
        return *this;
    }

}