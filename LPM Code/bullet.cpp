#include "enemy.h"
#include "damageNumbers.h"
#include <iostream>
#include <math.h>
using namespace std;

std::vector<bullet*>     bullet::bulletList;

/*This class handles the creation and movement of bullets that are shot by the player. This is the default class from which the
  other shot types inherit. As such, it is only actually used to fire the un-charged versions of 'Charge Shot'. The other ammo
  types have their own classes.
*/

bullet::bullet()
{
    this->HP = -1;
    this->hasKilled = false;
}

//Function handles the bullet removing itself after it contacts with an enemy
void bullet::die()
{
    this->newCleanup();

    //Update the rest of the indices
    for(int i = 0; i < bullet::bulletList.size(); i++)
        {
            if(i > this->index) bullet::bulletList[i]->index--;
        }

    bullet::bulletList.erase(bullet::bulletList.begin() + this->index);
    delete this;
}


void bullet::AI(LPM_Entity *other, hitbox box, SDL_Surface* Surf_Display, double scaling_factor_W, double scaling_factor_H)
    {
        //Update the current position
        if(this->isFacingLeft) this->X -= (2*scaling_factor_W);
        else this->X += (2*scaling_factor_W);

        //Check if scrolled of screen
        if(this->enemyBox.distance(this->X, other->X, this->Y, other->Y) > (450*scaling_factor_W) || this->hasKilled)
        {
            this->die();
        }
        else if(!this->hasKilled) //The else is to make sure that we don't die twice when an enemy gets hit over 450 units away
        {
            for(int i = 0; i < enemy::enemyList.size(); i++)
                {
                    //Make sure the thing we're hitting exists
                    if(!enemy::enemyList[i] || i > enemy::enemyList.size())
                        continue;

                    //Handle collisions with enemies
                    if( i < enemy::enemyList.size() && enemy::enemyList[i]->enemyBox.collisionCheck(this->enemyBox) &&  !(enemy::enemyList[i]->HP < 0))
                    {
                        enemy::enemyList[i]->HP -= 1;
                        enemy::enemyList[i]->damageDisplay = 1;
                        enemy::enemyList[i]->numCollisions ++;
                        enemy::enemyList[i]->stunFrames = 180;
                        enemy::enemyList[i]->knockback = (2*scaling_factor_W);
                        damageNumbers *tempNumber = new damageNumbers();
                        tempNumber->init(1.0, this->X, this->Y, (270));
                        tempNumber->index = damageNumbers::numberList.size();
                        damageNumbers::numberList.push_back(tempNumber);
                        this->hasKilled = true;
                    }
                }
        }
    }
