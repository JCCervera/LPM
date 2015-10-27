//Last Edit: 11/16/2013 - Matt
//Save Game: Writes relevant, current information to the character's file when the function is called.
//           Currently, the variables we monitor and update in the save file are:
//           CHAR_NAME, maxHP, CUR_LEVEL, CUR_HAT, CUR_WEP.
//           We also write the character's name to the file to act as an identifier when saving/loading.

#include "CApp.h"
using namespace std;

//saveGame - Saves the various variables we use to store character/level information into an output file.
//           Called from the pause menu when the user clicks the save button.
void saveGame(){

    //Declaring and assigning our output file. - we need to grab this from a global.
    ofstream ofp;
    ofp.open (cur_file);

    //Save our players name, maxHP, current level, current hat, and current weapon (not all of these variables are used yet in the game).
    ofp<< "CHAR_NAME "<< char_name<< endl;
    ofp << "MAX_HP "<< maxHP<< endl;
    ofp << "CUR_LEVEL "<< cur_level << endl;
    ofp << "CUR_HAT " << cur_hat<< endl;
    ofp << "CUR_WEP "<< cur_wep << endl;

    //Close our output file
    ofp.close();

}//end FUNCTION - saveGame
