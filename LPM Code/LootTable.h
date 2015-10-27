#include <SDL.h>

#ifndef _LOOTTABLE_H_
#define _LOOTTABLE_H_

void rollLoot(int x, int y, SDL_Surface* Surf_Display);
void spawnLoot(int type, int x, int y, SDL_Surface* Surf_Display);
void initLoot();

#endif // _LOOTTABLE_H_
