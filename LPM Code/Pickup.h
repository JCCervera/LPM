//Last Edit: 11/16/2013

#include <iostream>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "hitbox.h"
using namespace std;

//Functions used and declared in pickup, but not specific to the  pickup class.
//These functions are duplicate code, and need to be merged with those in the Button class.
SDL_Surface *loadImage3(string filename );
void apply_surface( double x, double y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect clipper);
SDL_Rect setClip3(int xpos, int ypos, int w, int h);
class Pickup;

//Pickup class - Armor, health, mana, whatever you like!
class Pickup{

    //Private variables - No touching
    private:
        SDL_Rect pickup_clip;

    //Public variables
    public:

        //Initialize our pickups. X and Y are the coords, W and H are width and height.
        //Remember, x grows large going right, y grows large going down.
         Pickup(double x, double y, double w, double h, SDL_Rect pickup_loc);
         SDL_Rect box;
         double x;
         double y;
         double w;
         double h;
         int pickup_type;
         hitbox  pickup_hitbox;
         void drawHitbox(SDL_Surface *display);


        //Display our pickup on the screen
        void showPickup(SDL_Surface *screen, SDL_Surface* pickup_sheet);

        //Makes our pickup slowly float to the ground.
        void descend(int miny);

        //Makes our pickup scroll with the screen when the character moves.
        void scroll(int direction);


};//end CLASS-  Pickup
