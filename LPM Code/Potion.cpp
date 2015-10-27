//Last Edit: 11/16/2013
//Potion: Called from our loot table function, a potion is created by chance when an enemy dies

#include <vector>
#include "Pickup.h"
#include "CApp.h"

//We declare a vector of pickups to store all of the potions that appear on screen.
vector<Pickup> potion_array;
SDL_Surface* potion_sheet = NULL;

//makePotion - Creates a health potion upon enemy death!
//             Takes in the x and y position of the enemy that just died, along with a pointer
//             to our screen, and creates a potion there.
void makePotion(int x, int y, SDL_Surface* surf){

    //Sets a pointer to the screen for later rendering
    SDL_Surface* Surf_Display = surf;

    //Sets the area we're going to clip out of our sprite sheet, and creates a pickup object of the same dimension.
    SDL_Rect potion_clip = setClip3(0, 0, 80*scaling_factor_W, 64*scaling_factor_H);
    Pickup my_potion(x,y,64*scaling_factor_W,64*scaling_factor_H, potion_clip);

    //Loads the image of the potion from our file, and puts it in the array.
    potion_sheet = loadImage3("Health.png");
    potion_array.push_back(my_potion);

    //Finally, we set the potion_flag= 1, indicating to the rest of the program that there are potions on the screen
    //Primarily for use in onloop and onrender, so we know to both move and display the potion.
    potion_flag = 1;

}//end FUNCTION - makePotion

//updatePotion - Calls descend potion to move our potion towards the ground, then checks to see
//               if our hitbox and the players hitbox are colliding. If so, the player has picked up
//               the potion and they gain some hp.
int updatePotion( SDL_Surface* Surf_Display, hitbox hitbox, int cur_hp, int max_hp){
    int i = 0;

    //update our potions y value.
    descendPotion();

    //For each element in our potion vector
    while(i != potion_array.size()){

        //Display the potion on the screen and update its hitbox.
        potion_array.at(i).drawHitbox(Surf_Display);
        potion_array.at(i).showPickup(Surf_Display, potion_sheet);

        //if the player has collided with the potion, delete that potion from our vector and
        //increase the player's hp (if it isn't at max).
        if(potion_array.at(i).pickup_hitbox.collisionCheck(hitbox) == true){
             deletePotion(i);
             i--;
             cur_hp+= 20;
             if (cur_hp > max_hp)
                cur_hp =  max_hp;

        }//end IF - potion collision

        //move to the next potion
        i++;
    }//end IF - looping through potions

    //return our newly update hp count.
    return cur_hp;

}//end FUNCTION - updatePotion

//potionExists - Called by LPM_OnLoop to see if there are any potions that need to be rendered/moved on screen. Self Explanatory.
bool potionExists(){

    if(potion_array.empty()){
        potion_flag = 0;
        return false;
    }//end IF

    return true;

}//end FUNCTION - potionExists

//descendPotion - For each function in our vector, if they're not on the ground then make them fall towards the ground.
void descendPotion(){

    int i = 0;

    //loop through our potion vector and descend all the potions that need it.
    while(i != potion_array.size()){

        potion_array.at(i).descend(410);
        i++;

    }//end WHILE

}//end FUNCTION - descendPotion


//movePotion - Takes in an integer (direction) and moves the potion either left of right depending on that direction.
void movePotion(int direction){

    int i = 0;

    //loop through our potion vector, moving all the potions left or right as needed.
    while(i != potion_array.size()){

        potion_array.at(i).scroll(direction);
        i++;

    }//end WHILE

}//end FUNCTION - movePotion

//deletePotion - Once a collision of hitboxes is triggered, we delete the potion from our vector array.
//               We're passed the index of the vector array that has been collided with, and delete that specific potion.
void deletePotion(int index){

    potion_array.erase(potion_array.begin()+index);

    if(!potionExists()){
        potion_flag = 0;
    }//end IF

}//end FUNCTION - deletePotion
