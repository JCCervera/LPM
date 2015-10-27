//Last Edit: 11/16/2013

//Pickup - How to make a pickup basic guide (the important, unique stuff):
//                                          1. Set the clips for the image:
//                                                          mypotion_clip = setClip3(0, 0, 80*scaling_factor_W, 64*scaling_factor_H);
//                                          2. Create the pickup:
//                                                          Pickup my_pickup(x,y,w,h,sdl_Rect clip)
//                                          3. Show it:
//                                                          my_pickup.showButton(Surf_Display, sprite sheet);
//                                          4. Reference potion.cpp for something more specific.


#include "LPM_Entity.h"
#include "CApp.h"
#include "Pickup.h"

//setClip - Set the clip area from the pickup sprite sheet.
//          Duplicate code from Button.cpp, consider putting this somewhere else.
//          Call this like: SDL_Rect my_pickup_clip = setClip(x,y,w,h)
SDL_Rect setClip3(int xpos, int ypos, int w, int h){

    SDL_Rect Rect;
    Rect.x = xpos;
    Rect.y = ypos;
    Rect.w = w;
    Rect.h = h;

    return Rect;
}//end FUNCTION - setClips

//Constructor for pickup
Pickup :: Pickup(double x, double y, double w, double h,  SDL_Rect pickup_loc){

    //Set the values of our box based on the passed in values.
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;

    //Set the default sprite for our pickup
    pickup_clip.x = pickup_loc.x;
    pickup_clip.y = pickup_loc.y;
    pickup_clip.w = pickup_loc.w;
    pickup_clip.h = pickup_loc.h;

}//end CONSTRUCTOR

//showPickup - Calls the function applySurface to show our pickup on the screen
void Pickup::showPickup(SDL_Surface *screen2, SDL_Surface* pickup_sheet){

    apply_surface(x, y, pickup_sheet, screen2, pickup_clip );

}//end FUNCTION - showPickup

//descend - We call this function with the minimum y value of the screen (i.e. the ground), and compare that
//          to where our pickup is now. if our pickup is not on the ground, make it move towards the ground.
void Pickup :: descend(int miny){
    if (y < (miny*scaling_factor_H))
        y++;
}//end FUNCTION - descend

//scroll - We call this function with a direction (either a 1 or something else).
//         If 1, then we move the pickup to the right by increasing its x value.
//         Else, we do the opposite.
void Pickup :: scroll(int direction){

    if (direction == 1){
        x+=(3*scaling_factor_W);
    }//end IF

    else{
        x-=(3*scaling_factor_W);
    }//end ELSE
}

//Loads image - Passed a filename in our current directory and loads that file into a surface.
SDL_Surface *loadImage3( std::string filename ){
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

    //Scale the Image
    loadedImage = scaleBy(loadedImage);

    //And, most importantly, return the image.
    return loadedImage;

}//end FUNCTION - loadImage

//Applys the passed in surface (our pickup) to our surface.
void apply_surface( double x, double y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect clipper )
{
    //Creates a SDL_rect object and sets the x and y values of our button to it, for passing to the built in
    //SDL_BlitSurface function.
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_Rect *clip = &clipper;
    //Blit it up
    SDL_BlitSurface( source, clip, destination, &offset );

}//end FUNCTION - apply_surface


//drawHitbox - Applies a hitbox to our current position for collision checking (picking up the pickup)
void Pickup :: drawHitbox(SDL_Surface *Surf_Display){

    //Update the hitbox position
    this->pickup_hitbox.update(this->x, this->y, this->w, this->h);

}//end FUNCTION - drawHitbox
