#include "CApp.h"
#include "PauseMenu.h"

//Make the event listener
void CApp::OnEvent(SDL_Event* Event) {
    LPM_Event::OnEvent(Event);

}

//When a key is pressed, handle it in here
void CApp::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode){


        //Causes ground to move, so that Yoshi looks like he is moving
        //Yoshi's legs are so powerful, he moves the crust under him
        /*if(sym == SDLK_LEFT){
                        Entity1.Anim_Control.FrameRate = 100;
                        Entity2.Anim_Control.FrameRate = 100;
                        Ground.X += 2;
                        Background.X +=.1;
                        Entity1.AnimState = 2;
                        Entity2.AnimState = 2;
                        if(keystate[SDLK_SPACE]){
                            jump();
                        }
        }
        //Samething, other direction, also makes yoshi turn around
        if(sym == SDLK_RIGHT) {
                        Entity1.Anim_Control.FrameRate = 100;
                        Entity2.Anim_Control.FrameRate = 100;
                        Ground.X -= 2;
                        Background.X -=.1;
                        Entity1.AnimState = 3;
                        Entity2.AnimState = 3;
                        if(keystate[SDLK_SPACE]){
                            jump();
                        }
        }

        //If yuou press 1, control the first Yoshi. Cause you hate him or whatever. Same goes with 2.
        if(sym == SDLK_1){ Entity1.Activated = 1; Entity2.Activated = 0;}
        if(sym == SDLK_2){ Entity2.Activated = 1; Entity1.Activated = 0;}

        if(sym == SDLK_SPACE && !NOJUMP){

                        if(keystate[SDLK_LEFT]){
                            Ground.X += 2;
                        }
                        if(keystate[SDLK_RIGHT]){
                            Ground.X -= 2;
                        }
                        jump();

        }

        if(sym == SDLK_z){
                     Entity1.AnimState = 4;
                     Entity2.AnimState = 4;
                     Entity1.Anim_Control.FrameRate = 50;
                     Entity2.Anim_Control.FrameRate = 50;
                     Ground.X += 15;
                     Background.X += .3;
        }

        if(sym == SDLK_x){
                     Entity1.AnimState = 5;
                     Entity2.AnimState = 5;
                     Entity1.Anim_Control.FrameRate = 50;
                     Entity2.Anim_Control.FrameRate = 50;
                     Ground.X -= 15;
                     Background.X -= .3;
        }
                //If you press ESC, go to the pause menu
        */
        if(sym == SDLK_ESCAPE){
                pauseMenu(Surf_Display);
        }

        if(sym == SDLK_RIGHTBRACKET){
                if(Entity1.HP < maxHP) Entity1.HP += 1;
                maxHP++;
                drawHitboxes = true;
        }

        if(sym == SDLK_LEFTBRACKET)
            {
                if(Entity1.HP > 0) Entity1.HP -= 1;
                drawHitboxes = false;
            }

}

void CApp::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode){
        switch(sym) {

        //Make him fart rainbows!
        case SDLK_LEFT: Entity1.AnimState = 2;
                        Entity2.AnimState = 1;
                        break;
        //Make him fart rainbows!
        case SDLK_RIGHT: Entity1.AnimState = 0;
                        Entity2.AnimState = 0;
                        break;


        //Make him fart rainbows!
        case SDLK_1: Entity1.AnimState = 0;
                 Entity2.AnimState = 0;break;
        case SDLK_2: Entity1.AnimState = 0;
                 Entity2.AnimState = 0;break;

        case SDLK_a:    Entity1.hasShot = false;
                        //if(Musket.AnimState == 0) Musket.hasSwung = false;
                        if(Entity1.chargeFrames > 270 && gunType == 1)
                            {
                                playShoot();
                                chargeShot *tempchargeShot = new chargeShot();
                                tempchargeShot->isFacingLeft = Entity1.isFacingLeft;
                                tempchargeShot->iFrames = 0;
                                tempchargeShot->OnLoad("chargeBullet.png", 90*scaling_factor_W, 90*scaling_factor_H, 1);
                                if(Entity1.isFacingLeft) tempchargeShot->X = Entity1.X - Musket.Width/2;
                                else tempchargeShot->X = Entity1.X + Musket.Width/2;
                                tempchargeShot->Y = Entity1.Y;
                                tempchargeShot->enemyBox.hitSurface = LPM_Surface::OnLoad("blue.png");
                                tempchargeShot->index = bullet::bulletList.size();
                                bullet::bulletList.push_back(tempchargeShot);
                            }
                        Entity1.chargeFrames = 0;
                        if(Musket.Form == 'G'){Musket.AnimState = 0;}
                        //if(Musket.Form == 'S'){Musket.AnimState = 2;}
                        break;
        case SDLK_w:    hasSwitched = false;
                        break;
       /* case SDLK_x:    Entity1.AnimState = 0;
                        Entity2.AnimState = 0;

                        break;
        /*case SDLK_z:    Entity1.AnimState = 1;
                        Entity2.AnimState = 1;

                        break;*/
        case SDLK_s: Musket.changeReload = false;
                        break;

        default:;//{Entity1.AnimState = 0;
                // Entity2.AnimState = 0;}

    }

}




//Close the window, I'm out.
void CApp::OnExit(){
    active = false;
    Running = false;
}
