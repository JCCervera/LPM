#include "CApp.h"

/*CApp::CApp() {
    //Intiate the surfaces
    Surf_Display = NULL;
    Surf_Backdrop = NULL;

    Ascent = 10;
    NOJUMP = false;

    //Set running to true
    Running = true;
}*/


CApp::CApp(char* fileName)
{
    loadGame();
    //Intiate the surfaces
    Surf_Display = NULL;
    Surf_Backdrop = NULL;

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

    //Constructor the event reader
    SDL_Event Event;

    //play the music
    playHUBBG();

    //While its running, do the stuffs
    while(Running) {
        //While we are looking for some events
        while(SDL_PollEvent(&Event)) {
            //Get those events rolling
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

//MAIN
/*
int main(int argc, char* argv[]) {
    //Constructor app
    CApp LaserPoweredMustketGame;

    return LaserPoweredMustketGame.OnExecute();
}*/

