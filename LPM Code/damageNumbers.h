#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <sstream>
#include <vector>

class damageNumbers
{
    public: //Variables
        static std::vector<damageNumbers*>     numberList;
        float numberDisplay, frames, X, Y;
        int index;
        TTF_Font *font;
        SDL_Rect location;
        SDL_Surface *toDisplay;
        std::stringstream out;
    public: //Functions
        void init(float number, float x, float y, float anim);
        void update(SDL_Surface *display, double scaling_factor_W, double scaling_factor_H);
        void die();
};
