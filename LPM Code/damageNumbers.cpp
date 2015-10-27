#include "damageNumbers.h"


std::vector<damageNumbers*>     damageNumbers::numberList;


void damageNumbers::init(float number, float x, float y, float anim)
{
    this->numberDisplay = number;
    this->frames = anim;
    this->Y = y;
    this->X = x;
    this->font = TTF_OpenFont("FreeSans.ttf", 16);
    this->out.str("");
    this->out << number;
    this->toDisplay = TTF_RenderText_Solid(this->font, out.str().c_str(), {255, 255, 255});
}


void damageNumbers :: update(SDL_Surface *display, double scaling_factor_W, double scaling_factor_H)
{
    this->location = {this->X, this->Y, (600*scaling_factor_W), (400*scaling_factor_H)};
    SDL_BlitSurface(this->toDisplay, NULL, display, &this->location);
    this->Y -= (.1*scaling_factor_W);
    if(this->frames > 0) this->frames --;
    //if(this->frames == 0)
    else this->die();
}

void damageNumbers :: die()
{
    for(int i = 0; i < damageNumbers::numberList.size(); i++)
        {
            if(!damageNumbers::numberList[i]) continue;
            if(i > this->index) damageNumbers::numberList[i]->index--;
        }
    while(this->index > damageNumbers::numberList.size()) this->index--;
    SDL_FreeSurface(this->toDisplay);
    damageNumbers::numberList.erase(damageNumbers::numberList.begin() + this->index);
    delete this;
}
