#include "enemy.h"
#include "damageNumbers.h"
#include <iostream>
#include <math.h>
using namespace std;

/*This is a class used to create bullets that come from the enemies. At the moment,the boss is the only enemy that actually
  fires bullets. Functionally, these are quite similar to the normal bullets. The only real difference is that they check for
  collisions with Entity1, rather than with the enemy array.
*/

//Constructor
//Not all values are accounted for here. Some are set on the fly at the time of creation
badBullet::badBullet()
{
    this->HP = -1;
    this->hasKilled = false;
}

//AI function
void badBullet::AI(LPM_Entity *other, hitbox box, SDL_Surface* Surf_Display, double scaling_factor_W, double scaling_factor_H)
    {
        //Animate
        this->Anim_Control.OnAnimate();

        //Change direction based on relation to player
        if(this->isFacingLeft) this->X -= (2*scaling_factor_W);
        else this->X += (2*scaling_factor_W);

        //Check if scrolled of screen
        if(this->enemyBox.distance(this->X, other->X, this->Y, other->Y) > (450*scaling_factor_W) || this->hasKilled)
        {
            this->die();
        }
        else if(!this->hasKilled) //The else is to make sure that we don't die twice when an enemy gets hit over 450 units away
        {
                    //Check collision and deal damage
                    if(box.collisionCheck(this->enemyBox) && other-> iFrames == 0)
                    {
                        other->HP -= 2;
                        if(other->HP < 0) other->HP = 0;
                        other->iFrames = 180;
                        this->hasKilled = true;
                    }

        }
    }
