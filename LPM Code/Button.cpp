//Last Edit: 9/18/2013
//Button: Contains the button class and all relevant functions to the button class.
//        Lots of help from the lazyfoo.net sdl button tutorial.


//Quick HOW-TO: How do I make a button in the game?
//              1. Call load(SDL_Surface pointer, string)
//                 where SDL_Surface is the name of the surface where you'll store your sprite sheeet, and
//                 string is the name of the sprite sheet you'd like to store.
//              2. Call SetClips(SDL_rect pointer, xpos, ypos, width, height)
//                 Where sdl_rect pointer is where you want to apply the clip, and the other varibles
//                 correspond to the buttons position and size on the sprite sheet.
//              3. Create a button!
//                 Button myButton(default_button_image, mouseover_button_image, int xpos, int ypos, width, height)
//                 Where default_button_image and mouseover_button_image the clipped images you want to apply, and
//                 the position and size variables correspond to the buttons orientation on the screen.
//              4. Call the corresponding showButton and pollEvent functions for the buttons. For a specific example,
//                 check the main menu.


#include "Button.h"
#include "ResolutionManager.h"

int button_mouse_flag = 0;
SDL_Event mouse_event;


//loadButtonSheet - Simple loads a file into memory in the form of a sdl_surface pointer. Can be used for
//                  both button and background images.
//                  Returns true if everything went awesome, false if the load failed and we need to exit.
bool loadButtonSheet(SDL_Surface *surface2, char* filename){

    //Loads our sprite sheet into the button_sheet surface. If theres a problem, return false.
    if((surface2 = loadImage(filename)) == NULL)
       return false;
    //Success
    return true;
}//end FUNCTION - loadButtonSheet

//setClips - designates the areas from our sprite sheet where each button image is located.
//           For SDL_Rect, x and y coords should correspond to top left corner of the box, while
//           w and h correspond to the width and height of the box.
SDL_Rect setClip(int xpos, int ypos, int w, int h){

    SDL_Rect Rect;
    Rect.x = xpos;
    Rect.y = ypos;
    Rect.w = w;
    Rect.h = h;

    return Rect;
}//end FUNCTION - setClips


//Constructor for our button class.
Button :: Button(int x, int y, int w, int h,  SDL_Rect default_but, SDL_Rect mouseover_but){

    //Set the values of our box based on the passed in values.
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;

    //Set the default sprite for our button
    button_clip.x = default_but.x;
    button_clip.y = default_but.y;
    button_clip.w = default_but.w;
    button_clip.h = default_but.h;
    default_button.x = default_but.x;
    default_button.y = default_but.y;
    default_button.w = default_but.w;
    default_button.h = default_but.h;
    mouseover_button.x = mouseover_but.x;
    mouseover_button.y = mouseover_but.y;
    mouseover_button.w = mouseover_but.w;
    mouseover_button.h = mouseover_but.h;

}//end FUNCTION - button constructor

//handleEvents - Function that manages events our button. If there's a mouseover, we change the sprite. If theres a click, we set a flag.
void Button::handleEvents()
{
    //These variables mark the mouse offsets, essentially initializing the mouse position to 0.
    int x = 0, y = 0;

    //If the event is mouse movement:
    if( mouse_event.type == SDL_MOUSEMOTION ){


        //set our x and yalues to the mouses current position
        x = mouse_event.motion.x;
        y = mouse_event.motion.y;

        //If those x and y values are between the boxes x and y values (they're mousing over the button:
        if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) ){

            //Show the mouseover animation for the specific button.
            button_clip = mouseover_button;

        }//end IF - mouseover

        //If the mouse isn't hovering over the button, we go back to/remain default.
        else
            button_clip = default_button;

    }//end IF - mousemotion

    if(mouse_event.type == SDL_MOUSEBUTTONDOWN){
        x = mouse_event.motion.x;
        y = mouse_event.motion.y;

         if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) ){

            //Show the mouseover animation for the specific button.
            button_mouse_flag = 1;

        }//end IF - mouseover

    }//end IF - mousebuttondown

}//end FUNCTION - handleEvents

//showButton - Calls the apply_surface function to show our button on screen.
void Button::showButton(SDL_Surface *screen2, SDL_Surface* button_sheet)
{
    //Show the button
    apply_surface2( box.x, box.y, button_sheet, screen2, button_clip );
}//end FUNCTION - showButton

//loadImage - This one is fairly self explanatory. Takes in a image name (thats in our games directory) and loads that image
SDL_Surface *loadImage( std::string filename )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

    //Scale the Image
    loadedImage = scaleBy(loadedImage);

    //Return our new image!
    return loadedImage;
}//end FUNCTION - loadImage


//applySurface - Shows our button on the screen at the designated coordinates
void apply_surface2( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect clipper )
{
    //Creates a SDL_rect object and sets the x and y values of our button to it, for passing to the built in
    //SDL_BlitSurface function.
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_Rect *clip = &clipper;
    //Blit it up
    SDL_BlitSurface( source, clip, destination, &offset );

}//end FUNCTION - apply_surface2
