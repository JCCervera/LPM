#include "CApp.h"
#include "PauseMenu.h"

//Make the event listener
void CApp::OnEvent(SDL_Event* Event) {
    LPM_Event::OnEvent(Event);

}

//When a key is pressed, handle it in here
void CApp::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode){

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

        //Move left
        case SDLK_LEFT: Entity1.AnimState = 2;
                        Entity2.AnimState = 1;
                        break;
        //Move right
        case SDLK_RIGHT: Entity1.AnimState = 0;
                        Entity2.AnimState = 0;
                        break;


        //Stop
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
        case SDLK_s: Musket.changeReload = false;
                        break;

        default:;

    }

}




//Close the window
void CApp::OnExit(){
    active = false;
    Running = false;
}
