#include "platform.h"

/*This class is used for handling the floating platforms in the game. They work by altering the player's 'min height' value.
  The actual collision functions are not really handled here, as they are all included in the hitbox object.
*/

//List of platforms
std::vector<platform*> platform::platformList;

//Constructor
platform :: platform()
{
    this->X = this->Y = this->Height = this->Width = 0;
    this->Surf_Ground = NULL;
    this->Type = 'P';
}

//Rendering function
void platform :: drawHitbox(SDL_Surface *display, bool isDraw)
{
    //Check location of hitbox.
    this->collider.update(this->X, this->Y, this->Width, 4);

    //Draw the actual platform sprite
    LPM_Surface::OnDraw(display, this->Surf_Ground, this->X, this->Y);

    //Draw hitSurface (if the debug flag passed to the function is set to true)
    if(isDraw) LPM_Surface::OnDraw(display, this->collider.hitSurface, (int)this->collider.X, (int)this->collider.Y, 0, 0, (int)this->collider.Width, (int)this->collider.Height);


}

//Update a platform when the player is moving left or right
void platform :: moveUpdate(bool isLeft, double scaling_factor_W)
{
    if(isLeft) this-> X += (3* scaling_factor_W);
    else this-> X -= (3*scaling_factor_W);
}

//Free the surfaces
void platform :: newCleanup()
{
    this->OnCleanup();
    this->collider.onCleanup();
}
