#include "enemy.h"
#include "SDL.h"
#include "damageNumbers.h"
#include "UpgradeMenu.h"
#include <iostream>
using namespace std;

/*This class handles the mysterious hat merchant who dwells within the middle of the demo level, standing on a bed of energy crystals. He has some
  default text that displays if you press the attack button near him, informing the player that he can be interacted with by using enter. Pressing
  the enter key will bring up the upgrade menu, at which the player can grab a randomly generated hat. You can, however, only get one hat, and the
  merchant will not give you any more if you have over 100 max HP.
*/

//Constructor
//StunFrames, HP, and knockback are given these values so that the NPC does not interact with the player's attacks
npc::npc()
{
    this->HP = -1;
    this->stunFrames = 999;
    this->knockback = 999;
    this->damageDisplay = 0;
    this->numCollisions = 0;
    this->hasTalked = false;
    this->keystate = SDL_GetKeyState(NULL);
}

//AI function
void npc::AI(LPM_Entity *other, hitbox box, SDL_Surface* Surf_Display, double scaling_factor_W, double scaling_factor_H)
    {
        //Activate the dialogue text
        if(keystate[SDLK_a] && !this->hasTalked && this->enemyBox.collisionCheck(box))
        {
            damageNumbers *tempNumber = new damageNumbers();
            tempNumber->init(1.0, this->X, this->Y, 270);
            tempNumber->index = damageNumbers::numberList.size();
            tempNumber->toDisplay = TTF_RenderText_Solid(tempNumber->font, "Press enter to view my hats...or enter the portal!", {255, 255, 255});
            damageNumbers::numberList.push_back(tempNumber);
            this->hasTalked = true;
        }
        //Activate the upgrade menu
        else if(keystate[SDLK_RETURN] && !this->hasTalked && this->enemyBox.collisionCheck(box))
        {
            this->hasTalked = true;
            upgradeMenu(Surf_Display);
        }
        else if(!keystate[SDLK_RETURN] && !keystate[SDLK_a])
            this->hasTalked = false;

    }

