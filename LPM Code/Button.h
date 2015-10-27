//Last Edit: 9/18/2013

#include <iostream>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
using namespace std;

//Variables and functions used by the class, but not class specific.
bool loadButtonSheet(SDL_Surface *surface, char* filename);
SDL_Surface *loadImage(std::string filename);
void apply_surface2( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect clip );
SDL_Rect setClip(int xpos, int ypos, int w, int h);
class Button;

 //Event Tracker variable
extern SDL_Event mouse_event;

//Flag that gets set upon mouse release on a button.
extern int button_mouse_flag;

//The Master Button
class Button{

    //Private variables - No touching
    private:
        SDL_Rect box;
        SDL_Rect button_clip;
        SDL_Rect default_button;
        SDL_Rect mouseover_button;
    //Public variables
    public:
        //Initialize our buttons. X and Y are the coords, W and H are width and height.
        //Remember, x grows large going right, y grows large going down.
         Button(int x, int y, int w, int h, SDL_Rect default_but, SDL_Rect mouseover_but);

        //Handles the events that happen to our button
        void handleEvents();

        //Display our button on the screen
        void showButton(SDL_Surface *screen2, SDL_Surface* button_sheet);


};//end CLASS - button
