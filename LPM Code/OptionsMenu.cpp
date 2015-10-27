//Last Edit: 11/17/2013 - Matt
//Options Menu: Called from the main menu.
//              Gives the user the option to change the resolution or view the controls

#include "Button.h"
#include "CApp.h"
#include "UserPref.h"

//Initialize our surface pointers, where we'll store the button and background images, to null.
SDL_Surface* options_button_sheet = NULL;
SDL_Surface* background8 = NULL;


//optionsMenu - Gives the user the option to change their display resolution (requiring a restart of the game), or to view the controls menu.
void optionsMenu(SDL_Surface* Surf_Display){


    //Setting our rectangles, which represent the area from the sprite sheet we'd like to clip from
    SDL_Rect back_button_default = setClip(0, 0, 256*scaling_factor_W, 96*scaling_factor_H);
    SDL_Rect back_button_mouseover = setClip(256*scaling_factor_W, 0*scaling_factor_H, 256*scaling_factor_W, 96*scaling_factor_H);
    SDL_Rect smallres_button_default = setClip(0, 96*scaling_factor_H, 256*scaling_factor_W, 96*scaling_factor_H);
    SDL_Rect smallres_button_mouseover = setClip(256*scaling_factor_W, 96*scaling_factor_H, 256*scaling_factor_W, 96*scaling_factor_H);
    SDL_Rect medres_button_default = setClip(0, 192*scaling_factor_H, 256*scaling_factor_W, 96*scaling_factor_H);
    SDL_Rect medres_button_mouseover = setClip(256*scaling_factor_W, 192*scaling_factor_H, 256*scaling_factor_W, 96*scaling_factor_H);
    SDL_Rect largeres_button_default = setClip(0, 288*scaling_factor_H, 256*scaling_factor_W, 96*scaling_factor_H);
    SDL_Rect largeres_button_mouseover = setClip(256*scaling_factor_W, 288*scaling_factor_H, 256*scaling_factor_W, 96*scaling_factor_H);
    SDL_Rect controls_button_default = setClip(0, 384*scaling_factor_H, 256*scaling_factor_W, 96*scaling_factor_H);
    SDL_Rect controls_button_mouseover = setClip(256*scaling_factor_W, 384*scaling_factor_H, 256*scaling_factor_W, 96*scaling_factor_H);

    //Creating the buttons themselves. We pass the location of the area we'd like to clip, along with the dimensions and locations of the button we'd like
    //to show on screen.
    Button back_button(384*scaling_factor_W, 0*scaling_factor_H, 256*scaling_factor_W, 96*scaling_factor_H, back_button_default, back_button_mouseover);
    Button smallres_button(384*scaling_factor_W, 96*scaling_factor_H, 256*scaling_factor_W, 96*scaling_factor_H, smallres_button_default, smallres_button_mouseover);
    Button medres_button(384*scaling_factor_W, 192*scaling_factor_H, 256*scaling_factor_W, 96*scaling_factor_H, medres_button_default, medres_button_mouseover);
    Button largeres_button(384*scaling_factor_W, 288*scaling_factor_H, 256*scaling_factor_W, 96*scaling_factor_H, largeres_button_default, largeres_button_mouseover);
    Button controls_button(384*scaling_factor_W, 384*scaling_factor_H, 256*scaling_factor_W, 96*scaling_factor_H, controls_button_default, controls_button_mouseover);

    //Offset values (these are necessary in SDL when we call the BlitSurface function later)
    SDL_Rect offset;
    offset.x = 0;
    offset.y = 0;

    //While loop that continuously polls for events. We break out of the loop and return to main when the user hits Back, or
    //restart the game if the user chooses a new resolution
    while(1){

        //If the user moved or clicked their mouse
        if(SDL_PollEvent(&mouse_event)){


            //For the resume button, if the mouse flag is set we do the following:
            //1. Play the button sound.
            //2. Break out of the while loop, ending the pause menu.
            back_button.handleEvents();
            if(button_mouse_flag == 1){
                playButtonClick();
                button_mouse_flag = 0;
                break;

            }//end IF - resume button

            //For the smallres button we:
            //1. Play the button sound.
            //2. Set the resolution
            //3. Save the resolution in a file (for future use).
            //4.Restart the game
            smallres_button.handleEvents();
            if(button_mouse_flag == 1){

                playButtonClick();
                button_mouse_flag = 0;
                screen_width = 320;
                screen_height = 240;
                saveResolution(320, 240);
                Running = false;

                if(file_menu_running == 1)
                    fileCleanUp();

                mainCompleteCleanUp();
                break;

            }//end IF - smallres

           //For the medres button we:
            //1. Play the button sound.
            //2. Set the resolution
            //3. Save the resolution in a file (for future use).
            //4.Restart the game
            medres_button.handleEvents();
            if(button_mouse_flag == 1){

                playButtonClick();
                button_mouse_flag = 0;
                screen_width = 640;
                screen_height = 480;
                saveResolution(640, 480);
                Running = false;

                if(file_menu_running == 1)
                    fileCleanUp();

                mainCompleteCleanUp();
                break;

            }//end IF - medres

           //For the largeres button we:
            //1. Play the button sound.
            //2. Set the resolution
            //3. Save the resolution in a file (for future use).
            //4.Restart the game
            largeres_button.handleEvents();
            if(button_mouse_flag == 1){

                playButtonClick();
                button_mouse_flag = 0;
                screen_width = 800;
                screen_height = 600;
                saveResolution(800, 600);
                Running = false;
                if(file_menu_running == 1)
                    fileCleanUp();

                mainCompleteCleanUp();
                break;

            }//end IF - largeres

           //For the controls button we:
            //1. Play the button sound.
            //2. Jump to the controls menu and wait for control to return.
            controls_button.handleEvents();
            if(button_mouse_flag == 1){
                playButtonClick();
                button_mouse_flag = 0;
                controlsMenu(Surf_Display);

            }//end IF - controls

             //Our last event to see if we've gotten an SDL_QUIT command, which happens when the user hits the X button in the
            //upper right to close the window. If they do, we:
            //1. Set the active and running flags to false, so we can signal the end of the program and begin cleanup.
            //2. Break out of the options menu loop.
            if(mouse_event.type == SDL_QUIT){

                //if and else statements determine the type of cleanup we need to do (depending on if the game was ever running)
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


         //Display our various buttons on the screen.
        SDL_BlitSurface(background8, NULL, Surf_Display, &offset);
        back_button.showButton(Surf_Display, options_button_sheet);
        smallres_button.showButton(Surf_Display, options_button_sheet);
        medres_button.showButton(Surf_Display, options_button_sheet);
        largeres_button.showButton(Surf_Display, options_button_sheet);
        controls_button.showButton(Surf_Display, options_button_sheet);
       if(SDL_Flip(Surf_Display) == -1)
           break;



    }//end WHILE
    return;

}//end FUNCTION - optionsMenu


//optionsInit - Initializes the images for our background and buttons
void optionsInit(){

    options_button_sheet = loadImage("options_buttons.bmp");
    background8 = loadImage("options_bg.png");

}//end FUNCTION - optionsInit


//optionsCleanUp - Basic cleanup functions that releases the two images we loaded into memory for the pause menu.
void optionsCleanUp(){

    SDL_FreeSurface(background8);
    SDL_FreeSurface(options_button_sheet);

}//end FUNCTION - optionsCleanUp


