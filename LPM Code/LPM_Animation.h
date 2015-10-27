#ifndef _LPM_ANIMATION_H_
    #define _LPM_ANIMATION_H_

#include <SDL.h>

class LPM_Animation{
    public:
        int CurrentFrame;//Keeps track of which frame is currently displayed

        int FrameInc;//Decides which way to increment the animations


    private:


        long OldTime;//Use for framerate, explained more in LPM_Animation.cpp

    public:
        int MaxFrames;//Amount of frames

        bool Oscillate;//Decides whether animated object oscillates its frames, rather than looping

        int FrameRate;

    public:
        LPM_Animation();//Animation constructor

        void OnAnimate();//handles looping the frame, and framerate handling

    public:
        void SetFrameRate(int Rate);//Allows to set a framerate

        void SetCurrentFrame(int Frame);//Allows to choose a frame

        int GetCurrentFrame();//Returns which frame you're currently on
};
#endif // _LPM_ANIMATION_H_
