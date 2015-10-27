#include "CApp.h"
#include <SDL_rotozoom.h>

//Intialize
bool CApp::OnInit() {
    Entity1.chargeFrames = 0;
    SwordMotion = 5;
    hasSwitched = false;
    gunDisplay = "Charge Shot";
    gunType = 1;
    Entity1.hasShot = Entity1.isFacingLeft = false;
    font = TTF_OpenFont("FreeSans.ttf", 24*scaling_factor_H);
    text_color = {255, 255, 255};
    drawHitboxes = false;
    onPlatform = true;
    Entity1.HP = maxHP;

    ratio = 1;
    Entity1.iFrames = 0;
    trackX = 100*scaling_factor_W;
    HPtext = maxText = HPDisplay = " ";
    text = TTF_RenderText_Solid(font, HPDisplay.c_str(), text_color);
    gameover = TTF_RenderText_Solid(font, "Game Over", text_color);
    myGun = TTF_RenderText_Solid(font, gunDisplay.c_str(), text_color);

    //Initialize everything, I guess. Checking if SDL started fine
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        return false;
    }

    keystate = SDL_GetKeyState(NULL);

    // Initialize SDL_ttf library
   if (TTF_Init() != 0)
    {
        std::cerr << "init";
        return false;
    }

    //Sets the window display
    Surf_Display = screen;

    if((Surf_Backdrop = LPM_Surface::OnLoad("backdrop.png")) == NULL){
        return false;
    }

    //Loads background image
    if(Background.OnLoad("background.png") == false) {
        return false;
    }
    Background.Type = 'B';
    //loads ground
    if(Ground.OnLoad("ground.png") == false){
        return false;
    }
    Ground.Type = 'G';

    //Loads Player
    if(Entity1.OnLoad("PlayerAnim.png", ((130.0*scaling_factor_W)*.75) , ((216.0*scaling_factor_H)*.75), 10) == false){
        return false;
    }
    //Scale down the sprite
    Entity1.Surf_Entity = zoomSurface(Entity1.Surf_Entity, .75, .75, 1);

    minY = (472*scaling_factor_H) - Entity1.Height;
    maxY = 164 - Entity1.Height;
    Entity1.Y = minY;


    //Load some green
    if((Surf_Green = LPM_Surface::OnLoad("green.png")) == NULL)
    {
        return false;
    }

    //Load some red
    if((Surf_Red = LPM_Surface::OnLoad("red.png")) == NULL)
    {
        return false;
    }
    //Load some frame
    if((Surf_Frame = LPM_Surface::OnLoad("healthbarframe.png")) == NULL)
    {
        return false;
    }

    //Load some blue
    if((playerBox.hitSurface = LPM_Surface::OnLoad("blue.png")) == NULL)
    {
        return false;
    }

    //Load the LPM
    if(Musket.OnLoad("TheLPM.png", ((200*scaling_factor_W)*.75), ((260*scaling_factor_H)*.75), 8) == false) {
		return false;
	}
    //Scale the LPM
    Musket.Surf_Weapon = zoomSurface(Musket.Surf_Weapon, .75, .75, 1);

    //Allows you to hold down them keys
    SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL/3);

    //Center the player
    Entity1.X = (250*scaling_factor_W);


    //Load level
    platform::platformList = loadPlatforms("level1.txt");
    enemy::enemyList = loadEnemies("level1.txt");

    //Set up hitboxes
    playerBox.X = Entity1.X;
    playerBox.Y = Entity1.Y;

    //Set up musket
    Musket.InitiatePlacement(Entity1.X, Entity1.Y, scaling_factor_W, scaling_factor_H);

    //Initializing the sound, pause, and upgrade menus.
    loadHubSound();
    loadGameSound();
    pauseInit();
    upgradeInit();

    return true;
}
