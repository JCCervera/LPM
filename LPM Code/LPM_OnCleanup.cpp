#include "CApp.h"

void CApp::OnCleanup() {
    //Free the background!
    //Free the window!
    SDL_FreeSurface(Surf_Display);
    //Free the ground!
    Ground.OnCleanup();
    Background.OnCleanup();

    //Free all the yoshis!
    for(int i = 0; i < LPM_Entity::EntityList.size(); i++) {
        if(!LPM_Entity::EntityList[i]) continue;

        LPM_Entity::EntityList[i]->OnCleanup();
    }

    //Free hitbox
    SDL_FreeSurface(playerBox.hitSurface);

    //HEY GUYS I ACTUALLY DID CLEANUP THIS TIME
    for(int i = 0; i < platform::platformList.size(); i++)
        {
            if(!platform::platformList[i]) continue;

            platform::platformList[i]->newCleanup();
        }

    for(int i = 0; i < enemy::enemyList.size(); i++)
        {
            if(!enemy::enemyList[i]) continue;

            enemy::enemyList[i]->newCleanup();
        }

    for(int i = 0; i < bullet::bulletList.size(); i++)
        {
            if(!bullet::bulletList[i]) continue;

            bullet::bulletList[i]->newCleanup();
        }

    for(int i = 0; i < damageNumbers::numberList.size(); i++)
        {
            if(!damageNumbers::numberList[i]) continue;

            damageNumbers::numberList[i]->die();
        }

    //Free lifebars
    SDL_FreeSurface(Surf_Green);
    SDL_FreeSurface(Surf_Red);
    SDL_FreeSurface(Surf_Frame);



    Musket.OnCleanup();

    //Free the list of yoshis!
    LPM_Entity::EntityList.clear();
    //Clean all my garbage! - Matt's stuff.
    soundCleanUp();
    pauseCleanUp();
    upgradeCleanUp();
    fileCleanUp();
    mainCleanUp();
    buttonSoundCleanUp();
    mixerCleanUp();


}
