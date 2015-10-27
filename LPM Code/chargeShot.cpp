#include "enemy.h"
#include "damageNumbers.h"
#include <iostream>
using namespace std;

/*This class handles the creation, movement, and collisions that occur when you fire a 'charge shot' by holding the fire button
  down and releasing it a few seconds later. It inherits some of its functionality from the base class found in bullet.cpp
*/

//Constructor
//Most values are handled on creation
chargeShot::chargeShot()
{
    this->HP = -1;
}

void chargeShot::AI(LPM_Entity *other, hitbox box, SDL_Surface* Surf_Display, double scaling_factor_W, double scaling_factor_H)
    {
        /*Since the shot is meant to have a 'piercing' effect, it does not die on contact. This had an unintended effect of causing
          the bullet to hit individual enemies many times as is went off screen. In order to prevent this, the charge shot is given
          a set amount of 'iFrames'. While there are more than 0 of these, it does not hurt anything. This allows it to hit enemies
          only 1 or 2 times.
        */
        if (this->iFrames > 0) this->iFrames--;
        if(this->isFacingLeft) this->X -= 2;
        else this->X += 2;

        //Check if scrolled of screen
        if(this->enemyBox.distance(this->X, other->X, this->Y, other->Y) > 450)
        {
            this->die();
        }
        else if(this->iFrames == 0)
        {
            //Handle collisions with enemies
            for(int i = 0; i < enemy::enemyList.size(); i++)
                {
                    if(!enemy::enemyList[i] || i > enemy::enemyList.size())
                        continue;


                    if( i < enemy::enemyList.size() && enemy::enemyList[i]->enemyBox.collisionCheck(this->enemyBox) &&  !(enemy::enemyList[i]->HP < 0))
                    {
                        enemy::enemyList[i]->HP -= 5;
                        enemy::enemyList[i]->damageDisplay = 5;
                        enemy::enemyList[i]->stunFrames = 180;
                        enemy::enemyList[i]->knockback = 2;
                        this->iFrames = 50; //We don't want too many hits on the same guy
                        damageNumbers *tempNumber = new damageNumbers();
                        tempNumber->init(5.0, this->X, this->Y, 270);
                        tempNumber->index = damageNumbers::numberList.size();
                        damageNumbers::numberList.push_back(tempNumber);
                    }
                }
        }
    }
