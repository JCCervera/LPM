//Last Edit: 11/17/2013 - Matt
//Controls Menu: Displays a How-To-Play Slash Screen, with a back button! Very Exciting.

#include "Button.h"
#include "CApp.h"

//Initialize the surface pointers we need to store our images
SDL_Surface* controls_button_sheet = NULL;
SDL_Surface* background9 = NULL;


//controlsMenu - A super simple menu that has one button, a back button, and shows a splash screen telling the user how to play the game.
void controlsMenu(SDL_Surface* Surf_Display){


    //Set the clips for our two images, the default back button and its mouseover counter part
    SDL_Rect back_button_default = setClip(0, 0, 100*scaling_factor_W, 50*scaling_factor_H);
    SDL_Rect back_button_mouseover = setClip(0*scaling_factor_W, 50*scaling_factor_H, 100*scaling_factor_W, 50*scaling_factor_H);

    //Create the button with the given dimensions and location.
    Button back_button(270*scaling_factor_W, 400*scaling_factor_H, 100*scaling_factor_W, 50*scaling_factor_H, back_button_default, back_button_mouseover);

    //Offset values (these are necessary in SDL when we call the BlitSurface function later)
    SDL_Rect offset;
    offset.x = 0;
    offset.y = 0;

    //While loop that polls for events (in this case, all we're checking to see is if the user clicks the back button or exits the game).
    while(1){

        if(SDL_PollEvent(&mouse_event)){


            //For the back button, if the mouse flag is set we do the following:
            //1. Play the button sound.
            //2. Break out of the while loop, ending the controls menu.
            back_button.handleEvents();
            if(button_mouse_flag == 1){
                playButtonClick();
                button_mouse_flag = 0;
                break;

            }//end IF - back button



             //If we get an SDL_QUIT (user presses the X in the top right of the window)
            //1. Set the active and running flags to false, so we can signal the end of the program and begin cleanup.
            //2. Break out of the pause menu loop.
            //3, The if/else tells us what type of cleanup to do (dictated by if the game is currently running or not).
            if(mouse_event.type == SDL_QUIT){

               if (game_running == 1){
                    Running = false;
                    active = false;
                }//end IF - inner

                else{
                    Running = false;
                    active = false;
                    if(file_menu_running == 1)
                        fileCleanUp();
                    mainCompleteCleanUp();
                }//end ELSE

                break;

            }//end IF - sdl quit

        }//end IF - event handling


         //Displays our button and background to the display
        SDL_BlitSurface(background9, NULL, Surf_Display, &offset);
        back_button.showButton(Surf_Display, controls_button_sheet);
        if(SDL_Flip(Surf_Display) == -1)
            break;

    }//end WHILE


}//end FUNCTION - controlsMenu


//controlsInit - loads the two images for our controls button and background into their respective pointers
void controlsInit(){

    controls_button_sheet = loadImage("controls.bmp");
    background9 = loadImage("controls_bg.png");

}//end FUNCTION - controlsInit


//controlsCleanUp - Basic cleanup functions that releases the two images we loaded into memory for the controls menu.
void controlsCleanUp(){

    SDL_FreeSurface(background9);
    SDL_FreeSurface(controls_button_sheet);

}//end FUNCTION - controlsCleanUp


