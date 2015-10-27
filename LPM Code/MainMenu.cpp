//Last Edit: 11/16/2013 - Matt
//Main Menu: The most important of menus. Called at the beginning of each game instance, the main menu gives the player the
//           option to play the game, visit the options menu, or exit the game.

#include "Button.h"
#include "CApp.h"

//Initialize our global surfaces to null. These surfaces are used by multiple functions, and store the background image for
//the main menu, the images for the buttons, and creates a display for us to draw these images on (surface).
SDL_Surface* mm_button_sheet = NULL;
SDL_Surface* background2 = NULL;
SDL_Surface* surface = NULL;

//mainMenu - Runs the main menu function. It calls an init function to
//           initializes the true type font, buttons, images, and sounds for the main menu.
//           It also contains a loop which runs the main menu, continually checking for events to detect when the user
//           clicks a button.
void mainMenu(SDL_Surface* Surf_Display){

    //Sets our main surface (what we render all of our images and buttons on) to the global display, Surf_Display.
    surface = Surf_Display;

    //Calls playMMBG from our SoundPlayer to play our background menu music.
    playMMBG();


    //Now, we start the button creation process. We create a set of SDL_Rects, whose dimensions correspond to the x-position,
    //y position, width, and height of each button on our button sprite sheet (the file address is stored in mm_button_sheet).
    SDL_Rect start_button_default = setClip(0, 0, 100*scaling_factor_W, 50*scaling_factor_H);
    SDL_Rect start_button_mouseover = setClip(100*scaling_factor_W, 0, 100*scaling_factor_W, 50*scaling_factor_H);
    SDL_Rect options_button_default = setClip(0, 50*scaling_factor_H, 100*scaling_factor_W, 50*scaling_factor_H);
    SDL_Rect options_button_mouseover = setClip(100*scaling_factor_W, 50*scaling_factor_H, 100*scaling_factor_W, 50*scaling_factor_H);
    SDL_Rect exit_button_default = setClip(0, 100*scaling_factor_H, 100*scaling_factor_W, 50*scaling_factor_H);
    SDL_Rect exit_button_mouseover = setClip(100*scaling_factor_W, 100*scaling_factor_H, 100*scaling_factor_W, 50*scaling_factor_H);

    //Here, we create each individual button for our three main menu buttons (start, options, and exit).
    //We pass in the parameters x-pos- y-pos, width, height, and the two images that correspond to the regular mouse button,
    //as well as the mouse-over button, which we just set by set clips.
    //The x and y positions here correspond to the top left corner of the button on our screen.
    //The width and height correspond to the area where the button can be interacted with.
    Button start_button(250*scaling_factor_W, 330*scaling_factor_H, 100*scaling_factor_W, 50*scaling_factor_H, start_button_default, start_button_mouseover);
    Button options_button(250*scaling_factor_W, 380*scaling_factor_H, 100*scaling_factor_W, 50*scaling_factor_H, options_button_default, options_button_mouseover);
    Button exit_button(250*scaling_factor_W, 430*scaling_factor_H, 100*scaling_factor_W, 50*scaling_factor_H, exit_button_default, exit_button_mouseover);


    //Offset values (these are necessary in SDL when we call the BlitSurface function later)
    SDL_Rect offset;
    offset.x = 0;
    offset.y = 0;

    //This while loop runs the main menu. It continually checks for "mouse_event" to be true, and if it is we check the mouses
    //position and act accordingly.
    while(Running == true){
        if(SDL_PollEvent(&mouse_event)){

            //Each individual button calls handle event when we detect a mouse event. It also has a corresponding if statement,
            //which is triggered if the position of the mouse is within the area of the button and the user clicks the mouse.
            //The trigger is named button_mouse_flag, and is set by handleEvents.

            //For the start button, if the mouse flag is set we do the following:
            //1. Play the button sound.
            //2. Call the File Menu, which prompts the user to load a game.
            //3. After we return from the file menu, if the user has chosen to exit the game we break from the loop.
            //   If not, then the user chose the "Back" option from the file menu, and we continue the main menu loop.
            start_button.handleEvents();
            if(button_mouse_flag == 1){

                button_mouse_flag = 0;
                playButtonClick();
                fileMenu(Surf_Display);
                if (Running == false){

                    break;

                }//end IF - running check

            }//end IF - start button

            //For the options button, if the mouse flag is set we do the following:
            //1. Play the button sound.
            //2. Call the options menu, which gives the user a variety of gameplay options.
            //3. Will have a running parameter similar to the file menu after implementation.
            options_button.handleEvents();
            if(button_mouse_flag == 1){
                playButtonClick();
                button_mouse_flag = 0;
                optionsMenu(Surf_Display);
                 if (Running == false){

                    break;

                }//end IF - running check

            }//end IF - options button

            //For the Exit button, if the mouse flag is set we do the following:
            //1. Play the button sound.
            //2. Set the necessary flags for exiting the game. This means we set Running to false to exit the main menu loop,
            //   and the active flag to false to break the loop in main.
            //3. We choose the appropriate cleanup mode with an if-else statement, based on whether the game has been running
            //   and already attempted cleanup, or if we are exiting prior to the game launching.
            exit_button.handleEvents();
            if(button_mouse_flag == 1){

                playButtonClick();
                button_mouse_flag = 0;
                Running = false;
                active = false;
                if (game_running == 0){

                    fileCleanUp();
                    mainCompleteCleanUp();


                }//end IF - game running flag
               break;
            }//end IF - exit button

            //Our last event to see if we've gotten an SDL_QUIT command, which happens when the user hits the X button in the
            //upper right to close the window. If they do, we:
            //1. Set the active and running flags to false, so we can break out of the main and main menu loops.
            //2. Call our clean-up functions if the game has not been running. Clean-up occurs in the game if it has been
            //3. running, but must occur here if it has not been running.
            if(mouse_event.type == SDL_QUIT){

                active = false;
                Running = false;
                if (game_running == 0){
                    fileCleanUp();
                    mainCompleteCleanUp();
                }//end IF - game running

                break;
            }//end IF - sdl quit

        }//end IF - event polling

        //The following set of function calls are used to update and display both our button and our background on the
        //screen (our Surf_Display). The background image is passed to the blitsurface function, and the buttons are
        //shown by calling showbutton.
        SDL_BlitSurface(background2, NULL, Surf_Display, &offset);
        start_button.showButton(Surf_Display, mm_button_sheet);
        options_button.showButton(Surf_Display, mm_button_sheet);
        exit_button.showButton(Surf_Display, mm_button_sheet);

        //Flip display is a built in function that updates changes on the screen. If it has encounters an error, we break and
        //relaunch the main menu.
       if(SDL_Flip(Surf_Display) == -1)
           break;

    }//end WHILE - main menu

}//end FUNCTION - mainMenu

//mainInit - Initializes various aspects of our main menu, including general SDL, our font, sounds, and images.
//           If there is an error in any of the initialization, return false. Right now, we're ignoring the return value until
//           we implement some kind of error prompt.
bool mainInit(){

    //Required function call to the built in SDL_Init to get the program up and running.
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
      return false;

    //Initialize TTF - true type font (for displaying text on the screen).
    if (TTF_Init() != 0)
       return false;

    //Initialize the sound, called from file SoundPlayer.cpp
    //Also loads the relevant sound files for the main menu so we can play them upon launching the menu.
    initSound();
    loadMMSound();
    loadButtonSound();


    //Setting the caption for our window
    SDL_WM_SetCaption("LASER POWERED MUSKET", NULL);


    //Loading our sprite sheets for both the main menu background and the button sheet.
    mm_button_sheet = loadImage("menu_buttons.bmp");
    background2 = loadImage("MainMenuBgTitle.png");

    //Load the options menu.
    optionsInit();

    //Load the controls menu
    controlsInit();


    //We initialized! Return true.
    return true;

}//end FUNCTION - mainInit


//mainCleanUp - The basic cleanup function that frees only entities used within the main menu.
//              Used if the game has started and cleaned up the other aspects of SDL before returning.
//              Called in OnCleanup
void mainCleanUp(){

    SDL_FreeSurface(background2);
    SDL_FreeSurface(mm_button_sheet);
    SDL_FreeSurface(surface);
    MMSoundCleanup();
    optionsCleanUp();
    controlsCleanUp();

}//end FUNCTION - mainCleanUp

//mainCompleteCleanUp - Bigger cleanup function.
//                      This function is called if the game has not started, which requires the main menu to clean up extra aspects of SDL.
//                      Called in MainMenu and FileMenu
void mainCompleteCleanUp(){

    SDL_FreeSurface(background2);
    SDL_FreeSurface(surface);
    SDL_FreeSurface(mm_button_sheet);
    MMSoundCleanup();
    buttonSoundCleanUp();
    mixerCleanUp();
    optionsCleanUp();
    controlsCleanUp();


}//end FUNCTION - mainCompleteCleanUp


