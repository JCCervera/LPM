#include "CApp.h"
#include "endgame.h"

void CApp::OnRender() {

    out.str("");
    out << Entity1.HP;
    HPtext = out.str();
    out.str("");
    out << maxHP;
    maxText = out.str();

    HPDisplay = "HP:"+HPtext+"/"+maxText;

   //Location and size rectangles
    SDL_Rect location = {(150*scaling_factor_W),(20*scaling_factor_H),(600*scaling_factor_W),(400*scaling_factor_H)};
    SDL_Rect center = {(20*scaling_factor_W),(240*scaling_factor_H),(600*scaling_factor_W),(400*scaling_factor_H)};



    LPM_Surface::OnDraw(Surf_Display, Surf_Backdrop, 0, 0);

    //Draw the background
    if(!bossMode)Background.OnRender(Surf_Display, 240*scaling_factor_H);

    // Apply the text to the screen
    SDL_BlitSurface(text, NULL, Surf_Display, &location);


    location = {(25*scaling_factor_W),(50*scaling_factor_H),(600*scaling_factor_W),(400*scaling_factor_H)};
    //Draw some gun text~
    SDL_BlitSurface(myGun, NULL, Surf_Display, &location);

    //Draw the ground
    if(!bossMode)Ground.OnRender(Surf_Display, 350*scaling_factor_H);

    //Calculate length
    ratio = (float)Entity1.HP/(float)maxHP;
    length = (int)(ratio*100);

    //Update HP text
    out.str("");
    out << Entity1.HP;
    HPtext = out.str();
    out.str("");
    out << maxHP;
    maxText = out.str();
    HPDisplay = "HP:"+HPtext+"/"+maxText;
    SDL_FreeSurface(text);
    text = TTF_RenderText_Solid(font, HPDisplay.c_str(), text_color);
    currentHP = Entity1.HP;

    //Draw dead bar
    LPM_Surface::OnDraw(Surf_Display, Surf_Red, (26*scaling_factor_W), (26*scaling_factor_H), 0, 0, (100*scaling_factor_W), (24*scaling_factor_H));

    //Draw life bar
    LPM_Surface::OnDraw(Surf_Display, Surf_Green, (26*scaling_factor_W), (26*scaling_factor_H), 0, 0, (length*scaling_factor_W), (24*scaling_factor_H));

    //Draw frame
    LPM_Surface::OnDraw(Surf_Display, Surf_Frame, 0, 0);

    //Game over
    if(Entity1.HP == 0) endgame(Surf_Display, false);


    int i;
    //std::cerr << enemy::enemyList.size() << "\n";

    //Draw all the platforms
    for(i = 0; i < platform::platformList.size(); i++)
        {
            if(!platform::platformList[i]) continue;

            platform::platformList[i]->drawHitbox(Surf_Display, drawHitboxes);
        }

    //Draw all the enemies
    for(i = 0; i < enemy::enemyList.size(); i++)
        {
            if(!enemy::enemyList[i]) continue;

            enemy::enemyList[i]->drawHitbox(Surf_Display, drawHitboxes);
        }

    //Draw bullets
    for(i = 0; i < bullet::bulletList.size(); i++)
        {
            if(!bullet::bulletList[i]) continue;

            bullet::bulletList[i]->drawHitbox(Surf_Display, drawHitboxes);
        }



    Musket.OnRender(Surf_Display);

    //Draw the hitbox (debug only)
    if(Entity1.iFrames == 0 && drawHitboxes)
        {
            LPM_Surface::OnDraw(Surf_Display, playerBox.hitSurface, playerBox.X, playerBox.Y, 0, 0, playerBox.Width, playerBox.Height);
        }

    //Draw the player
    if((int)Entity1.iFrames % 3 == 0)
    {
        Entity1.OnRender(Surf_Display);
    }

    //Draw damage numbers
    for(i = 0; i < damageNumbers::numberList.size(); i++)
        {
            if(!damageNumbers::numberList[i]) continue;
            damageNumbers::numberList[i]->update(Surf_Display, scaling_factor_W, scaling_factor_H);
        }

    if(potion_flag == 1){
        Entity1.HP = updatePotion(Surf_Display, playerBox, Entity1.HP, maxHP);
    }
    if(armor_flag == 1){
        updateArmor(Surf_Display, playerBox, Entity1.HP, maxHP, &Entity1);
    }

    //Flip it
    SDL_Flip(Surf_Display);
}
