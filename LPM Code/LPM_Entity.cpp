#include "LPM_Entity.h"
#include "ResolutionManager.h"
#include "CApp.h"
//List of entities
std::vector<LPM_Entity*> LPM_Entity::EntityList;

//Entity constructor
LPM_Entity::LPM_Entity() {
    //Intialize that surface
    Surf_Entity = NULL;

    iFrames = 0;

    //Intialize where it goes in life
    X = 0.0f;
    //This makes it start out on the ground
    Y = 408.0f;

    //The sizes of the image
    Width = Height = 0;

    //The state of animation, right not its just whether its facing forward or back
    AnimState = 0;

    //?
    Activated = 0;
    Facing = 'R';
    Jumping = false;
}

//Evil entity constructor
LPM_Entity::~LPM_Entity(){
}

//Load some surfaces
bool LPM_Entity::OnLoad(char* File, double Width, double Height, int MaxFrames) {
    //Load it and check it
    if((Surf_Entity = LPM_Surface::OnLoad(File)) == NULL) {
        return false;
    }
    //Set them parameters not that we got em.
    this->Width = Width;
    this->Height = Height;

    //Give the animation control for this dude some info concerning how many frames he has
    Anim_Control.MaxFrames = MaxFrames;
    //Surf_Entity = scaleBy(Surf_Entity);

    return true;
}

//Animate him
void LPM_Entity::OnLoop() {
    Anim_Control.OnAnimate();
}

//Draw him
void LPM_Entity::OnRender(SDL_Surface* Surf_Display){
    //First check if they exist
    if(Surf_Entity == NULL || Surf_Display == NULL) return;

    //Draw them using special better draw for animation purposes.
    //Sections off each frame, and AnimState traverse the rows of animations
    //Use the current frame to make sure you are drawing the correct frame
    LPM_Surface::OnDraw(Surf_Display, Surf_Entity, X, Y, AnimState * Width, Anim_Control.GetCurrentFrame()*Height, Width, Height);

}

//Free the surfaces!
void LPM_Entity::OnCleanup() {
    if(Surf_Entity) {
        SDL_FreeSurface(Surf_Entity);
    }

    Surf_Entity = NULL;
}
