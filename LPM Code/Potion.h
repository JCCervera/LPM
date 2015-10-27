//Last Edit: 11/16/2013

#ifndef _POTION_H_
#define _POTION_H_


void makePotion(int x, int y, SDL_Surface* Surf_Display);
int updatePotion(SDL_Surface* Surf_Display, hitbox hitbox, int cur_hp, int max_hp);
void movePotion(int direction);
bool potionExists();
void descendPotion();
void deletePotion(int index);

#endif
