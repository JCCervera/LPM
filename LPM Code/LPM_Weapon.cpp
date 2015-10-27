#include "LPM_Weapon.h"
#include "damageNumbers.h"


LPM_Weapon::LPM_Weapon(){
     Surf_Weapon = NULL;

     X = 0.0f;
     Y = 0.0f;

     Form = 'G'; // G is for Gun, S is for Sword

     Width = Height = 0;

     AnimState = 0;

     changeReload = false;

     hasSwung = false;

     comboNum = 0;

}

bool LPM_Weapon::OnLoad(char* File, double Width, double Height, int MaxFrames) {
    //Load it and check it
    if((Surf_Weapon = LPM_Surface::OnLoad(File)) == NULL) {
        return false;
    }
    //Set the parameters
    this->Width = Width;
    this->Height = Height;

    //Give the animation control the maximum amount of animation frames
    Anim_Control.MaxFrames = MaxFrames;

    Weapon_Box.update(X, Y, this->Width, this->Height);

    return true;
}

void LPM_Weapon::OnLoop() {
    Anim_Control.OnAnimate();
}
void LPM_Weapon::OnHit() {
    for(int i = 0; i < enemy::enemyList.size(); i++)
                {

                    if(!enemy::enemyList[i] || i > enemy::enemyList.size())
                        continue;

                    if(i < enemy::enemyList.size() && enemy::enemyList[i]->enemyBox.collisionCheck(Weapon_Box) && !enemy::enemyList[i]->justHit)
                    {
                        //Input the characteristic of an enemy being hit
                        enemy::enemyList[i]->HP -= 5;
                        enemy::enemyList[i]->damageDisplay = 5;
                        enemy::enemyList[i]->numCollisions ++;
                        enemy::enemyList[i]->stunFrames = 180;
                        enemy::enemyList[i]->knockback = 2;
                        enemy::enemyList[i]->justHit = true;
                        damageNumbers *tempNumber = new damageNumbers();
                        tempNumber->init(5.0, this->X, this->Y, 270);
                        tempNumber->index = damageNumbers::numberList.size();
                        damageNumbers::numberList.push_back(tempNumber);

                    }
                }
}

void LPM_Weapon::OnRender(SDL_Surface* Surf_Display){
    //First check if they exist
    if(Surf_Weapon == NULL || Surf_Display == NULL) return;

    //Draw them using special draw for animation purposes.
    //Sections off each frame, and AnimState traverse the rows of animations
    //Use the current frame to make sure you are drawing the correct frame
    LPM_Surface::OnDraw(Surf_Display, Surf_Weapon, X, Y, AnimState * Width, Anim_Control.GetCurrentFrame()*Height, Width, Height);
    Weapon_Box.update(X, Y, Width, Height);
}

void LPM_Weapon::OnCleanup() {
    if(Surf_Weapon) {
        SDL_FreeSurface(Surf_Weapon);
    }

    Surf_Weapon = NULL;
}

void LPM_Weapon::InitiatePlacement(int Ex, int Ey, double scaling_factor_W, double scaling_factor_H){
    X = Ex - (15* scaling_factor_W);
    Y = Ey - (25* scaling_factor_H);
}

void LPM_Weapon::changeForm(){
    if(Form == 'G'){
        AnimState = 1;
        if(Anim_Control.CurrentFrame == Anim_Control.MaxFrames-1){
            AnimState = 2;
            Form = 'S';
            return;
        }
    }
    if(Form == 'S'){
        Anim_Control.FrameInc = -1;
        AnimState = 1;
        if(Anim_Control.CurrentFrame == 0){
            AnimState = 0;
            Form = 'G';
            Anim_Control.FrameInc = 1;
            return;
        }
    }
}
