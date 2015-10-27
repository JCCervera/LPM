//Matthew Magnuson
//Last Edit: 9/12/2013 - Matt
//Sound Player: Contains functions for initializing, playing, pausing, and freeing sound files from memory.
//              Pump the beats.

//A note about loading sound files into memory:
//The idea here is we want to load into memory only the relevant sounds in a given section of the game.
//We don't want the entire games audio to load all at once, since the files are relatively large.
//So, we'll have separate functions to load the sound for the main menu, the hub world, the shop music, and individual levels.
//Sounds should be loaded prior to each level, and the sounds of the previous level should be cleaned up.

#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
using namespace std;

//Creating variables where we'll store our sounds later. These need to be accessed by a large number of functions within
//the file.
Mix_Chunk *button_click_clip = NULL;
Mix_Chunk *jump_clip = NULL;
Mix_Chunk *shoot_clip = NULL;
Mix_Chunk *sword_clip = NULL;
Mix_Music *hub_bg_music = NULL;
Mix_Music *boss_bg_music = NULL;
Mix_Music *mm_bg_music = NULL;


//initSound- initializes the SDL_mixer. Our audio files need to be in .wav format to work correctly.
//           Parameters: The 1st, 2nd, and 4th parameters are all recommended parameters by SDL.
//           The third specifies mono (1) or stereo (2).
void initSound(){

    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );

}//end FUNCTION - initSound


//loadButtonSound - Used in all areas of the game for the main menu, pause menu, file menu, and upgrade menu.
void loadButtonSound(){

    button_click_clip = Mix_LoadWAV("sound_pew.wav");

}//end FUNCTION - loadButtonSound

//loadMMSound - loads the background music for the main menu.
void loadMMSound(){

    mm_bg_music = Mix_LoadMUS("mm_bg_music.wav");
}//end FUNCTION - loadMMSound

//loadHubSound - loads the background music for the HUB world.
void loadHubSound(){

    hub_bg_music = Mix_LoadMUS("hub_bg_music.wav");

}//end FUNCTION - loadHubSound

void loadBossSound(){

    boss_bg_music = Mix_LoadMUS("boss_bg_music.wav");

}

//loadGameSounds - Contains all the standard sounds for the game. Jumping, shooting, enemy sounds, etc.
void loadGameSound(){

   // jump_clip = Mix_LoadWAV("sound_pew.wav");
    shoot_clip = Mix_LoadWAV("sound_pew.wav");
    sword_clip = Mix_LoadWAV("sound_sword.wav");

}//end FUNCTION - loadGameSound

//MMSoundCleanup - Frees the background music for the main menu.
//                 Currently called only in the main menu cleanup functions.
void MMSoundCleanup(){

    Mix_FreeMusic(mm_bg_music);

}//end FUNCTION - MMSoundCleanup

//soundCleanUp - Frees the various game sounds used throughout the entire function, which includes the jump and shoot sounds.
//               Called in OnCleanup
void soundCleanUp(){

    //Mix_FreeChunk(jump_clip);
    Mix_FreeChunk(shoot_clip);
    Mix_FreeChunk(sword_clip);
    Mix_FreeMusic(hub_bg_music);
    if(boss_bg_music != NULL) Mix_FreeMusic(boss_bg_music);
}//end FUNCTION - soundCleanUp

//buttonSoundCleanUp -Frees our button click sound effect.
//                    Called in OnCleanUp and mainCompleteCleanUp
void buttonSoundCleanUp(){

    Mix_FreeChunk(button_click_clip);

}//end FUNCTION - buttonSoundCleanUp

//mixerCleanUp - Frees the SDL audio mixer.
//               Called in mainCompleteCleanUp and OnCleanup
void mixerCleanUp(){

    Mix_CloseAudio();

}//end FUNCTION - mixerCleanUp

//All of the following functions relate to playing individual sounds effects or single music files. Individual descriptions
//of each are not necessary.
void playButtonClick(){

    Mix_PlayChannel(-1, button_click_clip, 0);

}//end FUNCTION - playButtonClick

void playHUBBG(){

    Mix_PlayMusic(hub_bg_music, -1);

}//end FUNCTION - playHUBBG

void playMMBG(){

    Mix_PlayMusic(mm_bg_music, -1);

}//end FUNCTION - playMMBG

void playBBG(){

    Mix_PlayMusic(boss_bg_music, -1);

}

void playJump(){

    //Mix_PlayChannel(-1, jump_clip, 0);

}//end FUNCTION - playJump

void playShoot(){

    Mix_PlayChannel(-1, shoot_clip, 0);

}//end FUNCTION - playShoot

void playSword(){
    Mix_PlayChannel(-1, sword_clip, 0);
}


