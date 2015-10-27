//Last Edit: 10/23/2013 - Matt
//Armor - Similar to potion.cpp, armor.cpp creates a pickup of type armor that the player can pickup to improve their stats!
//        Still at a very basic level of implementation


#include <vector>
#include "CApp.h"
#include "Armor.h"
#include "Pickup.h"
#include <SDL_rotozoom.h>


//vector array to store all of our loots!
vector<Pickup> armor_array;
SDL_Surface* armor_sheet = NULL;


//spawnArmor - Takes in an x, y, our screen, and a type.
//             Create a piece of loot at that given position, based upon the type.
void spawnArmor(int x, int y, SDL_Surface* surf, int type){

    //Setting a pointer to the screen.
    SDL_Surface* Surf_Display = surf;
    SDL_Rect armor_clip;

    //Decide what armor we're going to spawn (currently they all use the same thumbnail, which
    //we're setting the thumbnail for with this switch)
    switch (type){

        case 1: armor_clip = setClip3(0, 0, 62*scaling_factor_W, 48*scaling_factor_H);
                break;
        case 2: armor_clip = setClip3(0, 0, 62*scaling_factor_W, 48*scaling_factor_H);
                break;
        case 3: armor_clip = setClip3(0, 0, 62*scaling_factor_W, 48*scaling_factor_H);
                break;
        case 4: armor_clip = setClip3(0, 0, 62*scaling_factor_W, 48*scaling_factor_H);
                break;
        case 5: armor_clip = setClip3(0, 0, 62*scaling_factor_W, 48*scaling_factor_H);
                break;
        case 6: armor_clip = setClip3(0, 0, 62*scaling_factor_W, 48*scaling_factor_H);
                break;
        case 7: armor_clip = setClip3(0, 0, 62*scaling_factor_W, 48*scaling_factor_H);
                break;
        default: return;

    }//end SWITCH

    //Now that we've got our thumbnail dimensions and position , construct the pickup, load the thumbnail,
    //set our armor type, and add it to our vector.
    Pickup armor(x,y,62*scaling_factor_W,48*scaling_factor_H, armor_clip);
    armor_sheet = loadImage3("armor1.png");
    armor.pickup_type = type;
    armor_array.push_back(armor);

    //Set the armor_flag to 1 so the rest of the program knows we exist and need to be rendered.
    armor_flag = 1;

}//end FUNCTION - spawnArmor

//updateArmor - Checks the hitbox for our armor (for collisions), descends it to the ground, and deletes it if necessary.
//              Called from LPM_OnLoop
void updateArmor( SDL_Surface* Surf_Display, hitbox hitbox, int cur_hp, int max_hp, LPM_Entity* Entity1){

    int i = 0;

    //Descend the armor towards the ground if necessary (if it spawns above the ground)
    descendArmor();

    //Loop through our armor vector to see if the player has collided with our item.
    while(i != armor_array.size()){

        armor_array.at(i).drawHitbox(Surf_Display);
        armor_array.at(i).showPickup(Surf_Display, armor_sheet);

        //If collision occurs, delete the armor thumbnail from the  ground and apply the armor to the player.
        if(armor_array.at(i).pickup_hitbox.collisionCheck(hitbox) == true){

             deleteArmor(i, Entity1);
             i--;

        }//end IF - hitbox collision

    i++;

    }//end WHILE

}//end FUNCTION - updateArmor


//armorExists - Checks to see if there's any armor in our vector (lets the game know what to render in LPM_OnLoop and LPM_OnRender)
bool armorExists(){

    if(armor_array.empty()){
        armor_flag = 0;
        return false;
    }//end IF

    return true;

}//end FUNCTION - armorExists


//descendArmor - If our armor is floating somewhere above the ground, slowly increment its y value so it moves towards the floor
void descendArmor(){
    int i = 0;

    //Loop through out vector of armor, seeing what needs to be descended and do so.
    while(i != armor_array.size()){

        armor_array.at(i).descend(415);
        i++;

    }//end WHILE

}//end FUNCTION - descendArmor


//moveArmor - Given a passed in integer direction (0 or 1), move our armor left or right
void moveArmor(int direction){
    int i = 0;

    //Loop through each piece of armor and move the given direction.
    while(i != armor_array.size()){

        armor_array.at(i).scroll(direction);
        i++;

    }//end WHILE

}//end FUNCTION - moveARMOR


//deleteArmor - We are passed the index in our vector that corresponds to the piece of armor that needs to be deleted, and delete the
//              loot icon on the screen for that piece of armor. We are also passed the pointer to Entity1 (the player character).
//              We change the player characters sprite sheet based on the piece of armor you picked up. We can also give the player
//              a slight stat boost. The armor you pick up, however, is not permanent yet. It will reset the next time you log into the
//              game, but, if you save, the stat bonuses will stay.
void deleteArmor(int index, LPM_Entity* Entity1){
    SDL_Surface* temp_armor;

    if (armor_array.at(index).pickup_type == 1){

        Entity1->OnLoad("PlayerAnim2-1.png", ((130.0*scaling_factor_W)*.75) , ((216.0*scaling_factor_H)*.75), 10);
        Entity1->Surf_Entity = zoomSurface(Entity1->Surf_Entity, .75, .75, 1);
        maxHP+= 20;


    }//end IF


    if (armor_array.at(index).pickup_type == 2){

        Entity1->OnLoad("PlayerAnim2-2.png", ((130.0*scaling_factor_W)*.75) , ((216.0*scaling_factor_H)*.75), 10);
        Entity1->Surf_Entity = zoomSurface(Entity1->Surf_Entity, .75, .75, 1);
        maxHP+= 30;

    }//end IF


    if (armor_array.at(index).pickup_type == 3){

        Entity1->OnLoad("PlayerAnim3.png", ((130.0*scaling_factor_W)*.75) , ((216.0*scaling_factor_H)*.75), 10);
        Entity1->Surf_Entity = zoomSurface(Entity1->Surf_Entity, .75, .75, 1);
        maxHP+= 40;

    }//end IF


    if (armor_array.at(index).pickup_type == 4){

        Entity1->OnLoad("PlayerAnim2-3.png", ((130.0*scaling_factor_W)*.75) , ((216.0*scaling_factor_H)*.75), 10);
        Entity1->Surf_Entity = zoomSurface(Entity1->Surf_Entity, .75, .75, 1);
        maxHP+= 25;

    }//end IF


    if (armor_array.at(index).pickup_type == 5){

       Entity1->OnLoad("PlayerAnim2-4.png", ((130.0*scaling_factor_W)*.75) , ((216.0*scaling_factor_H)*.75), 10);
        Entity1->Surf_Entity = zoomSurface(Entity1->Surf_Entity, .75, .75, 1);
        maxHP+= 20;

    }//end IF

    if (armor_array.at(index).pickup_type == 6){

        Entity1->OnLoad("PlayerAnim2-5.png", ((130.0*scaling_factor_W)*.75) , ((216.0*scaling_factor_H)*.75), 10);
        Entity1->Surf_Entity = zoomSurface(Entity1->Surf_Entity, .75, .75, 1);
        maxHP+= 20;

    }//end IF

    //delete the armor
    armor_array.erase(armor_array.begin()+index);


    //If there's no more armor in our array, set the flag to 0.
    if(!armorExists()){
        armor_flag = 0;
    }//end IF

}//end FUNCTION - deleteArmor


