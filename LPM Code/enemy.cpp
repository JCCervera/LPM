#include "enemy.h"
#include "LootTable.h"
#include <iostream>

using namespace std;
std::vector<enemy*>     enemy::enemyList;

/*The default enemy class contains much of the data that is used in all of the different types of enemies. As it is, it functions
  as a dangerous but immobile enemy that is best avoided. We use this class to create hazards throughout the level that are best jumped over.
  In order to discourage players from simply destroying these enemies, they do a great deal of damage and rush to the player's current
  X position with great speed and accuracy.
*/

//Constructor
enemy :: enemy()
{
    this->justHit = false;
    this->damageDisplay = 0;
    this->stunFrames = 0;
    this->font = TTF_OpenFont("FreeSans.ttf", 24);
    this->numCollisions = 0;
    this->HP = 0;
    out.str("");
    out << this->HP;
    this->life = TTF_RenderText_Solid(this->font, out.str().c_str(), {255, 255, 255});
}

//Updates hit box, draws it (if we are drawing them), and render's the sprite
void enemy :: drawHitbox(SDL_Surface *display, bool isDraw)
{
    //Check location of hitbox.
    this->enemyBox.update(this->X, this->Y, this->Width, this->Height);

    //Display HP if debug mode is activated
    if(this->HP > 0)
    {
        this->out.str("");
        this->out << this->HP;
        this->location = {this->X,this->Y-50,600,400};
        SDL_FreeSurface(this->life);
        this->life = TTF_RenderText_Solid(this->font, out.str().c_str(), {255, 255, 255});
        SDL_BlitSurface(this->life, NULL, display, &this->location);
    }
    if(isDraw && this->stunFrames == 0) LPM_Surface::OnDraw(display, this->enemyBox.hitSurface, (int)this->enemyBox.X, (int)this->enemyBox.Y, 0, 0, (int)this->enemyBox.Width, (int)this->enemyBox.Height);

    //Render the sprite
    this->OnRender(display);
}

//Cleanup function. Uses both the hitbox and entity cleanup functions
void enemy :: newCleanup()
{
    this->enemyBox.onCleanup();
    this->OnCleanup();
}

//Deal with the enemy being moved because of the player pressing left or right.
void enemy :: moveUpdate(bool isLeft, double scaling_factor_W)
{
    if(isLeft) this-> X += (3*scaling_factor_W);
    else this-> X -= (3*scaling_factor_W);
}

//Kills the enemy and removes it from the list. Also has a chance to drop things.
void enemy :: die(SDL_Surface* Surf_Display)
{
    rollLoot(this->X, this->Y, Surf_Display);
    this->newCleanup();
    for(int i = 0; i < enemy::enemyList.size(); i++)
        {
            if(!enemy::enemyList[i]) continue;
            if(i > this->index) enemy::enemyList[i]->index--;
        }
    while(this->index > enemy::enemyList.size()) this->index--;
    enemy::enemyList.erase(enemy::enemyList.begin() + this->index);
    delete this;
}

//Handle the enemies being knocked back and frozen after being hit
void enemy :: hitStun(LPM_Entity *other)
{
    if(this->stunFrames > 0)
        {
            this->stunFrames --;
            if(this->X > other->X)
            {
                this->X += this->knockback;
                this->knockback -= .1;
            }
            else if(this->X < other->X)
            {
                this->X -= this->knockback;
                this->knockback -= .1;
            }
        }
}

//Handle movement and collisions with the player
void enemy :: AI(LPM_Entity *other, hitbox box, SDL_Surface* Surf_Display, double scaling_factor_W, double scaling_factor_H)
{
    this->hitStun(other);
    if(this->HP <= 0)
    {
        this->die(Surf_Display);
    }

    if(this->enemyBox.collisionCheck(box) && other->iFrames == 0)
        {
                    if(other->HP>=50)other->HP-=50;
                    else other->HP = 0;
                    other->iFrames = 270;
        }

}
