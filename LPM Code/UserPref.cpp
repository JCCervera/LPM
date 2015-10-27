//Last Edit: 10/22/2013
//User Pref: Saves the users resolution preferences for next launch.
//           NOTE:  You can manually edit the userpref.txt file with a text editor to change the resolution (if you
//                  make the resolution too big and can't click the buttons anymore, this is the solution for now).

#include "UserPref.h"
#include "CApp.h"


using namespace std;

//saveResolution - When the user changes their preferred resolution, we save these changes to a text file,
//                 and load them up upon launch next  time.
//                 Takes in the width and height of the changed screen.
void saveResolution(int width, int height){

    //open file, or create the file if it doesn't exit
    ofstream ofp;
    ofp.open ("userpref.txt");

    //write the screen width on line 1, screen height on line 2
    ofp << width << "\n" << height << endl;

    //close the file.
    ofp.close();

}//end FUNCTION - saveResolution

//loadPreferences - Add new pref functions as we go (maybe one for user controls next)
//                  Right now, all we call is loadresolution, which sets the width and height of the screen that the user has chosen.
void loadPreferences(){

    loadResolution();

}//end FUNCTION - loadPreferences

//loadResolution - Opens up our user preferences file, loads in the values for screen resolution, and closes the file. Simple!
void loadResolution(){

    //Opens an input stream, reads in the
    ifstream ifp;
    string temp;
    ifp.open("userpref.txt");

    //Getting the values and setting them for use by the game.
    ifp >> temp;
    screen_width = atoi(temp.c_str());
    ifp >> temp;
    screen_height = atoi(temp.c_str());

    //close our file
    ifp.close();

}//end FUNCTION - loadResolution

