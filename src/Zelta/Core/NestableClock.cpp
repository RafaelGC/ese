/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <Zelta/Core/NestableClock.hpp>

namespace zt {

    void NestableClock::addClock(zt::Clock& clock) {
        this->clocks.push_back(&clock);

        if (this->isPaused()) {
            clock.pause();
        }
    }

    void NestableClock::pause() {
        zt::Clock::pause();

        for (auto& clock : clocks) {
            clock->pause();
        }
    }

    void NestableClock::resume() {
        zt::Clock::resume();

        for (auto& clock : clocks) {
            clock->resume();
        }
    }

}