#include "enemy.h"
#include <SDL_rotozoom.h>
#include <iostream>
#include <math.h>
#include "endgame.h"
#include "damageNumbers.h"
#include <SDL_mixer.h>
using namespace std;

/*This class deals with the final boss of our first level. He still uses much of the same functionality of the 'mad mask' enemy.
  He does, however, have many unique traits of his own. His first ability is to shoot bullets at the player, spawning 'bad bullets'.
  He can also spawn lesser clones of himself. These clones function exactly like the 'mad mask' enemy, but they have a different sprite.
  This class also handles the beginning intro of the boss and the first part of the endgame state. Dealing with him not being hurt in the intro
  was done by initializing many of his stats to odd values. Some of that happens here, but some of it also happens in the 'load level' function.
*/

boss::boss()
{
    this->stunFrames = 0;
    this->knockback = 0;
    this->damageDisplay = 0;
    this->numCollisions = 0;
    this->state = -1;
    this->AnimState = 0;
    this->dir = 1;
    this->x = 0;
    this->stunFrames = 999;
    this->justHit = true;
    this->cutscene = true;
    this->teleDir = 0;
}

void boss::AI(LPM_Entity *other, hitbox box, SDL_Surface* Surf_Display, double scaling_factor_W, double scaling_factor_H)
    {
        //These two if/else blocks allow the boss to scroll off the screen and return on the other side
        //This was done to prevent a game state in which winning would be impossible due to the boss being far off screen
        if(this->X > 640 * scaling_factor_W) this->X = 40*scaling_factor_W;
        else if(this->X <= 0) this->X = 600*scaling_factor_W;

        if(this->Y > 440 * scaling_factor_H) this->Y = 40*scaling_factor_H;
        else if (this->Y <= 0) this->Y = 440*scaling_factor_H;


        /*Check to see if he has died. If he has, start the endgame cinematic
          The 'cutscene' flag is used because we initialize his hp to a value that is less than zero. This is done to prevent
          the player from shooting him before the fight actually starts, as the bullets do not collide with entities whose HP
          is less than or equal to zero.
        */
        if(!this->cutscene && this->HP <= 0)
        {
            Mix_HaltMusic();
            SDL_Surface *background = LPM_Surface::OnLoad("MainMenuBg.png");
            int z = 0;
            this->X = (Surf_Display->w / 2) - (100*scaling_factor_W);
            this->Y = (Surf_Display->h / 2) - (200*scaling_factor_H);
            this->Width *= 4*scaling_factor_W;
            this->Height *= 4*scaling_factor_H;
            this->Surf_Entity = zoomSurface (this->Surf_Entity, 4*scaling_factor_W, 4*scaling_factor_H, 1);
            SDL_Rect offset;
            offset.x = 0;
            offset.y = 0;

            //This is the actual cinematic itself. It plays in slow motion due to the large constant value.
            while(z < 600000000*2)
            {
                if((z % (2*600000000/10)) == 0)
                {
                    SDL_BlitSurface(background, NULL, Surf_Display, &offset);
                    if(this->Anim_Control.CurrentFrame != 9) this->Anim_Control.OnAnimate();
                    this->drawHitbox(Surf_Display, false);
                    SDL_Flip(Surf_Display);
                }
                z++;
            }
            this->die(Surf_Display);
            endgame(Surf_Display, true);

        }


        //These next two blocks deal with the creation of bad bullets and clones
        if(this->state > 1 && (rand() % 120 == 0) && enemy::enemyList.size() <= 10)
        {
            madmask *tempMask = new madmask();
            tempMask->OnLoad("MaskSpawn.png", 64*scaling_factor_W, 64*scaling_factor_H, 8);
            tempMask->HP = 10;
            tempMask->X = this->X + (rand() % 76);
            tempMask->Y = this->Y + (rand() % 76);
            tempMask->enemyBox.hitSurface = LPM_Surface::OnLoad("red.png");
            tempMask->index = enemy::enemyList.size();
            tempMask->state = 2;
            enemy::enemyList.push_back(tempMask);
        }
        if(this->state > 1 && (bullet::bulletList.size() < 20) && rand() % 60 == 0)
        {
            badBullet *tempBullet = new badBullet();
            if(this->X > other->X) tempBullet->isFacingLeft = true;
            else tempBullet->isFacingLeft = false;
            tempBullet->OnLoad("badBullet.png", (45*scaling_factor_W), (45*scaling_factor_H), 3);
            tempBullet->X = this->X;
            tempBullet->Y = this->Y;
            tempBullet->enemyBox.hitSurface = LPM_Surface::OnLoad("red.png");
            tempBullet->index = bullet::bulletList.size();
            bullet::bulletList.push_back(tempBullet);
        }

        //These are the default hit-stun clauses used by enemies
        if(this->knockback > 0) this->hitStun(other, scaling_factor_W);
        else if(!cutscene && this->stunFrames > 0) this->stunFrames--;
        else{
            //Within this block, the different AI states are all handled

            //In state 1, he vibrates angrily like one of the mad masks
            if(this->state == 1)
            {
                this->Y += sin(this->X);
                this->X += cos(this->Y);
                if(this->enemyBox.distance(this->X, this->Y, other->X, other->Y) < 200)
                    this->state = 3;
            }
            //In state two, he rushes at the player while randomly zig-zagging up and down
            else if(this->state == 2)
            {

                this->knockback = 0;
                if(this->X < other->X)
                    {
                        this->X += (1*scaling_factor_W);
                        this->dir = 2;
                    }
                else
                {
                        this->X -= (1*scaling_factor_W);
                        this->dir = 1;
                }

                if((int)(this->X / scaling_factor_W) % 3 == 0){
                    this->Y += ((pow(-1, this->dir))*20*sin(this->X / scaling_factor_W))*scaling_factor_H;
                }

                if(this->enemyBox.distance(this->X, other->X, this->Y, other->Y) <= (100*scaling_factor_W))
                    {
                        this->state = 3;
                    }
            }
            //In state 3, he retreats back to a safe distance
            else if(this->state == 3)
            {
                this->knockback = 0;
                if(this->X > other->X) this->X += (1*scaling_factor_W);
                else this->X -= (1*scaling_factor_W);
                if(this->Y < other->Y) this->Y += (1*scaling_factor_H);
                else this->Y -= (1*scaling_factor_H);


                if(this->enemyBox.distance(this->X, other->X, this->Y, other->Y) > (300*scaling_factor_W))
                    {
                        this->state = 2;
                    }
            }
            //State -1 is the intro cinematic state
            else if (this->state == -1)
                {
                    /*Dialogue is handled by the 'damage numbers' class. The second line spawns halfway through the lifetime of
                      the first. Once the damage numbers list is empty, the dialogue has finished and the fight begins in earnest.
                    */
                    if(damageNumbers::numberList.size() == 0 && x != 9999999)
                    {
                        damageNumbers *tempNumber = new damageNumbers();
                        tempNumber->init(1.0, this->X - this->Width, this->Y - this->Height, 270*4);
                        tempNumber->index = damageNumbers::numberList.size();
                        tempNumber->toDisplay = TTF_RenderText_Solid(tempNumber->font, "HAHAHAHAHA!", {255, 0, 0});
                        damageNumbers::numberList.push_back(tempNumber);
                    }

                    if(x < damageNumbers::numberList[0]->frames) x++;
                    else if(x < 9999999)
                        {
                            damageNumbers *tempNumber2 = new damageNumbers();
                            tempNumber2->init(1.0, this->X + this->Width, this->Y + this->Height, 270*4);
                            tempNumber2->index = damageNumbers::numberList.size();
                            tempNumber2->toDisplay = TTF_RenderText_Solid(tempNumber2->font, "YOU HAVE NO HOPE!", {255, 0, 0});
                            damageNumbers::numberList.push_back(tempNumber2);
                            x = 9999999;
                        }
                    else if(damageNumbers::numberList.size() == 0)
                        {
                            playBBG();
                            this->stunFrames = 0;
                            this->justHit = false;
                            this->HP = 500;
                            this->state = 2;
                            this->cutscene = false;
                        }
                }

        }

        //The boss still hurts you on contact
        if((state != -1) && this->enemyBox.collisionCheck(box) && other->iFrames == 0 && this->stunFrames <= 0)
        {
                    if(other->HP>=1)other->HP-=1;
                    else other->HP = 0;
                    other->iFrames = 270;
        }
    }

//This boss has a unique way of dealing with hitstun. He teleports randomly either forward or backward by 100-200 units.
void boss :: hitStun(LPM_Entity *other, double scaling_factor_W)
{
    if(this->stunFrames > 0 && !(this->state == -1))
        {

            this->stunFrames = this->knockback = 0;
            if(this->state == 3) this->state = 2;
            else this->state = 3;
            this->teleDir = 100*scaling_factor_W + (rand() % 100*scaling_factor_W);
            if(rand() % 2 == 1)
            {
                this->X += teleDir;
            }
            else this->X -= teleDir;

        }
}
