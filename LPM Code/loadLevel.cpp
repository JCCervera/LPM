#include "CApp.h"

/*This is used to load levels from a txt file. Whitespace and such is used to increment x and y values, while certain characters
  are used to denote individual game objects. If you are interested in seeing how this works, check out 'level1.txt' in the folder.
*/

//This function takes a file name and derives a platform vector from it
std::vector<platform*> CApp::loadPlatforms(char* fileName)
{
    std::string line;
    std::ifstream myfile;
    std::vector<platform*> returnList;
    char c;
    int iX = 0;
    int iY = 0;
    myfile.open(fileName);

    //Get platforms and put them in the vector
    if(myfile.is_open())
    {
        //Using the char '=' to denote platforms.
        //Set their X and Y values according to their position in the text file
        while ( myfile.good() )
        {
           c = myfile.get();
           if(c == '=')
            {
                platform *tempPlatform = new platform();
                tempPlatform->OnLoad("platformnew.png");
                tempPlatform->Type = 'P';
                tempPlatform->collider.hitSurface = LPM_Surface::OnLoad("green.png");
                tempPlatform->Width = 124*scaling_factor_W;
                tempPlatform->Height = 28*scaling_factor_H;
                tempPlatform->X = iX;
                tempPlatform->Y = iY;
                returnList.push_back(tempPlatform);
                iX += (80*scaling_factor_W);
            }
            else if(c == ' ') iX += (80*scaling_factor_W);//Whitespace increment
            else if(c == '\n')//End of line
            {
                iX = 0;
                iY += (48*scaling_factor_H);
            }
            else if(c == '#')//# denotes end of level
            {
                myfile.close();
                return returnList;
            }
            else iX += (80*scaling_factor_W); //Deal with any other character
        }
        myfile.close();
        return returnList;
    }
    else myfile.close();
    return returnList;
}

//Takes a file name and derives an enemy vector from it
std::vector<enemy*> CApp::loadEnemies(char*fileName)
{
    std::string line;
    std::ifstream myfile;
    std::vector<enemy*> returnList;
    char c;
    int iX = 0;
    int iY = 0;
    myfile.open(fileName);
    //iX = iY = 0;

//Get platforms and put them in the vector
    if(myfile.is_open())
    {

        while ( myfile.good() )
        {
           c = myfile.get();
           if(c == '*')//Character * denotes a spike ball
            {
                enemy *tempEnemy = new enemy();
                tempEnemy->OnLoad("GordoNew.png", 98*scaling_factor_W, 86*scaling_factor_H, 8);
                tempEnemy->HP = 10;
                tempEnemy->X = iX;
                tempEnemy->Y = iY;
                tempEnemy->enemyBox.hitSurface = LPM_Surface::OnLoad("red.png");
                tempEnemy->index = returnList.size();
                returnList.push_back(tempEnemy);
                iX += (80*scaling_factor_W);
            }
            else if(c == 'V')//Character V denotes a mad mask
            {
                madmask *tempMask = new madmask();
                tempMask->OnLoad("MaskNew.png", 80*scaling_factor_W, 80*scaling_factor_H, 8);
                tempMask->HP = 10;
                tempMask->X = iX;
                tempMask->Y = iY;
                tempMask->enemyBox.hitSurface = LPM_Surface::OnLoad("red.png");
                tempMask->index = returnList.size();
                int i = tempMask->index;
                returnList.push_back(tempMask);
                iX += (80*scaling_factor_W);
            }
            else if(c == '-') iX += (80*scaling_factor_W);//Whitespace just increments
            else if(c == '\n')//End of line
            {
                iX = 0;
                iY += (48*scaling_factor_H);
            }
            else if(c == '#')//# denotes the ground (end of file)
            {
                myfile.close();
                return returnList;
            }
            else if(c == 'N')//Character N denotes NPC
            {
                npc *tempNPC = new npc();
                tempNPC->OnLoad("ShopMan.png", 130*scaling_factor_W, 216*scaling_factor_H, 1);
                tempNPC->X = iX;
                tempNPC->Y = iY;
                tempNPC->enemyBox.hitSurface = LPM_Surface::OnLoad("green.png");
                tempNPC->index = returnList.size();
                returnList.push_back(tempNPC);
                iX += (80*scaling_factor_W);
            }
            else if(c == 'B')//Character B denotes boss
            {
                boss *tempBoss = new boss();
                tempBoss->OnLoad("BossDie.png", 64*scaling_factor_W, 64*scaling_factor_H, 10);
                tempBoss->HP = -999;
                tempBoss->X = iX;
                tempBoss->Y = iY;
                tempBoss->enemyBox.hitSurface = LPM_Surface::OnLoad("red.png");
                tempBoss->index = returnList.size();
                returnList.push_back(tempBoss);
                iX += (80*scaling_factor_W);
            }
            else if(c == 'O')//Character O denotes a portal
            {
                portal *tempPortal = new portal();
                tempPortal->OnLoad("Portal.png", 288*scaling_factor_W, 288*scaling_factor_H, 1);
                tempPortal->X = iX;
                tempPortal->Y = iY;
                tempPortal->enemyBox.hitSurface = LPM_Surface::OnLoad("red.png");
                tempPortal->index = returnList.size();
                returnList.push_back(tempPortal);
                iX += (80*scaling_factor_W);
            }
            else iX += (80*scaling_factor_W);
        }
        myfile.close();
        return returnList;
    }
    else myfile.close();
    return returnList; //Eventual plan I think would be to return a default level
}

