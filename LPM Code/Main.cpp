//Matthew Magnuson
//Last Edit: 11/15/2013 - Matt
//Main: The game launches from here. It handles the initialization of our file and main menus, calls the main menu, and
//      restarting the game if the user chooses to do so.

#include "CApp.h"
#include "UserPref.h"



//Creating global variables we declared extern in CApp.h. Too many globals.
int maxHP;
int game_running;
int file_menu_running;
bool Running;
bool active = true;
char* cur_file;
string char_name;
int cur_level;
int cur_hat;
int cur_wep;
int potion_flag;
int armor_flag;
double scaling_factor_W;
double scaling_factor_H;
float second_holder = 0;
float frame_num = 0;
float cur_time = 1;
float next_time = 1;
float time_counter = 0;
bool bossRoom = false;


//Declaring default values for screen size, along with the screen we'll be displaying on.
double screen_width = 640;//DEFAULT
double screen_height = 480;//DEFAULT
int screen_bpp = 32;
SDL_Surface *screen = NULL;

//Main - Runs the game! Read below.
int main(int argc, char* args[]){

    //Loads the users preset preferences (right now, just screen resolution) before we start the game.
    loadPreferences();

    //This while loop runs through the  various parts of our program, initially calling init functions for our main menu and
    //file menu, and then calls the main menu itself. It also initializes all of our character specific variables to their
    //default amount, to avoid any overlapping between save files.
    //The active flag is only set false if the user chooses to completely exit the game. If the user choose to return to the
    //main menu from the game, we essentially rerun the entire loop.

    while(active == true){
        //Initiaizing our character file variables.
        cur_hat = 0;
        cur_level = 0;
        cur_wep = 0;
        cur_file = NULL;
        char_name = "New Game";
        maxHP = 100;
        potion_flag = 0;
        armor_flag = 0;

        //settng variables for screen resolution
        scaling_factor_W = screen_width/640.0;
        scaling_factor_H = screen_height/480.0;

        //Set the various flags we use throughout the game to 0.
        //Running allows the main menu to run, game_running and main_menu_running tells our main menu how to handle cleanup.
        Running = true;
        game_running = 0;
        file_menu_running = 0;

        //Here, we declare the screen for use throughout the game.
        screen = SDL_SetVideoMode(screen_width, screen_height, screen_bpp, /*SDL_FULLSCREEN*/  SDL_HWSURFACE | SDL_DOUBLEBUF);


        //Call the init functions for our file menu, main menu, and our loot. Loads in images and sounds.
        initLoot();
        fileInit();
        mainInit();

        //Calls our main menu function, passing it the screen it needs to display on as a parameter.
        mainMenu(screen);

        //Free SDL! We're either exiting or restarting the game at this point, so this includes our cleanup efforts
        //before we restart the loop.
        SDL_Quit();

    }//end WHILE - active flag

    //WHY WAS SIX AFRAID OF SEVEN GUYS?
    return 789;

}//end FUNCTION - main
