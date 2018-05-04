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
        void addClock(zt::Clock& clock);
        void pause();
        void resume();
    private:
        std::vector<zt::Clock*> clocks;
    };

}

#endif /* NESTABLECLOCK_HPP */

