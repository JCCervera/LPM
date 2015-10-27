//Last Edit: 11/16/2013 - Matt
//Upgrade Menu: Called from the pause menu whenever the user clicks the upgrade button.
//              Gives the user the option to buy on of many various hats, or to return.
//              NOT YET IMPLEMENTED. You can't actually buy anything yet.

#include "Button.h"
#include "CApp.h"
#include "Armor.h"

SDL_Surface* pause_button_sheet3 = NULL;
SDL_Surface* background3 = NULL;

using namespace std;

//upgradeInit - Initializes the images for our background and buttons
//              Called in LPM_OnInit
void upgradeInit(){

    pause_button_sheet3 = loadImage("shop_buttons.bmp");
    background3 = loadImage("ShopMenu.png");

}//end FUNCTION - upgradeInit

//upgradeCleanup - Frees all of the surfaces used in the upgrade menu.
//                 Called in LPM_OnCleanup
void upgradeCleanUp(){

    SDL_FreeSurface(background3);
    SDL_FreeSurface(pause_button_sheet3);

}//end FUNCTION - upgradeCleanup


//upgradeMenu - Runs the upgrade menu. Create buttons, display the buttons, and gives those buttons various properties.
//              As it currently stands, there is no interaction to be done other than to look at the hats and exit the window.
//              Takes in an sdl_surface (our screen).
void upgradeMenu(SDL_Surface* Surf_Display){


    //Clipping that image to individal rectangles (we need two: one for our default button, and one for the mouseover)
    SDL_Rect starhat_button_default = setClip(0, 0, 150*scaling_factor_W, 150*scaling_factor_H);
    SDL_Rect starhat_button_mouseover = setClip(0, 150*scaling_factor_H, 150*scaling_factor_W, 150*scaling_factor_H);
    SDL_Rect pinkhat_button_default = setClip(150*scaling_factor_W, 0, 150*scaling_factor_W, 150*scaling_factor_H);
    SDL_Rect pinkhat_button_mouseover = setClip(150*scaling_factor_W,150*scaling_factor_H, 150*scaling_factor_W, 150*scaling_factor_H);
    SDL_Rect thunderhat_button_default = setClip(300*scaling_factor_W, 0, 150*scaling_factor_W, 150*scaling_factor_H);
    SDL_Rect thunderhat_button_mouseover = setClip(300*scaling_factor_W, 150*scaling_factor_H, 150*scaling_factor_W, 150*scaling_factor_H);
    SDL_Rect heart_button_default = setClip(450*scaling_factor_W, 0, 150*scaling_factor_W, 150*scaling_factor_H);
    SDL_Rect heart_button_mouseover = setClip(450*scaling_factor_W, 150*scaling_factor_H, 150*scaling_factor_W, 150*scaling_factor_H);
    SDL_Rect nohats_button_default = setClip(0, 300*scaling_factor_H, 450*scaling_factor_W, 50*scaling_factor_H);
    SDL_Rect nohats_button_mouseover = setClip(0, 350*scaling_factor_H, 450*scaling_factor_W, 50*scaling_factor_H);

    //Constructing the buttons, passing them the images, position, and size variables.
    Button starhat_button(250*scaling_factor_W, 200*scaling_factor_H, 150*scaling_factor_W, 150*scaling_factor_H, starhat_button_default, starhat_button_mouseover);
    Button pinkhat_button(250*scaling_factor_W, 350*scaling_factor_H, 150*scaling_factor_W, 150*scaling_factor_H, pinkhat_button_default, pinkhat_button_mouseover);
    Button thunderhat_button(400*scaling_factor_W, 200*scaling_factor_H, 150*scaling_factor_W, 150*scaling_factor_H, thunderhat_button_default, thunderhat_button_mouseover);
    Button heart_button(400*scaling_factor_W, 350*scaling_factor_H, 150*scaling_factor_W, 150*scaling_factor_H, heart_button_default, heart_button_mouseover);
    Button nohats_button(200*scaling_factor_W, 130*scaling_factor_H, 450*scaling_factor_W, 50*scaling_factor_H, nohats_button_default, nohats_button_mouseover);

    //Offset values (these are necessary in SDL when we call the BlitSurface function later)
    SDL_Rect offset;
    offset.x = 0;
    offset.y = 0;
    button_mouse_flag = 0;

    //Our loop that runs the upgrades menu.
    //It Polls for events, and renders the buttons onto the screen.
    while(1){

        //if there was an event.
        if(SDL_PollEvent(&mouse_event)){

            //Handle events for the star hat button! If the user clicks on the star hat, they get an arbitrary,free random hat!
            //Only one free hat per playthrough (decided by the maxhp <= 100 check)
            //This will be changed later to have a currency attached to it).
            starhat_button.handleEvents();
            if(button_mouse_flag == 1){
                if(maxHP <= 100)spawnArmor(640*scaling_factor_W/2, 480*scaling_factor_H/2, Surf_Display, 2);
                    playButtonClick();
                button_mouse_flag = 0;
                break;
            }//end IF - starhat

            //Handle events for the pink hat button! If the user clicks on the star hat, they get an arbitrary,free hat!
            //Only one free hat per playthrough (decided by the maxhp <= 100 check)
            //This will be changed later to have a currency attached to it).
            pinkhat_button.handleEvents();
            if(button_mouse_flag == 1){
                if(maxHP <= 100)spawnArmor(640*scaling_factor_W/2, 480*scaling_factor_H/2, Surf_Display, 3);
                playButtonClick();
                button_mouse_flag = 0;
                break;
            }//end IF - pinkhat

            //Handle events for the thunder hat button! If the user clicks on the star hat, they get an arbitrary,free random hat!
            //Only one free hat per playthrough (decided by the maxhp <= 100 check)
            //This will be changed later to have a currency attached to it).
            thunderhat_button.handleEvents();
            if(button_mouse_flag == 1){
                if(maxHP <= 100)spawnArmor(640*scaling_factor_W/2, 480*scaling_factor_H/2, Surf_Display, 4);
                playButtonClick();
                button_mouse_flag = 0;
                break;
            }//end IF -thunderhat

            //Handle events for the heart hat button! If the user clicks on the star hat, they get an arbitrary,free random hat!
            //Only one free hat per playthrough (decided by the maxhp <= 100 check)
            //This will be changed later to have a currency attached to it).
            heart_button.handleEvents();
            if(button_mouse_flag == 1){
                if(maxHP <= 100)spawnArmor(640*scaling_factor_W/2, 480*scaling_factor_H/2, Surf_Display, 5);
                playButtonClick();
                button_mouse_flag = 0;
                break;
            }//end IF - heartbutton

            //Handle events for the back button.
            //If the user clicks the button, we return to the calling function (right now, the pause menu).
            nohats_button.handleEvents();
            if(button_mouse_flag == 1){
                playButtonClick();
                button_mouse_flag = 0;
                break;
            }//end IF - nohats(return)

            //If the user X's out of the window, we quit the program.
            if(mouse_event.type == SDL_QUIT){
                Running = false;
                active = false;
                break;
            }//end IF - SDL_QUIT

        }//end IF - Event Polling


        //Display our background and render the buttons onto the screen.
        SDL_BlitSurface(background3, NULL, Surf_Display, &offset);
        starhat_button.showButton(Surf_Display, pause_button_sheet3);
        pinkhat_button.showButton(Surf_Display, pause_button_sheet3);
        thunderhat_button.showButton(Surf_Display, pause_button_sheet3);
        heart_button.showButton(Surf_Display, pause_button_sheet3);
        nohats_button.showButton(Surf_Display, pause_button_sheet3);
        if(SDL_Flip(Surf_Display) == -1)
            break;



    }//end WHILE

    return;

}//end FUNCTION - upgradeMenu


