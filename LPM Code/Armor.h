#include <SDL.h>
#include <SDL_image.h>

#ifndef _ARMOR_H_
#define _ARMOR_H_

void spawnArmor(int x, int y, SDL_Surface* surf, int type);
void updateArmor( SDL_Surface* Surf_Display, hitbox hitbox, int cur_hp, int max_hp, LPM_Entity* Entity1);
bool armorExists();
void descendArmor();
void moveArmor(int direction);
void deleteArmor(int index, LPM_Entity* Entity1);


#endif // _ARMOR_H_
