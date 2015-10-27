#include "LPM_Animation.h"

//Construct the animation dude
LPM_Animation::LPM_Animation() {
    //current frame displayed
    CurrentFrame    = 0;
    //Max amount of frames
    MaxFrames       = 0;
    //By how many frames we are incrementing
    FrameInc        = 1;

    //Rate of frame change in milliseconds
    FrameRate       = 100;
    OldTime         = 0;

    //Allows to oscillate between frames
    Oscillate       = false;
}

//Animate that stuff!
void LPM_Animation::OnAnimate() {

    //Get our current frame rate and make sure its kosher.
    if(OldTime + FrameRate > SDL_GetTicks()){
        return;
    }

    //If kosher, save the amount so we can check it later
    OldTime = SDL_GetTicks();

    //Increment the current frame
    CurrentFrame += FrameInc;

    //if you want to oscillate it
    if(Oscillate) {
        //and you are snimating forward
        if(FrameInc > 0) {
            //and you are at the last frame
            if(CurrentFrame >= MaxFrames) {
                //Start heading back
                FrameInc = -FrameInc;
            }
        }
        //If you reached the beginning, head forward
        else{
            if(CurrentFrame <= 0){
                FrameInc = -FrameInc;
            }
        }
    }
    //If you are just looping, head back to the first frame
    else{
        if(CurrentFrame >= MaxFrames) {
            CurrentFrame = 0;
        }
    }
}
//Set your framerate
void LPM_Animation::SetFrameRate(int Rate) {
    FrameRate = Rate;
}
//Set your current frame
void LPM_Animation::SetCurrentFrame(int Frame) {
    if(Frame < 0 || Frame >= MaxFrames) return;

    CurrentFrame = Frame;
}
//Find out which frame you're currently on
int LPM_Animation::GetCurrentFrame() {
    return CurrentFrame;
}
