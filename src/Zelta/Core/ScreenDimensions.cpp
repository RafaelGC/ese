#include <Zelta/Core/ScreenDimensions.hpp>
namespace zt {

    ScreenDimensions::ScreenDimensions(float devW, float devH, float targetW, float targetH) :
    devW(devW), devH(devH), targetW(targetW), targetH(targetH) {
        if (devAspectRatio() < targetAspectRatio()) {
            // Black bars on the right/left sides.
            factorX = factorY = (targetH / devH);
        } else {
            // Black bars on the top/bottom sides.
            factorX = factorY = (targetW / devW);
        }
    }

    float ScreenDimensions::getFactorX() const {
        return factorX;
    }

    float ScreenDimensions::getFactorY() const {
        return factorY;
    }

    float ScreenDimensions::getUsefulW() const {
        return devW * getFactorX();
    }

    float ScreenDimensions::getUsefulH() const {
        return devH * getFactorY();
    }

    float ScreenDimensions::getUselessW() const {
        return targetW - getUsefulW();
    }

    float ScreenDimensions::getUselessH() const {
        return targetH - getUsefulH();
    }

    float ScreenDimensions::devAspectRatio() const {
        return devW / devH;
    }

    float ScreenDimensions::targetAspectRatio() const {
        return targetW / targetH;
    }
    
    float ScreenDimensions::getDevW() const{
        return devW;
    }
    
    float ScreenDimensions::getDevH() const{
        return devH;
    }
    
    float ScreenDimensions::getTargetW() const{
        return targetW;
    }
    
    float ScreenDimensions::getTargetH() const{
        return targetH;
    }
}
