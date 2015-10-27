
#include "LPM_Event.h"
//Event constructor
LPM_Event::LPM_Event() {
}
//Evil Event constructor
LPM_Event::~LPM_Event(){
}

//So again, this one is really long, but basically it does what it needs to
//in order to listen for controls pressed
void LPM_Event::OnEvent(SDL_Event* Event) {
    switch(Event->type) {
        case SDL_ACTIVEEVENT: {
            switch(Event->active.state) {
                case SDL_APPMOUSEFOCUS: {
                    if ( Event->active.gain )   OnMouseFocus();
                    else                OnMouseBlur();

                    break;
                }
                case SDL_APPACTIVE:     {
                    if( Event->active.gain )    OnRestore();
                    else               OnMinimize();

                    break;
                }
            }
            break;
        }

        case SDL_KEYDOWN: {
            OnKeyDown(Event->key.keysym.sym,Event->key.keysym.mod,Event->key.keysym.unicode);
            break;
        }

        case SDL_KEYUP: {
            OnKeyUp(Event->key.keysym.sym,Event->key.keysym.mod,Event->key.keysym.unicode);
            break;
        }

        case SDL_MOUSEMOTION: {
            OnMouseMove(Event->motion.x,Event->motion.y,Event->motion.xrel,Event->motion.yrel,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE))!=0);
            break;
        }

        case SDL_MOUSEBUTTONDOWN: {
            switch(Event->button.button) {
                case SDL_BUTTON_LEFT: {
                    OnLButtonDown(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT: {
                    OnRButtonDown(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE:{
                    OnMButtonDown(Event->button.x,Event->button.y);
                    break;
                }
            }
            break;
        }

        case SDL_MOUSEBUTTONUP:     {
            switch(Event->button.button) {
                case SDL_BUTTON_LEFT: {
                    OnLButtonUp(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT: {
                    OnRButtonUp(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE: {
                    OnMButtonUp(Event->button.x,Event->button.y);
                    break;
                }
            }
            break;
        }

        case SDL_JOYAXISMOTION: {
            OnJoyAxis(Event->jaxis.which,Event->jaxis.axis,Event->jaxis.value);
            break;
        }
        case SDL_JOYHATMOTION: {
            OnJoyHat(Event->jhat.which,Event->jhat.hat,Event->jhat.value);
            break;
        }
        case SDL_JOYBUTTONDOWN: {
            OnJoyButtonDown(Event->jbutton.which,Event->jbutton.button);
            break;
        }
        case SDL_JOYBUTTONUP: {
            OnJoyButtonUp(Event->jbutton.which,Event->jbutton.button);
            break;
        }
        case SDL_QUIT: {
            OnExit();
            break;
        }
        case SDL_SYSWMEVENT: {
            break;
        }
        case SDL_VIDEORESIZE: {
            OnResize(Event->resize.w,Event->resize.h);
            break;
        }
        case SDL_VIDEOEXPOSE: {
            OnExpose();
            break;
        }
        default: {
            OnUser(Event->user.type,Event->user.code,Event->user.data1,Event->user.data2);
            break;
        }
    }
}

void LPM_Event::OnInputFocus(){
}

void LPM_Event::OnInputBlur(){
}

void LPM_Event::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode){
}

void LPM_Event::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode){
}

void LPM_Event::OnMouseFocus(){
}

void LPM_Event::OnMouseBlur(){
}

void LPM_Event::OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle){
}

void LPM_Event::OnMouseWheel(bool Up, bool Down){
}

void LPM_Event::OnLButtonDown(int mX, int mY){
}

void LPM_Event::OnLButtonUp(int mX, int mY){
}

void LPM_Event::OnRButtonDown(int mX, int mY){
}

void LPM_Event::OnRButtonUp(int mX, int mY){
}

void LPM_Event::OnMButtonDown(int mX, int mY){
}

void LPM_Event::OnMButtonUp(int mX, int mY){
}

void LPM_Event::OnJoyAxis(Uint8 which, Uint8 axis, Sint16 value){
}

void LPM_Event::OnJoyButtonDown(Uint8 which, Uint8 button){
}

void LPM_Event::OnJoyButtonUp(Uint8 which, Uint8 button){
}

void LPM_Event::OnJoyHat(Uint8 which, Uint8 hat, Uint8 value){
}

void LPM_Event::OnJoyBall(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel){
}

void LPM_Event::OnMinimize(){
}

void LPM_Event::OnRestore(){
}

void LPM_Event::OnResize(int w, int h){
}

void LPM_Event::OnExpose(){
}

void LPM_Event::OnExit(){
}

void LPM_Event::OnUser(Uint8 type, int code, void* data1, void* data2){
}



