#include "enemy.h"
#include "damageNumbers.h"
#include <iostream>
#include <math.h>
using namespace std;

/*This class handles one of the alternate ammunition types. The 'sin(x) shot' fires two bullets at once that move in a sin wave
  pattern. Each bullet does minimal damage, but the wide angle is useful for keeping large amounts of enemies at bay.
*/

//Constructor
sinShot::sinShot()
{
    this->HP = -1;
}

//Movement functions
void sinShot::AI(LPM_Entity *other, hitbox box, SDL_Surface* Surf_Display, double scaling_factor_W, double scaling_factor_H)
    {
        //Move the bullet in the direction it was shot
        if(this->isFacingLeft) this->X -= 2*scaling_factor_W;
        else this->X += 2*scaling_factor_W;

        //Have the bullet go through its wave pattern
        if((int)(this->X / scaling_factor_W) % 3 == 0){
                this->Y += ((pow(-1, this->dir))*20*sin(this->X / scaling_factor_W))*scaling_factor_H;
        }

        //Check if scrolled of screen
        if(this->enemyBox.distance(this->X, other->X, this->Y, other->Y) > (450*scaling_factor_W) || this->hasKilled)
        {
            this->die();
        }
        else if(!this->hasKilled) //The else is to make sure that we don't die twice when an enemy gets hit over 450 units away
        {
            //Check the enemies for a hit
            for(int i = 0; i < enemy::enemyList.size(); i++)
                {
                    //Make sure the enemy we're on exists
                    if(!enemy::enemyList[i] || i > enemy::enemyList.size())
                        continue;

                    //Deal with actually damaging an enemy
                    if( i < enemy::enemyList.size() && enemy::enemyList[i]->enemyBox.collisionCheck(this->enemyBox) &&  !(enemy::enemyList[i]->HP < 0))
                    {
                        enemy::enemyList[i]->HP -= 1;
                        enemy::enemyList[i]->damageDisplay = 1;
                        enemy::enemyList[i]->numCollisions ++;
                        enemy::enemyList[i]->stunFrames = 180;
                        enemy::enemyList[i]->knockback = (2*scaling_factor_W);
                        damageNumbers *tempNumber = new damageNumbers();
                        tempNumber->init(1.0, this->X, this->Y, 270);
                        tempNumber->index = damageNumbers::numberList.size();
                        damageNumbers::numberList.push_back(tempNumber);
                        this->hasKilled = true;
                    }
                }
        }
    }
