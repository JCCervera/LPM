//Last Edit: 9/13/2013 - Matt
//File Menu



#include "CApp.h"
#include "Button.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <SDL_ttf.h>
using namespace std;

SDL_Surface* filemenu_button_sheet = NULL;
SDL_Surface* background5 = NULL;


//Initialize data
void fileInit(){
    filemenu_button_sheet = loadImage("menu_buttons.bmp");
    background5 = loadImage("MainMenuBg.png");
    file_menu_running = 1;
}

//Frees surfaces
void fileCleanUp(){
    SDL_FreeSurface(background5);
    SDL_FreeSurface(filemenu_button_sheet);
}

void fileMenu(SDL_Surface* Surf_Display){


    SDL_Rect location = {140*scaling_factor_W, 100*scaling_factor_H, 600*scaling_factor_W, 400*scaling_factor_H};
    SDL_Rect location1 = {140*scaling_factor_W, 220*scaling_factor_H, 600*scaling_factor_W, 400*scaling_factor_H};
    SDL_Rect location2 = {140*scaling_factor_W, 340*scaling_factor_H, 600*scaling_factor_W, 400*scaling_factor_H};

    //Clipping that image to individal rectangles (we need two: one for our default button, and one for the mouseover)
    SDL_Rect slot1_button_default = setClip(0, 350*scaling_factor_H, 100*scaling_factor_W, 50*scaling_factor_H);
    SDL_Rect slot1_button_mouseover = setClip(100*scaling_factor_W, 350*scaling_factor_H, 100*scaling_factor_W, 50*scaling_factor_H);
    SDL_Rect slot2_button_default = setClip(0, 350*scaling_factor_H, 100*scaling_factor_W, 50*scaling_factor_H);
    SDL_Rect slot2_button_mouseover = setClip(100*scaling_factor_W, 350*scaling_factor_H, 100*scaling_factor_W, 50*scaling_factor_H);
    SDL_Rect slot3_button_default = setClip(0, 350*scaling_factor_H, 100*scaling_factor_W, 50*scaling_factor_H);
    SDL_Rect slot3_button_mouseover = setClip(100*scaling_factor_W, 350*scaling_factor_H, 100*scaling_factor_W, 50*scaling_factor_H);
    SDL_Rect back_button_default = setClip(0, 150*scaling_factor_H, 100*scaling_factor_W, 50*scaling_factor_H);
    SDL_Rect back_button_mouseover = setClip(100*scaling_factor_W, 150*scaling_factor_H, 100*scaling_factor_W, 50*scaling_factor_H);

    //Making the button
    Button slot1_button(35*scaling_factor_W, 100*scaling_factor_H, 100*scaling_factor_W, 50*scaling_factor_H, slot1_button_default, slot1_button_mouseover);
    Button slot2_button(35*scaling_factor_W, 220*scaling_factor_H, 100*scaling_factor_W, 50*scaling_factor_H, slot2_button_default, slot2_button_mouseover);
    Button slot3_button(35*scaling_factor_W, 340*scaling_factor_H, 100*scaling_factor_W, 50*scaling_factor_H, slot3_button_default, slot3_button_mouseover);
    Button back_button(250*scaling_factor_W, 340*scaling_factor_H, 100*scaling_factor_W, 50*scaling_factor_H, back_button_default, back_button_mouseover);

    //Ken stuff

    //Initialize libraries to deal with text
    TTF_Init();
    TTF_Font *font;
    font = TTF_OpenFont("FreeSans.ttf", 24*scaling_factor_H);

    //Check that the font exists
    if (font == NULL)
    {
        cerr << "font";
        return;
    }

    //Load the file names
    string line1, line2, line3;
   line1 = loadName("file1.txt");
   line2 = loadName("file2.txt");
   line3 = loadName("file3.txt");
   SDL_Surface *text, *text1, *text2;
   SDL_Color text_color = {255, 0, 125};
   text = TTF_RenderText_Solid(font, line1.c_str(), text_color);
   text1 = TTF_RenderText_Solid(font, line2.c_str(), text_color);
   text2 = TTF_RenderText_Solid(font, line3.c_str(), text_color);
    //end ken stuff

    //Make a background
    SDL_Rect offset;
    offset.x = 0;
    offset.y = 0;

//Handle mouse input for the menu
    while(1){
        if(SDL_PollEvent(&mouse_event)){
            slot1_button.handleEvents();
            if(button_mouse_flag == 1){
                playButtonClick();
                game_running = 1;
                cur_file = "file1.txt";
                CApp LaserPoweredMustketGame("file1.txt");
                LaserPoweredMustketGame.OnExecute();
                button_mouse_flag = 0;
                break;
            }
            slot2_button.handleEvents();
            if(button_mouse_flag == 1){
                playButtonClick();
                game_running = 1;
                cur_file = "file2.txt";
                CApp LaserPoweredMustketGame("file2.txt");
                LaserPoweredMustketGame.OnExecute();
                button_mouse_flag = 0;
                break;

            }
            slot3_button.handleEvents();
            if(button_mouse_flag == 1){
                playButtonClick();
                game_running = 1;
                cur_file = "file3.txt";
                CApp LaserPoweredMustketGame("file3.txt");
                LaserPoweredMustketGame.OnExecute();
                button_mouse_flag = 0;
                break;
            }
            back_button.handleEvents();
            if(button_mouse_flag == 1){
                playButtonClick();
                button_mouse_flag = 0;
                break;
            }
            if(mouse_event.type == SDL_QUIT){
                if (game_running == 1){
                    Running = false;
                    active = false;
                }

                else{
                    Running = false;
                    active = false;
                    fileCleanUp();
                    mainCompleteCleanUp();
                }
                break;
            }
        }


        SDL_BlitSurface(background5, NULL, Surf_Display, &offset);
        SDL_BlitSurface(text, NULL, Surf_Display, &location);
        SDL_BlitSurface(text1, NULL, Surf_Display, &location1);
        SDL_BlitSurface(text2, NULL, Surf_Display, &location2);

        slot1_button.showButton(Surf_Display, filemenu_button_sheet);
        slot2_button.showButton(Surf_Display, filemenu_button_sheet);
        slot3_button.showButton(Surf_Display, filemenu_button_sheet);
        back_button.showButton(Surf_Display, filemenu_button_sheet);



       if(SDL_Flip(Surf_Display) == -1)
           break;



    }//end while
    return;

}

//Loads the name of the file
string loadName(char* fileName)
{
  string line;
  string temp;
  ifstream myfile;
  myfile.open(fileName);

  if(myfile.is_open())
    {
        myfile >> temp;
        myfile >> line;
        myfile.close();
        return line;
    }

  myfile.close();
  return "New Game";
}
