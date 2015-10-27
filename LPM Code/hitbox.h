#ifndef _HITBOX_H_
    #define _HITBOX_H_

#include <SDL.h>
#include <SDL_image.h>
#include <math.h>


class hitbox
{
    public:
        float           X; //Entities X position
        float           Y; //Entities Y position
        float           Width; //Entities width
        float           Height; //Entities height
        float           farX;//X value of the bottom right corner of the box
        float           farY;//Y value of the bottom right corner of the box
        //float           CenterDist;//Distance from top left corner to center. Used in collission calculation.
        SDL_Surface     *hitSurface;//actual box to draw with
        float pointsX[10], pointsY[10]; //, pointDistances[10]; //Arrays

    public:
        hitbox(); //Constructor
    public:
        void onCleanup();
        void update(float x, float y, float width, float height);//Update location
        bool collisionCheck(hitbox other);//See if hitbox and hurtbox overlap
        float distance(float x1, float x2, float y1, float y2);//Just the distance equation
        bool inside(float checkX, float checkY, float leftX, float rightX, float topY, float bottomY); //Used for collisions
        bool platformCheck(hitbox other);
};

#endif
