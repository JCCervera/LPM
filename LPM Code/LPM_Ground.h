#ifndef _LPM_SURFACE_H_
    #define _LPM_SURFACE_H_
#include "LPM_Surface.h"

class LPM_Ground {
    protected:

        SDL_Surface* Surf_Ground;//Surface for the ground

    public:
        float X;//The grounds X coordinate

        char Type;

        LPM_Ground();//Constructor

        virtual bool OnLoad(char* File);//Load the image file

        virtual void OnRender(SDL_Surface* Surf_Display, int Y);//Render it

        virtual void OnCleanup();//Frees up the surface



};


#endif
