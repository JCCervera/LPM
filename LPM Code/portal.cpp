#include "enemy.h"
#include <iostream>
#include <math.h>
using namespace std;

/*This class is used to handle the blue portal at the end of the level that warps the player to the boss room. It works by setting
  a flag that is checked in the 'onLoop' function. The player interacts with it by pressing the enter key.
*/

//Variable to check in onLoop
int portal::level = 1;

//Constructor
//As with NPC, values are set strangely to avoid interaction with player attacks
portal::portal()
{
    this->HP = -1;
    this->stunFrames = 999;
    this->knockback = 999;
    this->damageDisplay = 0;
    this->numCollisions = 0;
    this->keystate = SDL_GetKeyState(NULL);
}

//AI
void portal::AI(LPM_Entity *other, hitbox box, SDL_Surface* Surf_Display, double scaling_factor_W, double scaling_factor_H)
    {
        //Activate the warp sequence
        if(keystate[SDLK_RETURN] && !this->hasTalked && this->enemyBox.collisionCheck(box))
        {
            this->hasTalked = true;
            portal::level = 2;
        }
        else if(!keystate[SDLK_RETURN] && !keystate[SDLK_a])
            this->hasTalked = false;
    }

