/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NestableClock.hpp
 * Author: rafa
 *
 * Created on May 4, 2018, 8:16 PM
 */

#ifndef ZELTALIB_NESTABLECLOCK_HPP
#define ZELTALIB_NESTABLECLOCK_HPP

#include <Zelta/Core/Clock.hpp>
#include <vector>

namespace zt {

    class NestableClock : public zt::Clock {
    public:
        NestableClock();
        void addClock(zt::NestableClock& clock);
        void pause();
        void resume();
        
        bool isLocked() const;
        NestableClock& lock();
        
        
    private:
        std::vector<zt::NestableClock*> clocks;
        bool locked;
    };

}

#endif /* NESTABLECLOCK_HPP */

