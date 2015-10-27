#include "Button.h"
#include "CApp.h"

void endgame(SDL_Surface *Surf_Display, bool isWin){

//Declare sprite sheet
SDL_Surface* end_button_sheet = NULL;

//Declare location rectangle
SDL_Rect offset;
offset.x = 0;
offset.y = 0;

//Declare background
SDL_Surface *background;

//Figure out whether the boss was killed or the player died
if(isWin) background = loadImage("MainMenuBg.png");
else background = loadImage("GameOver.png");

//Set sprite clips
SDL_Rect back_button_default = setClip(0, 0, 200*scaling_factor_W, 70*scaling_factor_H);
SDL_Rect back_button_mouseover = setClip(0, 70*scaling_factor_H, 200*scaling_factor_W, 70*scaling_factor_H);
SDL_Rect quit_button_default = setClip(0, 140*scaling_factor_H, 200*scaling_factor_W, 70*scaling_factor_H);
SDL_Rect quit_button_mouseover = setClip(0, 210*scaling_factor_H, 200*scaling_factor_W, 70*scaling_factor_H);

//Set up buttons
end_button_sheet = loadImage("end_buttons.bmp");
Button back_button(220*scaling_factor_W, 200*scaling_factor_H, 200*scaling_factor_W, 70*scaling_factor_H, back_button_default, back_button_mouseover);
Button quit_button(220*scaling_factor_W, 300*scaling_factor_H, 200*scaling_factor_W, 70*scaling_factor_H, quit_button_default, quit_button_mouseover);

//Stay here until user input
 while(1){
        button_mouse_flag = 0;
        if(SDL_PollEvent(&mouse_event)){

          back_button.handleEvents();
            if(button_mouse_flag == 1){

                playButtonClick();
                game_running = 0;
                Running = false;
                button_mouse_flag = 0;
                SDL_FreeSurface(end_button_sheet);
                break;

            }//end IF - return to main

            quit_button.handleEvents();
            if(button_mouse_flag == 1){

                playButtonClick();
                button_mouse_flag = 0;
                active = false;
                Running = false;
                SDL_FreeSurface(end_button_sheet);
                break;

            }//end IF - quit

          if(mouse_event.type == SDL_QUIT){

                Running = false;
                active = false;
                SDL_FreeSurface(end_button_sheet);
                break;

            }//end IF - sdl quit

        }//end IF - event handling

        SDL_BlitSurface(background, NULL, Surf_Display, &offset);
        back_button.showButton(Surf_Display, end_button_sheet);
        quit_button.showButton(Surf_Display, end_button_sheet);
        SDL_Flip(Surf_Display);

 }
}
