#include "enemy.h"
#include "damageNumbers.h"
#include <iostream>
#include <math.h>
using namespace std;

/*This class handles one of the alternate ammunition types. The 'shield shot' creates a bullet that spins around the player in a
  wide circle, striking enemies that come to close. Once three of these are on the screen, you can send them flying by shooting again.
*/

//Constructor
shieldShot::shieldShot()
{
    this->HP = -1;
    this->go = false;
    this->angle = 0;
}

//Movement functions
void shieldShot::AI(LPM_Entity *other, hitbox box, SDL_Surface* Surf_Display, double scaling_factor_W, double scaling_factor_H)
    {

        //The 'go' flag is used to check if the bullets are still in shield formation or if they have been released.
        if(!go){
        if(this->Y < box.Y - (50*scaling_factor_H))
            {
                //Correction for when the bullets are above the player
                this->Y += (1*scaling_factor_H);
                this->X += (5*cos(this->angle))*scaling_factor_W;
                this->angle += 0.05;
            }
        else if(this->Y > other->Y + box.Height-(10*scaling_factor_H))
            {
                //Correction for when the player is below the bullets
                this->Y -= (1*scaling_factor_H);
                this->X += (5*cos(this->angle))*scaling_factor_W;
                this->angle += 0.05;
            }
        else
            {
                //Equations for circular motion
                this->Y -= (5*sin(this->angle))*scaling_factor_H;
                this->X += (5*cos(this->angle))*scaling_factor_W;
                this->angle += 0.05;

            }
        }
        //Release the bullets in random directions
        else if(go)
            {
                this->Y -= (5*sin(this->angle))*scaling_factor_H;
                this->X += (5*cos(this->angle))*scaling_factor_W;
                this->angle += (rand() % 20) / 100;
            }

        //Check if scrolled of screen
        if(this->enemyBox.distance(this->X, other->X, this->Y, other->Y) > 450 || this->hasKilled)
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

                    //Handle damaging an enemy
                    if( i < enemy::enemyList.size() && enemy::enemyList[i]->enemyBox.collisionCheck(this->enemyBox) &&  !(enemy::enemyList[i]->HP < 0))
                    {
                        enemy::enemyList[i]->HP -= 1;
                        enemy::enemyList[i]->damageDisplay = 1;
                        enemy::enemyList[i]->numCollisions ++;
                        enemy::enemyList[i]->stunFrames = 180;
                        enemy::enemyList[i]->knockback = 2;
                        damageNumbers *tempNumber = new damageNumbers();
                        tempNumber->init(1.0, this->X, this->Y, 270);
                        tempNumber->index = damageNumbers::numberList.size();
                        damageNumbers::numberList.push_back(tempNumber);
                        this->hasKilled = true;
                    }
                }
        }
    }

