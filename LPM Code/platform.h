#ifndef _PLATFORM_H_
    #define _PLATFORM_H_

#include <SDL.h>
#include <SDL_image.h>
#include <math.h>
#include <vector>
#include "hitbox.h"
#include "LPM_Ground.h"


class platform: public LPM_Ground
{
    public: //Variables
        //Keeps track of all the different entities in order for the sake of collision
        static std::vector<platform*>     platformList;
        float           Y; //Entities Y position
        float           Width; //Entities width
        float           Height; //Entities height
        hitbox          collider;

    public: //Constructors
        platform(); //Constructor
    public: //Functions
        void drawHitbox(SDL_Surface *display, bool isDraw);
        //void collisionCheck();
        void newCleanup();
        void moveUpdate(bool isLeft, double scaling_factor_W);
};

#endif
