#include "LPM_Surface.h"
#include "ResolutionManager.h"
#include "CApp.h"
//Construct absolutely nothing
LPM_Surface::LPM_Surface() {
}

//Load them surfaces
SDL_Surface* LPM_Surface::OnLoad(char* File) {
    //Intialize a temporary surface and the surface to be returned
    SDL_Surface* Surf_Temp = NULL;
    SDL_Surface* Surf_Return = NULL;

    //Load the file into the temp
    if((Surf_Temp = IMG_Load(File)) == NULL){

        return NULL;
    }

    //Format alphas for transparency
    Surf_Return = SDL_DisplayFormatAlpha(Surf_Temp);
    Surf_Return = scaleBy(Surf_Return);

    //Free the temporary surface
    SDL_FreeSurface(Surf_Temp);
    //Return the surface we all like and deserve
    return Surf_Return;
}

//Draw the surface unto the window
bool LPM_Surface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y) {

    //Check if we actually got some surfaces
    if(Surf_Dest == NULL || Surf_Src == NULL){
        return false;
    }

    //The surface rectangle we are drawing
    SDL_Rect DestR;

    //Where it will be going
    DestR.x = X;
    DestR.y = Y;

    //Do it!
    SDL_BlitSurface(Surf_Src, NULL, Surf_Dest, &DestR);

    return true;
}

//A different draw that accomplishes different goals
bool LPM_Surface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y, int X2, int Y2, int W, int H){
    //Check if we got some surfaces
    if(Surf_Dest == NULL || Surf_Src == NULL){
        return false;
    }

    //Make a rectangle
    SDL_Rect DestR;

    //Where we are putting it
    DestR.x = X;
    DestR.y = Y;

    //Rectangle we are using to section off an image from the bigger image
    SDL_Rect SrcR;

    //Where we section off the smaller image from
    SrcR.x = X2;
    SrcR.y = Y2;

    //how big is this smaller image
    SrcR.w = W;
    SrcR.h = H;

    //DO IT!!!!
    SDL_BlitSurface(Surf_Src, &SrcR, Surf_Dest, &DestR);

    return true;
}
