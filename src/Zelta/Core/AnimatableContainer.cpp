#include <Zelta/Core/AnimatableContainer.hpp>

namespace zt{

    AnimatableContainer::AnimatableContainer(){
        paused = false;
    }

    void AnimatableContainer::add(Animatable& animatable){
        animatables.push_back(&animatable);
    }
    void AnimatableContainer::remove(Animatable& animatable){
        for (auto it = animatables.begin(); it!=animatables.end(); it++){
            if ((*it)==&animatable){
                animatables.erase(it);
                break;
            }
        }
    }

    void AnimatableContainer::advanceTime(float deltaTime){
        if (!isPaused()){
            for (auto it = animatables.begin(); it!=animatables.end(); it++){
                (*it)->advanceTime(deltaTime);
            }
        }
    }
    
    void AnimatableContainer::pause(){
        paused = true;
    }
    void AnimatableContainer::resume(){
        paused = false;
    }
    bool AnimatableContainer::isPaused() const{
        return paused;
    }
}