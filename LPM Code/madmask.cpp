#include "enemy.h"
#include <iostream>
#include <math.h>
using namespace std;

/*Mad mask is a basic enemy in our game. It begins in a passive state, not doing anything until the player gets too close. Once
  the player gets close enough, the mask begins to shake violently. Once the player gets super close (or attacks the mask) it opens
  up to reveal its true form and relentlessly chases the player.
*/

//Constructor
madmask::madmask()
{
    this->stunFrames = 0;
    this->knockback = 0;
    this->damageDisplay = 0;
    this->numCollisions = 0;
    this->state = 0;
}

void madmask::AI(LPM_Entity *other, hitbox box, SDL_Surface* Surf_Display, double scaling_factor_W, double scaling_factor_H)
    {
        //Death function
        if(this->HP <= 0)
        {
            this->die(Surf_Display);
        }

        //Deal with hit stun, knock back, and AI
        if(this->knockback > 0) this->hitStun(other);
        else if(this->stunFrames > 0) this->stunFrames--;
        else{

            //State 0 is the passive state
            if(this->state == 0)
            {
                if(this->enemyBox.distance(this->X, this->Y, other->X, other->Y) < 400*scaling_factor_W)
                    this->state = 1;
                else if(this->HP < 10) //Activate when attacked
                    this->state = 2;
            }
            //State 1 is the violent shaking state
            else if(this->state == 1)
            {
                this->Y += sin(this->X);
                this->X += cos(this->Y);
                if(this->enemyBox.distance(this->X, this->Y, other->X, other->Y) < 200*scaling_factor_W)
                    this->state = 2;
                else if(this->HP < 10) //Activate when attacked
                    this->state = 2;
            }
            //State 2 is the attack state
            else if(this->state == 2)
            {
                this->AnimState = 1;
                this->knockback = 0;
                if(this->X < other->X) this->X += (1*scaling_factor_W);
                else this->X -= (1*scaling_factor_W);
                if(this->Y < other->Y) this->Y += (1*scaling_factor_H);
                else this->Y -= (1*scaling_factor_H);
            }

        }

        //Handle colliding with player
        if(this->enemyBox.collisionCheck(box) && other->iFrames == 0 && this->stunFrames <= 0)
        {
                    if(other->HP>=1)other->HP-=1;
                    else other->HP = 0;
                    other->iFrames = 270;
        }
    }
