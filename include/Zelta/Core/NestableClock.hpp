#ifndef ZELTALIB_NESTABLECLOCK_HPP
#define ZELTALIB_NESTABLECLOCK_HPP

#include <Zelta/Export.hpp>
#include <Zelta/Core/Clock.hpp>
#include <vector>

namespace zt {

    class EXPORT NestableClock : public zt::Clock {
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

