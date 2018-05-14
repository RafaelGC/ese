/* 
 * File:   ScreenDimensions.hpp
 * Author: Rafa
 *
 * Created on 4 de abril de 2015, 13:26
 */

#ifndef ZELTALIB_SCREENDIMENSIONS_HPP
#define	ZELTALIB_SCREENDIMENSIONS_HPP

#include <Zelta/Export.hpp>

namespace zt {

    /**
     * @brief This class performs some calculations to keep aspect ratio.
     * 
     * Given a development width and a development height (this is, the
     * resolution you used during the development) and the target width and target
     * height (the real size of the window where your game is being executed),
     * the class provides you with some useful methods to know where you can
     * draw keeping in ming that you want to respect the aspect ratio.
     */
    class EXPORT ScreenDimensions {
    private:
        float devW, devH, targetW, targetH;
        float factorX, factorY;

    public:
        ScreenDimensions(float devW, float devH, float targetW, float targetH);
        
        float getFactorX() const;
        float getFactorY() const;

        float getUsefulW() const;
        float getUsefulH() const;

        float getUselessW() const;
        float getUselessH() const;

        float devAspectRatio() const;
        float targetAspectRatio() const;
        
        float getDevW() const;
        float getDevH() const;
        float getTargetW() const;
        float getTargetH() const;

    };
}
#endif	/* SCREENDIMENSIONS_HPP */

