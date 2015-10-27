#ifndef _FILEMENU_H_
#define _FILEMENU_H_
#include <string>
using namespace std;
void fileMenu(SDL_Surface *Surf_Display);
void fileInit();
void fileCleanUp();
string loadName(char* fileName);
#endif // _FILEMENU_H_
