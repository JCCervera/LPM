#ifndef _LPM_ENTITY_H_
    #define _LPM_ENTITY_H_

#include <vector>

#include "LPM_Animation.h"
#include "LPM_Surface.h"

class LPM_Entity {
    public:
        //Keeps track of all the different entities in order for the sake of collision
        static std::vector<LPM_Entity*>     EntityList;

    public:


        SDL_Surface*    Surf_Entity; //Sets the information for the entities surface

    public:
        float           X; //Entities X position
        float           Y; //Entities Y position
        char            Facing;
        double             Width; //Entities width
        double             Height; //Entities height
        int             HP;//Life
        float             iFrames, chargeFrames;//Invincibility frames and charge shot frames
        float stunFrames, knockback;

        int             AnimState; //The current frame of the entities animation that still needs to be animated

        int             Activated; //Unused?

        bool            Jumping, hasShot, isFacingLeft;

        LPM_Animation   Anim_Control; //Sets the information for the animations of the entity

    public:
        LPM_Entity(); //Constructor

        virtual ~LPM_Entity();//Unused, probably has purpose

    public:
        virtual bool OnLoad(char* File, double Width, double Height, int MaxFrames);//Loads file and parameters for entity

        virtual void OnLoop();//Loops animation

        virtual void OnRender(SDL_Surface* Surf_Display);//Renders entity

        virtual void OnCleanup();//Frees entity surfaces
};

#endif
