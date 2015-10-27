#ifndef _ENEMY_H_
    #define _ENEMY_H_

#include <SDL.h>
#include <SDL_image.h>
#include <math.h>
#include <vector>
#include <SDL_ttf.h>
#include <sstream>
#include "hitbox.h"
#include "LPM_Entity.h"
#include "SoundPlayer.h"
#include "Potion.h"


class enemy: public LPM_Entity
{
    public: //Variables
        static std::vector<enemy*>     enemyList;
        bool justHit;
        hitbox  enemyBox;
        SDL_Surface *redSurface;
        int index; //Spot in the vector
        int numCollisions; //debugging n stuff
        float damageDisplay;
        TTF_Font *font;
        SDL_Rect location;
        SDL_Surface *life;
        std::stringstream out;
        //Later, this will be more sophisticated. For now the default enemy class is only good for hazards
    public: //Constructors
        enemy();
    public: //Functions
        void hitStun(LPM_Entity *other);
        void drawHitbox(SDL_Surface *display, bool isDraw);
        void newCleanup();
        void moveUpdate(bool isLeft, double scaling_factor_W);
        void die(SDL_Surface* Surf_Display);
        virtual void AI(LPM_Entity *other, hitbox box, SDL_Surface* Surf_Display, double scaling_factor_W, double scaling_factor_H);
};

class madmask: public enemy
{
    using enemy::AI;
    public:
        int state;
        void AI(LPM_Entity *other, hitbox box, SDL_Surface* Surf_Display, double scaling_factor_W, double scaling_factor_H);
    public: //Constructors
        madmask();
};

class portal: public enemy
{
    using enemy::AI;
    public:
        void AI(LPM_Entity *other, hitbox box, SDL_Surface* Surf_Display, double scaling_factor_W, double scaling_factor_H);
    public:
        static int level;
        //static bool test;
        bool hasTalked;
        Uint8 *keystate;
    public://Constructors
        portal();
};

class npc: public enemy
{
    using enemy::AI;
    public:
        void AI(LPM_Entity *other, hitbox box, SDL_Surface* Surf_Display, double scaling_factor_W, double scaling_factor_H);
    public:
        bool hasTalked;
        Uint8 *keystate;
    public: //Constructors
        npc();
};

class bullet: public enemy
{
    using enemy::AI;
    public://Variables
        bool isFacingLeft, go;
        //bool hasDied;
        static std::vector<bullet*>     bulletList;
        bool hasKilled;
    public:
        virtual void AI(LPM_Entity *other, hitbox box, SDL_Surface* Surf_Display, double scaling_factor_W, double scaling_factor_H);
        void die();
    public: //Constructors
        bullet();
};

class badBullet: public bullet
{
    using bullet::AI;
    public://Variables
        bool isFacingLeft, go;
        bool hasKilled;
    public:
        virtual void AI(LPM_Entity *other, hitbox box, SDL_Surface* Surf_Display, double scaling_factor_W, double scaling_factor_H);
    public: //Constructors
        badBullet();
};

class boss: public enemy
{
    using enemy::AI;
    using enemy::hitStun;
    public:
        static bool dead;
        bool cutscene;
        int state;
        int dir, teleDir;
        int x;
        void AI(LPM_Entity *other, hitbox box, SDL_Surface* Surf_Display, double scaling_factor_W, double scaling_factor_H);
        void hitStun(LPM_Entity *other, double scaling_factor_W);
    public: //Constructors
        boss();
};


class chargeShot: public bullet
{
    using bullet::AI;
    public:
        void AI(LPM_Entity *other, hitbox box, SDL_Surface* Surf_Display, double scaling_factor_W, double scaling_factor_H);
    public: //Constructors
        chargeShot();
};

class sinShot: public bullet
{
    using bullet::AI;
    public:
        float dir;
    public:
        void AI(LPM_Entity *other, hitbox box, SDL_Surface* Surf_Display, double scaling_factor_W, double scaling_factor_H);
    public:
        sinShot();
};

class shieldShot: public bullet
{
    using bullet::AI;
    public:
        float angle;
    public:
        void AI(LPM_Entity *other, hitbox box, SDL_Surface* Surf_Display, double scaling_factor_W, double scaling_factor_H);
    public:
        shieldShot();
};
#endif
