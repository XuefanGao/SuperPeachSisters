#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    m_peach = nullptr;
    vector<Actor*> m_actorList;
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}

int StudentWorld::init()
{
    // if no level data file exists for current level
    bool rl = readLevel();
    if ( rl == false) {
        return GWSTATUS_LEVEL_ERROR;
    }


    // Initialize the data structures to keep track of your game’s world.
    // Allocate and insert a Peach object into the game world. Every time a level starts
    // or restarts, Peach starts out fully initialized(with the no special powers active,
    // etc.) in her initial location as specified by the current level data file.
    // Allocate and insert all of the blocks, pipes, flags, enemiesand Mario into the
    // game world as described below

    // thought: append actors to the vector in readlevel

    // load level data from level file


    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    // ask all actors to doSomething
    updatesStatusLine();

    if (m_peach->isAlive())
        m_peach->doSomething();

    for (auto it = std::begin(m_actorList); it != std::end(m_actorList); ++it) {
        if((*it)->isAlive())
            (*it)->doSomething();
        if (m_peach->isAlive() == false) {
            playSound(SOUND_PLAYER_DIE);
            return GWSTATUS_PLAYER_DIED;
        }
    }
    
    if (peachReachFlagAt(0, 0)) {
        playSound(SOUND_FINISHED_LEVEL);
        return GWSTATUS_FINISHED_LEVEL;
    }

    // if peach reach mario


    // delete dead obj
    for (auto it = std::begin(m_actorList); it != std::end(m_actorList); ++it) {
        // if((*it)->isAlive() == false)
            // remove (*it)
    }


    // update status text

    // 
    // decLives();
    // return GWSTATUS_PLAYER_DIED;
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    for (auto it = std::begin(m_actorList); it != std::end(m_actorList); ++it) {
        delete* it;
        it = m_actorList.erase(it);
    }
    if (m_peach != nullptr){
        delete m_peach;
        m_peach = nullptr;
    }
}

Actor* StudentWorld::getActor(int index) {
    return m_actorList[index];
}

int StudentWorld::getPeachDirection() {
    return m_peach->getDirection();
}



bool StudentWorld::readLevel() {
    Level lev(assetPath());
    string level_file = "level01.txt";
    Level::LoadResult result = lev.loadLevel(level_file);
    if (result == Level::load_fail_file_not_found)
        return false;
    else if (result == Level::load_fail_bad_format)
        return false;
    else if (result == Level::load_success)
    {
        cerr << "Successfully loaded level" << endl;
        Level::GridEntry ge;
        for (int x = 0; x < GRID_WIDTH; x++) {
            for (int y = 0; y < GRID_HEIGHT; y++) {
                ge = lev.getContentsOf(x, y); // x=5, y=10
                switch (ge)
                {
                case Level::empty:
                    break;

                case Level::peach:
                    m_peach = new Peach(x * SPRITE_WIDTH, y * SPRITE_HEIGHT, this);
                    break;

                case Level::block:
                    m_actorList.push_back(new Block(x * SPRITE_WIDTH, y * SPRITE_HEIGHT, this));
                    break;

                case Level::pipe:
                    m_actorList.push_back(new Pipe(x * SPRITE_WIDTH, y * SPRITE_HEIGHT, this));
                    break;

                case Level::mushroom_goodie_block:
                    m_actorList.push_back(new Block(x * SPRITE_WIDTH, y * SPRITE_HEIGHT, this));
                    break;

                case Level::flower_goodie_block:
                    m_actorList.push_back(new Block(x * SPRITE_WIDTH, y * SPRITE_HEIGHT, this));
                    break;

                case Level::star_goodie_block:
                    m_actorList.push_back(new Block(x * SPRITE_WIDTH, y * SPRITE_HEIGHT, this));
                    break;

                case Level::flag:
                    m_actorList.push_back(new Flag(x * SPRITE_WIDTH, y * SPRITE_HEIGHT, this));
                    break;

                case Level::goomba:
                    m_actorList.push_back(new Goomba(x * SPRITE_WIDTH, y * SPRITE_HEIGHT, this));
                    break;

                case Level::koopa:
                    m_actorList.push_back(new Koopa(x * SPRITE_WIDTH, y * SPRITE_HEIGHT, this));
                    break;

                case Level::piranha:
                    m_actorList.push_back(new Piranha(x * SPRITE_WIDTH, y * SPRITE_HEIGHT, this));
                    break;
                
                
                
                    // etc…
                }
            }
        }
        
        
        return true;
    }
}

 /*helper
 helper, returns true if an object(except peach) is appearing at (x,y)*/
bool StudentWorld::isObjectAt(int x, int y) {
    int arr[VIEW_WIDTH][VIEW_HEIGHT] = { 0 };
    for (auto it = std::begin(m_actorList); it != std::end(m_actorList); ++it) {
        int xx = (*it)->getX();
        int yy = (*it)->getY();
        for(int i = xx; i <xx + SPRITE_WIDTH; i++){
            for (int j = yy; j < yy + SPRITE_HEIGHT; j++) {
                arr[i][j] = 1;
            }
        }
    }
    if(arr[x][y] == 0){
        return false;
    }

    return true;
}

// if actor exist at a,b will get blocked by an actor (except peach), return the index of the object 
// otherwise, won't get blocked, return -1
int StudentWorld::overlapActor(double a, double b) {
    int x = int(a);
    int y = int(b);
    // check the pixels around the given location
    for (int i = x; i < x + SPRITE_WIDTH; i++) {
        for (int j = y; j < y + SPRITE_HEIGHT; j++) {
            //if (isBlockingObjectAt(i, j))
                //return true;
            // iterate through actor list
            for (int index = 0; index < m_actorList.size(); index++) {
                int actorX = m_actorList[index]->getX();
                int actorY = m_actorList[index]->getY();
                for (int ii = actorX; ii <actorX + SPRITE_WIDTH; ii++) {
                    for (int jj = actorY; jj < actorY + SPRITE_HEIGHT; jj++) {
                        if (ii == i && jj == j) {
                            return index;
                        }     
                    }
                }
            }
        }
    }
    return -1;
}


int StudentWorld::overlapDamageableActor(double a, double b) {
    int x = int(a);
    int y = int(b);
    // check the pixels around the given location
    for (int i = x; i < x + SPRITE_WIDTH; i++) {
        for (int j = y; j < y + SPRITE_HEIGHT; j++) {
            //if (isBlockingObjectAt(i, j))
                //return true;
            // iterate through actor list
            for (int index = 0; index < m_actorList.size(); index++) {
                if (m_actorList[index]->isDamageable() == false) {
                    break;
                }
                int actorX = m_actorList[index]->getX();
                int actorY = m_actorList[index]->getY();
                for (int ii = actorX; ii < actorX + SPRITE_WIDTH; ii++) {
                    for (int jj = actorY; jj < actorY + SPRITE_HEIGHT; jj++) {
                        if (ii == i && jj == j) {
                            return index;
                        }
                    }
                }
            }
        }
    }
    return -1;
}



// returns true if object at a,b will overlap with peach
bool StudentWorld::overlapPeach(double a, double b) {
    int x = int(a);
    int y = int(b);
    int peachX = int(m_peach->getX());
    int peachY = int(m_peach->getY());

    if (peachX - 4 < x && x < peachX + 4 && peachY - 4 < y && y < peachY + 4)
        return true;
    /*for (int i = x; i < x + SPRITE_WIDTH; i++) {
        for (int j = y; j < y + SPRITE_HEIGHT; j++) {
            if (peachX-4 < i && i < peachX + 4 && peachY-4 < j && j < peachY + 4)
                return true;
        }
    }*/
    
    return false;
}

void StudentWorld::pushActorList(Actor* a) {
    m_actorList.push_back(a);
}

// ========== private =====================

// returns true of peach reach flag at x,y
bool StudentWorld::peachReachFlagAt(double x, double y) {
    return false; // dummy
}


void StudentWorld::updatesStatusLine()
{
    int lives = getLives();
    int level = getLevel();
    int points = getScore();
    ostringstream status;
    status << "Lives: " << lives << "  Level: " << level << " Points: " << points;
    setGameStatText(status.str());
}



Peach* StudentWorld::getPeach() {
    return m_peach;
}