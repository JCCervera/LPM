#include "LPM_Ground.h"
#include "CApp.h"

//Construct the ground!
LPM_Ground::LPM_Ground(){
    //Intialize surface
    Surf_Ground = NULL;

    Type = 'N';

    //Make the X slightly offset for interesting reasons
    X = 0.0f;

}

//Load some files into my surface
bool LPM_Ground::OnLoad(char* File){
        //Better check if it worked
        if((Surf_Ground = LPM_Surface::OnLoad(File)) == NULL){
            return false;
        }
        //Surf_Ground = scaleBy(Surf_Ground);
        return true;
    }

//Render this surface
void LPM_Ground::OnRender(SDL_Surface* Surf_Display, int Y){

        //Draw it!
        LPM_Surface::OnDraw(Surf_Display, Surf_Ground, X, Y);

        //If it goes to far left, reset it!
        if(X<=(-160*scaling_factor_W) && Type == 'G'){X=(-80*scaling_factor_W);}

        if(X<=(-640*scaling_factor_W) && Type == 'B'){X=(640*scaling_factor_W);}

        //if(X < -64 && Type == 'E')X=703;

        //if(X < -121 && Type == 'P')X=703;

        //So far right? RESET IT!!
        if(X>=0 && Type == 'G'){X=(-80*scaling_factor_W);}

        if(X>=(641*scaling_factor_W) && Type == 'B'){X=(-639*scaling_factor_W);}

        //if(X > 704 && Type == 'E')X=-63;

        //if(X > 704 && Type == 'P')X=-120; if(X < -121 && Type == 'P')X=703;

     }



//Free the ground!
void LPM_Ground::OnCleanup(){
        if(Surf_Ground){
            SDL_FreeSurface(Surf_Ground);
        }

        //reintialize for future use
        Surf_Ground = NULL;

    }
