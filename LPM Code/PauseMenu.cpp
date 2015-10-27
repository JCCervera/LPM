//Last Edit: 9/12/2013 - Matt
//Pause Menu: Called from the game whenever the user presses ESC.
//            Gives the user the option to save their game, return to the main menu, or quit.

#include "Button.h"
#include "CApp.h"

//Initialize our global surfaces to null. These surfaces are used by multiple functions, and store the background image for
//the pause menu, as well as the various buttons images.
SDL_Surface* pause_button_sheet = NULL;
SDL_Surface* background6 = NULL;


//pauseMenu - Pause Menu, very aptly name, creates and runs the pause menu. It initializes and creates button, and contains
//            a while loop that continue polls events until the user makes a choice.
//            Called from LPM_OnEvent (when the user presses ESC)
void pauseMenu(SDL_Surface* Surf_Display){


    //Setting the area of our sprite sheet where the buttons are located.
    SDL_Rect return_button_mouseover = setClip(0*scaling_factor_W, 650*scaling_factor_H, 200*scaling_factor_W, 50*scaling_factor_H);
    SDL_Rect return_button_default= setClip(0*scaling_factor_W, 600*scaling_factor_H, 200*scaling_factor_W, 50*scaling_factor_H);
    SDL_Rect save_button_default = setClip(0, 300*scaling_factor_H, 100*scaling_factor_W, 50*scaling_factor_H);
    SDL_Rect save_button_mouseover = setClip(100*scaling_factor_W, 300*scaling_factor_H, 100*scaling_factor_W, 50*scaling_factor_H);
    SDL_Rect quit_button_default = setClip(0, 400*scaling_factor_H, 100*scaling_factor_W, 50*scaling_factor_H);
    SDL_Rect quit_button_mouseover = setClip(100*scaling_factor_W, 400*scaling_factor_H, 100*scaling_factor_W, 50*scaling_factor_H);
    SDL_Rect resume_button_default = setClip(0, 450*scaling_factor_H, 100*scaling_factor_W, 50*scaling_factor_H);
    SDL_Rect resume_button_mouseover = setClip(100*scaling_factor_W, 450*scaling_factor_H, 100*scaling_factor_W, 50*scaling_factor_H);
    SDL_Rect upgrade_button_default = setClip(0, 500*scaling_factor_H, 150*scaling_factor_W, 50*scaling_factor_H);
    SDL_Rect upgrade_button_mouseover = setClip(0, 550*scaling_factor_H, 150*scaling_factor_W, 50*scaling_factor_H);

    //Creating each individual button, passing the constructor the images for the button, along with the dimensions and locations.
    Button resume_button(250*scaling_factor_W, 115*scaling_factor_H, 100*scaling_factor_W, 50*scaling_factor_H, resume_button_default, resume_button_mouseover);
    Button upgrade_button(225*scaling_factor_W, 165*scaling_factor_H, 150*scaling_factor_W, 50*scaling_factor_H, upgrade_button_default, upgrade_button_mouseover);
    Button save_button(250*scaling_factor_W, 215*scaling_factor_H, 100*scaling_factor_W, 50*scaling_factor_H, save_button_default, save_button_mouseover);
    Button return_button(200*scaling_factor_W, 265*scaling_factor_H, 200*scaling_factor_W, 50*scaling_factor_H, return_button_default, return_button_mouseover);
    Button quit_button(250*scaling_factor_W, 315*scaling_factor_H, 100*scaling_factor_W, 50*scaling_factor_H, quit_button_default, quit_button_mouseover);

    //Offset values (these are necessary in SDL when we call the BlitSurface function later)
    SDL_Rect offset;
    offset.x = 0;
    offset.y = 0;

    //While loop that runs the pause menu until we quit.
    while(1){

        if(SDL_PollEvent(&mouse_event)){


            //For the resume button, if the mouse flag is set we do the following:
            //1. Play the button sound.
            //2. Break out of the while loop, ending the pause menu.
            resume_button.handleEvents();
            if(button_mouse_flag == 1){
                playButtonClick();
                button_mouse_flag = 0;
                break;

            }//end IF - resume button

            //For the upgrade button, if the mouse flag is set we do the following:
            //1. Play the button sound.
            //2. Call the upgrade menu. We then hold while the user interacts with the upgrade menu, and resume polling for
            //   events once the user returns.
            upgrade_button.handleEvents();
            if(button_mouse_flag == 1){

                playButtonClick();
                upgradeMenu(Surf_Display);
                button_mouse_flag = 0;

            }//end IF - upgrade button

            //For the save button, if the mouse flag is set we do the following:
            //1. Play the button sound.
            //2. Call saveGame, which writes various different variables to our character files. Once the user returns,
            //   we continue with the while loop.
            save_button.handleEvents();
            if(button_mouse_flag == 1){

                playButtonClick();
                saveGame();
                button_mouse_flag = 0;

            }//end IF - save button

            //For the return button button, if the mouse flag is set we do the following:
            //1. Play the button sound.
            //2. Set the game_running and running flags so we can cleanup and close the game
            //3. Break out of the loop and return to main.
            return_button.handleEvents();
            if(button_mouse_flag == 1){

                playButtonClick();
                game_running = 0;
                Running = false;
                button_mouse_flag = 0;
                break;

            }//end IF - return to main

            //For the quit button, if the mouse flag is set we do the following:
            //1. Play the button sound.
            //2. Set the active and running flags, which will signal the game to clean-up and totally exit the program.
            //3. Break out of the while loop.
            quit_button.handleEvents();
            if(button_mouse_flag == 1){

                playButtonClick();
                button_mouse_flag = 0;
                active = false;
                Running = false;
                break;

            }//end IF - quit

             //Our last event to see if we've gotten an SDL_QUIT command, which happens when the user hits the X button in the
            //upper right to close the window. If they do, we:
            //1. Set the active and running flags to false, so we can signal the end of the program and begin cleanup.
            //2. Break out of the pause menu loop.
            if(mouse_event.type == SDL_QUIT){

                Running = false;
                active = false;
                break;

            }//end IF - sdl quit

        }//end IF - event handling


         //Functions called to make our buttons appear on the screen.
        SDL_BlitSurface(background6, NULL, Surf_Display, &offset);
        resume_button.showButton(Surf_Display, pause_button_sheet);
        upgrade_button.showButton(Surf_Display, pause_button_sheet);
        save_button.showButton(Surf_Display, pause_button_sheet);
        return_button.showButton(Surf_Display, pause_button_sheet);
        quit_button.showButton(Surf_Display, pause_button_sheet);

        //Flip display is a built in function that updates changes on the screen. If it has encounters an error, we break and
        //relaunch the pause menu.
       if(SDL_Flip(Surf_Display) == -1)
           break;



    }//end WHILE
    return;

}//end FUNCTION - pauseMenu


//pauseInit - Initializes the images for our background and buttons
//            Called in LPM_OnInit
void pauseInit(){

    pause_button_sheet = loadImage("menu_buttons.bmp");
    background6 = loadImage("MainMenuBg.png");

}//end FUNCTION - pauseInit


//pauseCleanUp - Basic cleanup functions that releases the two images we loaded into memory for the pause menu.
//               Called in LPM_OnCleanup
void pauseCleanUp(){

    SDL_FreeSurface(background6);
    SDL_FreeSurface(pause_button_sheet);

}//end FUNCTION - pauseCleanUp


