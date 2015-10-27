#include "hitbox.h"

/*This class deals with the hitboxes used by every gameplay-related object in the game.
*/

//Constructor default
hitbox::hitbox()
{
    hitSurface = NULL;
    X = Y = Width = Height = farX = farY = 0;
}

//Calculates distance between two points
float hitbox::distance(float x1, float x2, float y1, float y2)
{
    float value = sqrt(pow((x2 - x1),2) + pow((y2 - y1), 2));
    return value;
}

//Check if a point is inside a given hitbox. Used for collision checking.
bool hitbox::inside(float checkX, float checkY, float leftX, float rightX, float topY, float bottomY)
{
    if(checkX < rightX && checkX > leftX && checkY < bottomY && checkY > topY)
        return true;
    else return false;
}

//Updates the the x, y, height, and width values with new values. Need to call this with the values
//Supplied by the entity (or whatever) it is attached to. Should be called every frame I guess.
void hitbox::update(float x, float y, float width, float height)
{
    this->X = x;
    this->Y = y;
    this->Width = width;
    this->Height = height;
    this->farX = x + width;
    this->farY = y + height;
}

//Check to see if the hitbox you call this from is in contact with another hitbox you provide.
//Eventually, when there are multiple hitbox / hurtbox objects on screen, we will likely need to store
//them all in an array or something and call this or each one
bool hitbox::collisionCheck(hitbox other)
{
    //Store collision points
    //Uses numpad order
    //  -For example the cooridants in (pointsX[1],pointsY[1]) are the bottom left corner of the box.
    //7 8 9
    //4 6 5
    //1 2 3
    pointsX[0] = pointsY[0] = 0; // Origin
    pointsX[5] = pointsX[8] = pointsX[2] = this->X + (this->Width / 2); //Center line Xs
    pointsY[5] = pointsY[4] = pointsY[6] = this->Y + (this->Height / 2); //Center line Ys
    pointsX[7] = pointsX[1] = pointsX[4] = this->X; //Left side Xs
    pointsX[9] = pointsX[3] = pointsX[6] = this->X + this->Width; //Right side Xs
    pointsY[7] = pointsY[8] = pointsY[9] = this->Y;//Top side Ys
    pointsY[1] = pointsY[2] = pointsY[3] = this->Y + this->Height;//Bottomm side Ys

    //Find the distance between each tracked point and the center of the target hitbox

    int i = 0;

    for(i = 1; i < 10; i++)
    {
        //Calculate distance

        //check for colissions
        if(inside(pointsX[i], pointsY[i], other.X, other.farX, other.Y, other.farY))
        {
            return true;
        }
    }

    return false;

}

//Platform only chills with the bottom 3 poitns (1,2,3)
bool hitbox::platformCheck(hitbox other)
{
    //Store collision points
    //Uses numpad order
    //  -For example the cooridants in (pointsX[1],pointsY[1]) are the bottom left corner of the box.
    //7 8 9
    //4 6 5
    //1 2 3
    pointsX[0] = pointsY[0] = 0; // Origin
    pointsX[2] = this->X + (this->Width / 2); //Center line Xs
    pointsX[1] = this->X; //Left side Xs
    pointsX[3] = this->X + this->Width; //Right side Xs
    pointsY[1] = pointsY[2] = pointsY[3] = this->Y + this->Height;//Bottomm side Ys

    //Find the distance between each tracked point and the center of the target hitbox
    //pointDistances[0] = 0;

    int i = 0;

    for(i = 1; i < 4; i++)
    {
        //Calculate distance
        //pointDistances[i] = distance(pointsX[i], other.CenterX, pointsY[i], other.CenterY);

        //check for collisions
        if(inside(pointsX[i], pointsY[i], other.X, other.farX, other.Y, other.farY))
        {
            return true;
        }
    }

    return false;

}

//Free everything
void hitbox :: onCleanup()
{
    if(hitSurface){
            SDL_FreeSurface(hitSurface);
        }

        hitSurface = NULL;
}
