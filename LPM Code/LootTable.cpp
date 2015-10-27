//Last Edit: 10/23/2013 - Matt
//Loot Table: Creates a basic loot table via a random number generator.

#include <stdlib.h>
#include <time.h>
#include "LootTable.h"
#include "CApp.h"
#include "Potion.h"
#include "Armor.h"

int temp;

//initLoot - called from LPM_OnInit, simply seeds the random number generator.
void initLoot(){
    srand (time(NULL));
}//end FUNCTION - initLoot


//rollLoot - Rolls a random number, 1 to 1000, and chooses what to drop from our monsters accordingly.
void rollLoot(int x, int y, SDL_Surface* Surf_Display){

    //If we are in the boss room, nothing drops
    if(bossRoom) return;

    //Roll 1-1000
    temp = rand() % 1000+1;

    //25% of the time we're going to drop a health pickup
    if(temp < 250)
        spawnLoot(1, x, y, Surf_Display);

    //Currently we only give armor via the NPC. This if statement can be updated, however, to allow
    //the hats to drop off a dying enemy.
    /*
    else if (temp < 350){
        temp = rand() % 6+2;
        spawnLoot(temp, x, y, Surf_Display);
    }//end ELSE
    */
    //if its 250+, no loot (yet)
    else{}

}//end FUNCTION - rollLoot


//spawnLoot - we're passed a type, x, y, and the screen.
//            We use a switch to identify the type and spawn the appropriate loot, and pass the other
//            variables to their respective creation functions.
void spawnLoot(int type, int x, int y, SDL_Surface* Surf_Display){

    //If type = 1 spawn a potion. Anything else, let's make some cool armor!
    switch (type){
        case 1: makePotion(x, y, Surf_Display);
                break;
        case 2: spawnArmor(x, y, Surf_Display, 1);
                break;
        case 3: spawnArmor(x, y, Surf_Display, 2);
                break;
        case 4: spawnArmor(x, y, Surf_Display, 3);
                break;
        case 5: spawnArmor(x, y, Surf_Display, 4);
                break;
        case 6: spawnArmor(x, y, Surf_Display, 5);
                break;
        case 7: spawnArmor(x, y, Surf_Display, 6);
        default: break;


    }//end SWITCH


}//end FUNCTION - spawnloot
