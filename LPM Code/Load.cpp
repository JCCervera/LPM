//Matthew Magnuson
//Last Edit: 9/13/2013 - Matt
//Load Game -


#include "CApp.h"
void loadGame(){

    std::string line;
    std:: string temp;
    std::ifstream myfile;
    myfile.open(cur_file);

    if(myfile.is_open())
        {
            //Grab name
            myfile >> temp;
            myfile >> line;
            char_name = line.c_str();

            //Grab max HP
            myfile >> temp;
            myfile >> line;
            maxHP = atoi(line.c_str());
            //maxHP = 100;

            //Close file
            myfile.close();
            //return line;
        }
    else
        {
            //name = "DEFAULT";
            maxHP = 100;
            myfile.close();
            //return "New Game";
        }





}
