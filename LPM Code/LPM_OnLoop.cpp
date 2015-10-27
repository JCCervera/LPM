#include "CApp.h"
#include "SoundPlayer.h"
#include <SDL_mixer.h>

void CApp::OnLoop() {

    if(portal::level == 2)
        {
            //If you entered the last boss room
            bossRoom = true;
            Mix_HaltMusic();
            loadBossSound();
            enemy::enemyList = loadEnemies("level2.txt");
            platform::platformList = loadPlatforms("level2.txt");
            Surf_Backdrop = LPM_Surface::OnLoad("MainMenuBg.png");
            Entity1.X = 0;
            bossMode = true;
            portal::level = -1;
        }
    //The sword weapon is not in use
    if(Musket.AnimState == 2 && !keystate[SDLK_a]) Musket.hasSwung = false;
    if(playerBox.distance(Musket.X, Entity1.X, Musket.Y, Entity1.Y) > 150*scaling_factor_W)
        {
            Musket.Anim_Control.CurrentFrame = 0;
            Musket.AnimState = 2;
            Musket.X = Entity1.X;
            SwordMotion = 0;
        }
    else if(Musket.hasSwung){
            if(Entity1.isFacingLeft){
                    Musket.X += (-SwordMotion);
            }
            else{
                    Musket.X += SwordMotion;
            }

            Musket.OnHit();
    }
     //FPS FUNCTION----------------------------------------
    if(time_counter == 0){
        cur_time = SDL_GetTicks();
        time_counter = 1;
        frame_num++;
    }
    else{
            next_time = SDL_GetTicks();
            time_counter = 0;
            second_holder += ((((next_time) - cur_time) / (1000.0)));
            frame_num++;
            if (second_holder >= 1){
                std:: stringstream fps;
                frame_num = frame_num / second_holder;
                fps << frame_num;
                fps.str("");
                second_holder = 0;
                frame_num = 0;
            }
        }


    //END FPS---------------------------------------------------------------

    if(Entity1.iFrames > 0) Entity1.iFrames--;


    //Loop function for Entity1 (just animates)
    Entity1.OnLoop();

    onPlatform = false;

    //Check if you're hitting a platform. Update minY accordingly
    for(i = 0; i < platform::platformList.size(); i++)
        {
            if(!platform::platformList[i])
                continue;
            if(playerBox.platformCheck(platform::platformList[i]->collider) && Ascent < 0)
                {
                    minY = platform::platformList[i]->collider.Y - Entity1.Height;
                    onPlatform = true;

                }

        }

    //Check flag
        if(!onPlatform)
            minY = (472*scaling_factor_H) - Entity1.Height;


    //Activate enemy AI
    for(i = 0; i < enemy::enemyList.size(); i++)
        {
            if(!enemy::enemyList[i])
                continue;
            enemy::enemyList[i]->AI(&Entity1, playerBox, Surf_Display, scaling_factor_W, scaling_factor_H);

            if(enemy::enemyList[i]->stunFrames == 0){
                   enemy::enemyList[i]->justHit = false;
            }
        }

    //Move bullets
    for(i = 0; i < bullet::bulletList.size(); i++)
        {
            if(!bullet::bulletList[i])
                continue;
            bullet::bulletList[i]->AI(&Entity1, playerBox, Surf_Display,  scaling_factor_W,  scaling_factor_H);
        }

    //Update player hitbox
    playerBox.update(Entity1.X, Entity1.Y, Entity1.Width, Entity1.Height);


    Musket.OnLoop();

    if(keystate[SDLK_s] && Musket.AnimState != 1 && !Musket.changeReload && Musket.AnimState < 6)
    {
       	Musket.changeForm();
        Musket.changeReload = true;
    }

    if(Musket.AnimState == 1 && !keystate[SDLK_s] && Musket.AnimState < 6)
    {
       	Musket.changeForm();
    }

	if(keystate[SDLK_SPACE])
    {
        jump();
        if(Entity1.Y >= minY || onPlatform)
        {
            playJump();
            Ascent = (2*scaling_factor_H);
        }

    }

    //Handle attacking
    if(keystate[SDLK_a] && ((Musket.Form == 'S' && !Musket.hasSwung) || (!Entity1.hasShot && bullet::bulletList.size() < 20)))
    {
        if(Musket.Form == 'G'){
        playShoot();
        if(gunType == 1)
            {
                bullet *tempBullet = new bullet();
                tempBullet->isFacingLeft = Entity1.isFacingLeft;
                if(!Entity1.isFacingLeft) {
                        tempBullet->OnLoad("bullet.png", (45*scaling_factor_W), (45*scaling_factor_H), 1);
                        tempBullet->X = Musket.X+Musket.Width;
                        tempBullet->Y = Entity1.Y+(Musket.Height/5);
                }
                else {
                        tempBullet->OnLoad("bullet.png", (45*scaling_factor_W), (45*scaling_factor_H), 1);
                        tempBullet->X = Musket.X;
                        tempBullet->Y = Entity1.Y+(Musket.Height/5);
                }

                tempBullet->enemyBox.hitSurface = LPM_Surface::OnLoad("blue.png");
                tempBullet->index = bullet::bulletList.size();
                bullet::bulletList.push_back(tempBullet);
            }
        else if(gunType == 2)
            {
                sinShot *tempBullet = new sinShot();
                tempBullet->isFacingLeft = Entity1.isFacingLeft;
                if(!Entity1.isFacingLeft) {
                        tempBullet->OnLoad("bullet.png", (45*scaling_factor_W), (45*scaling_factor_H), 1);
                        tempBullet->X = Musket.X+Musket.Width;
                        tempBullet->Y = Entity1.Y+(Musket.Height/5);
                        tempBullet->dir = 1;
                }
                else {
                        tempBullet->OnLoad("bullet.png", (45*scaling_factor_W), (45*scaling_factor_H), 1);
                        tempBullet->X = Musket.X;
                        tempBullet->Y = Entity1.Y+(Musket.Height/5);
                        tempBullet->dir = 1;
                }

                tempBullet->enemyBox.hitSurface = LPM_Surface::OnLoad("blue.png");
                tempBullet->index = bullet::bulletList.size();
                bullet::bulletList.push_back(tempBullet);

                sinShot *tempBullet2 = new sinShot();
                tempBullet2->isFacingLeft = Entity1.isFacingLeft;
                if(!Entity1.isFacingLeft) {
                        tempBullet2->OnLoad("bullet.png", (45*scaling_factor_W), (45*scaling_factor_H), 1);
                        tempBullet2->X = Musket.X+Musket.Width;
                        tempBullet2->Y = Entity1.Y+(Musket.Height/5);
                        tempBullet2->dir = 2;
                }
                else {
                        tempBullet2->OnLoad("bullet.png", (45*scaling_factor_W), (45*scaling_factor_H), 1);
                        tempBullet2->X = Musket.X;
                        tempBullet2->Y = Entity1.Y+(Musket.Height/5);
                        tempBullet2->dir = 2;
                }

                tempBullet2->enemyBox.hitSurface = LPM_Surface::OnLoad("blue.png");
                tempBullet2->index = bullet::bulletList.size();

                bullet::bulletList.push_back(tempBullet2);
            }
        else if(gunType == 3 && bullet::bulletList.size() < 3)
            {
                shieldShot *tempBullet = new shieldShot();
                tempBullet->isFacingLeft = Entity1.isFacingLeft;
                if(!Entity1.isFacingLeft) {
                        tempBullet->OnLoad("bullet.png", (45*scaling_factor_W), (45*scaling_factor_H), 1);
                        tempBullet->X = Entity1.X + Entity1.Width/2;
                        tempBullet->Y = Entity1.Y+Entity1.Height/2;
                }
                else {
                        tempBullet->OnLoad("bullet.png", (45*scaling_factor_W), (45*scaling_factor_H), 1);
                        tempBullet->X = Entity1.X + Entity1.Width/2;
                        tempBullet->Y = Entity1.Y+Entity1.Height/2;//(Musket.Height/5);
                }

                tempBullet->enemyBox.hitSurface = LPM_Surface::OnLoad("blue.png");
                tempBullet->index = bullet::bulletList.size();
                bullet::bulletList.push_back(tempBullet);
            }
        else if(gunType == 3 && bullet::bulletList.size() == 3 && !Entity1.hasShot)
        {
            for(int i = 0; i < bullet::bulletList.size(); i++)
            {
                bullet::bulletList[i]->go = true;
            }
            Entity1.hasShot = true;
        }

            Entity1.hasShot = true;
            if(Entity1.isFacingLeft){
                Musket.AnimState = 4;
            }
            else {Musket.AnimState = 3;}


        }

        if(Musket.Form == 'S' && Musket.comboNum < 4 && !Musket.hasSwung){
            playSword();
            SwordMotion = 4;
            Musket.hasSwung = true;
            if(Entity1.isFacingLeft)
                Musket.AnimState = 6;
            else
                Musket.AnimState = 5;
        }
    }

    if(keystate[SDLK_a] && Musket.Form == 'G') Entity1.chargeFrames++;


    //Weapon switching
    if(keystate[SDLK_w] && !hasSwitched)
        {
            gunType++;
            if(gunType > 3) gunType = 1;
            if(gunType == 1)
                {
                    SDL_FreeSurface(myGun);
                    gunDisplay = "Charge Shot";
                    myGun = TTF_RenderText_Solid(font, gunDisplay.c_str(), text_color);
                }
            else if(gunType == 2)
                {
                    SDL_FreeSurface(myGun);
                    gunDisplay = "Sin(X) Shot";
                    myGun = TTF_RenderText_Solid(font, gunDisplay.c_str(), text_color);
                }
            else if(gunType == 3)
                {
                    SDL_FreeSurface(myGun);
                    gunDisplay = "Shield Shot";
                    myGun = TTF_RenderText_Solid(font, gunDisplay.c_str(), text_color);
                }
            hasSwitched = true;
        }

    //Movement
    if(!bossMode && keystate[SDLK_LEFT]){
        Entity1.isFacingLeft = true;
        Entity1.Anim_Control.FrameRate = 100;
        Entity2.Anim_Control.FrameRate = 100;
        if((trackX >= (100*scaling_factor_W)) && (trackX <= (1600*scaling_factor_W)))
        {
            trackX -= (1*scaling_factor_W);
            Ground.X += (1*scaling_factor_W);
            Background.X += (.1*scaling_factor_W);

            //Update platforms
            for(int i = 0; i < platform::platformList.size(); i++)
            {
                if(!platform::platformList[i]) continue;

                platform::platformList[i]->moveUpdate(true, scaling_factor_W);
            }

            //Update enemies
            for(int i = 0; i < enemy::enemyList.size(); i++)
            {
                if(!enemy::enemyList[i]) continue;

                enemy::enemyList[i]->moveUpdate(true, scaling_factor_W);
            }

        }
        else if(trackX < (100*scaling_factor_W) && Entity1.X > 0)
        {
            Entity1.X-= (2*scaling_factor_W);
            Entity2.X-= (2*scaling_factor_W);
            Musket.X -= (2*scaling_factor_W);
            if(Entity1.X > (1*scaling_factor_W)) trackX -= (1*scaling_factor_W);
        }
        else if(trackX > (1600*scaling_factor_W))
        {
            if(Entity1.X > (250*scaling_factor_W))
            {
                Entity1.X -= (2*scaling_factor_W);
                Entity2.X -= (2*scaling_factor_W);
                Musket.X -= (2*scaling_factor_W);
            }
            trackX-= (1*scaling_factor_W);
        }


        Entity1.AnimState = 3;
        Entity2.AnimState = 2;
        if (potionExists() == true && trackX >= (100*scaling_factor_W) && trackX <= (1600*scaling_factor_W)){
            movePotion(1);
        }
        if (armorExists() == true && trackX >= (100*scaling_factor_W) && trackX <= (1600*scaling_factor_W)){
            moveArmor(1);
        }
    }

    else if(bossMode && keystate[SDLK_LEFT])
    {
        Entity1.AnimState = 3;
        Entity1.isFacingLeft = true;
        Entity1.Anim_Control.FrameRate = 100;
        if(Entity1.X > 0)
        {
            Entity1.X-= (2*scaling_factor_W);
            Entity2.X-= (2*scaling_factor_W);
            Musket.X -= (2*scaling_factor_W);
        }
    }

    if(!bossMode && keystate[SDLK_RIGHT]){
        Entity1.isFacingLeft = false;
        Entity1.Anim_Control.FrameRate = 100;
        Entity2.Anim_Control.FrameRate = 100;
        if(trackX >= (100*scaling_factor_W) && trackX <= (1600*scaling_factor_W))
        {
            Ground.X -= (1*scaling_factor_W);
            Background.X -= (.1*scaling_factor_W);
            trackX += (1*scaling_factor_W);
            //Update platforms
            for(int i = 0; i < platform::platformList.size(); i++)
            {
                if(!platform::platformList[i]) continue;

                platform::platformList[i]->moveUpdate(false, scaling_factor_W);
            }

            //Update enemies
            for(int i = 0; i < enemy::enemyList.size(); i++)
            {
                if(!enemy::enemyList[i]) continue;

                enemy::enemyList[i]->moveUpdate(false, scaling_factor_W);
            }
        }
        else if(trackX < (100*scaling_factor_W))
        {
            if(Entity1.X < (250*scaling_factor_W))
            {
                Entity1.X+= (2*scaling_factor_W);
                Entity2.X+= (2*scaling_factor_W);
                Musket.X+= (2*scaling_factor_W);
            }
            trackX += (1*scaling_factor_W);
        }
        else if(trackX >= (1600*scaling_factor_W) && Entity1.X < ((640 - 64)*scaling_factor_W))
        {
            Entity1.X += (2*scaling_factor_W);
            Entity2.X += (2*scaling_factor_W);
            Musket.X += (2*scaling_factor_W);
            if(Entity1.X < ((640 - 64)*scaling_factor_W)) trackX+= (1*scaling_factor_W);
        }

        Entity1.AnimState = 1;
        Entity2.AnimState = 3;
        if (potionExists() == true && trackX >= (100*scaling_factor_W) && trackX <= (1600*scaling_factor_W)){
            movePotion(2);
        }
        if (armorExists() == true && trackX >= (100*scaling_factor_W) && trackX <= (1600*scaling_factor_W)){
            moveArmor(2);
        }

    }
    else if(bossMode && keystate[SDLK_RIGHT])
    {
        Entity1.AnimState = 1;
        Entity1.isFacingLeft = false;
        Entity1.Anim_Control.FrameRate = 100;
        if(Entity1.X <= 600*scaling_factor_W)
        {
            Entity1.X+= (2*scaling_factor_W);
            Entity2.X+= (2*scaling_factor_W);
            Musket.X += (2*scaling_factor_W);
        }
    }

    //Jumping
    if(Entity1.Y < minY && !keystate[SDLK_SPACE]){
        if(Ascent > 0){
            Entity1.Y -= Ascent;
            Musket.Y -= Ascent;
            Ascent -= (.01*scaling_factor_H);
        }
        if(Ascent < 0){
            Entity1.Y -= Ascent;
            Musket.Y -= Ascent;
            Ascent -= (.01*scaling_factor_H);
        }
    }

    if ((SDL_GetTicks()- startTime) < (1000.0/600)){
        SDL_Delay((1000.0/400));
    }
    startTime = SDL_GetTicks();

}

//Jump function
void CApp::jump (){
    		Entity1.Y -= Ascent;
    		Musket.Y -= Ascent;
    		Ascent -= (.01*scaling_factor_H);
}
