#include "CApp.h"


CApp::CApp(char* fileName)
{
    loadGame();
    //Intiate the surfaces
    Surf_Display = NULL;
    Surf_Backdrop = NULL;

    //Intiate variables concerning movement
    Ascent = (2*scaling_factor_H);
    DashDistance = 0.0f;
    NoDash = bossMode = false;
    SwordMotion = 5;

    startTime = SDL_GetTicks();

    //Set running to true
    Running = true;
}

//Execute program
int CApp::OnExecute() {
    //If fails to intialize, get out
    if(OnInit() == false){
        return -1;
    }

    //Construct the event reader
    SDL_Event Event;

    //play the music
    playHUBBG();

    //While its running, listen for player inputs
    while(Running) {
        //While player inputs are being inputed
        while(SDL_PollEvent(&Event)) {
            //Decipher player inputs
            OnEvent(&Event);

        }
        //Loop what needs to be looped during gameplay
        OnLoop();
        //Render what needs to be rendered during gameplay
        OnRender();

    }

    //Clean up the assets
    OnCleanup();
    return 0;
}


