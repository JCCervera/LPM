//Last Edit: 11/14/2013 - Matt
//Resolution Manager: Currently, only serves the purpose of taking in a surface that is loaded in correctly
//                    for our default resolution, and then scaling that surface up or down depending on the new resolution.


#include "CApp.h"
#include <SDL_rotozoom.h>


//scaleBy - Takes any given image and zooms in to the appropriate value.
SDL_Surface* scaleBy(SDL_Surface* image){

    //We declare a temporary surface pointer and load our newly zoomed image into it.
    SDL_Surface* temp_image;
    temp_image = zoomSurface (image, scaling_factor_W, scaling_factor_H, 1);

    //Free the old image pointer.
    SDL_FreeSurface(image);

    //Set the pointer to the new image and return it.
    image = temp_image;
    return image;

}//end FUNCTION - scaleBy

