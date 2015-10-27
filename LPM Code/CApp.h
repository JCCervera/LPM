#ifndef _CAPP_H_
    #define _CAPP_H_

#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <time.h>

#include "LPM_Surface.h"
#include "LPM_Event.h"
#include "LPM_Animation.h"
#include "LPM_Entity.h"
#include "LPM_Ground.h"
#include "platform.h"
#include "enemy.h"
#include "SoundPlayer.h"
#include "PauseMenu.h"
#include "LPM_Weapon.h"
#include "Save.h"
#include "Load.h"
#include "FileMenu.h"
#include "MainMenu.h"
#include "UpgradeMenu.h"
#include "damageNumbers.h"
#include "Potion.h"
#include "ResolutionManager.h"
#include "OptionsMenu.h"
#include "LootTable.h"
#include "Armor.h"
#include "ControlsMenu.h"

extern int maxHP;
extern bool Running;
extern int file_menu_running;
extern int game_running;
extern bool active;
extern string char_name;
extern int cur_level;
extern int cur_hat;
extern int cur_wep;
extern char* cur_file;
extern int potion_flag;
extern int armor_flag;
extern SDL_Surface* screen;
extern double screen_width;
extern double screen_height;
extern double scaling_factor_W;
extern double scaling_factor_H;
extern float cur_time;
extern float next_time;
extern float time_counter;
extern float frame_num;
extern float second_holder;
extern bool bossRoom;


class CApp : public LPM_Event {
private:

        SDL_Surface*    Surf_Display;//Window display
        SDL_Surface*    Surf_Backdrop;
        float SwordMotion;

        LPM_Ground      Background;//Background

        LPM_Ground      Ground;

        LPM_Weapon      Musket;

        LPM_Entity      Entity1;//Player 1
        LPM_Entity      Entity2;//Debug Entity 2

        Uint8           *keystate;
        int             currentHP, length, i, gunType;
        float           ratio, minY, maxY, trackX;
        const char*     name;
        bool            drawHitboxes, onPlatform, hasSwitched, bossMode;
        SDL_Surface*    Surf_Green;
        SDL_Surface*    Surf_Red;
        SDL_Surface*    Surf_Frame;
        TTF_Font        *font;
        SDL_Color       text_color;

        //UI text and visuals
        std::string     HPtext, maxText, HPDisplay, gunDisplay;
        std::stringstream out;
        SDL_Surface     *text, *gameover, *myGun;
        hitbox          playerBox;

        float Ascent;
        float DashDistance;
        bool  NoDash;

        //Variables for the sake of debugging
        platform        testPlatform;
        enemy           baseEnemy;
        madmask         testMask;

    public:
        CApp();//Main program
        CApp(char* fileName);//For when file passed from load

        int OnExecute();//Checks if OnInit went off properly
        float startTime;

    public:
        bool OnInit();//When program is first intiated

        void OnEvent(SDL_Event* Event);//When a player controlled Event goes off

        void OnExit();//When player exits the window

        void OnLoop();//What to keep looping in the game

        void OnRender();//Renders objects on the screen

        void OnCleanup();//Cleans up assests

        void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);//When a key is pressed
        void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);//When a key is let go
        void jump();

        std::vector<platform*> loadPlatforms(char* fileName);
        std::vector<enemy*> loadEnemies(char*fileName);

};

#endif
