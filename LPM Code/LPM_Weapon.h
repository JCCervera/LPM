#include "LPM_Animation.h"
#include "LPM_Surface.h"
#include "hitbox.h"
#include "enemy.h"


class LPM_Weapon{
        public:


            SDL_Surface*    Surf_Weapon; //Sets the information for the weapons surface

            public:
            float           X; //Weapons X position
            float           Y; //Weapons Y position

            double             Width; //Weapons width
            double             Height; //Weapons height

            char            Form;
            bool            changeReload, hasSwung;
            int             comboNum;

            int             AnimState; //The current frame of the Weapons animation that still needs to be animated
            LPM_Animation   Anim_Control;
            hitbox          Weapon_Box;

        public:

            LPM_Weapon ();

        public:
            virtual bool OnLoad(char* File, double Width, double Height, int MaxFrames);//Loads file

            virtual void OnLoop();//Loops animation

            virtual void OnHit();

            virtual void OnRender(SDL_Surface* Surf_Display);

            virtual void OnCleanup();

            virtual void InitiatePlacement(int Ex, int Ey, double scaling_factor_W, double scaling_factor_H);

            virtual void changeForm();

};
