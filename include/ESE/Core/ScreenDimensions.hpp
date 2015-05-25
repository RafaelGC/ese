/* 
 * File:   ScreenDimensions.hpp
 * Author: Rafa
 *
 * Created on 4 de abril de 2015, 13:26
 */

#ifndef ESE_SCREENDIMENSIONS_HPP
#define	ESE_SCREENDIMENSIONS_HPP
namespace ESE {

    class ScreenDimensions {
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

