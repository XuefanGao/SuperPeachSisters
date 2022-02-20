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
    decLives();
    return GWSTATUS_PLAYER_DIED;
}

void StudentWorld::cleanUp()
{
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
        ge = lev.getContentsOf(5, 10); // x=5, y=10
        switch (ge)
        {
        case Level::empty:
            cout << "Location 5,10 is empty" << endl; // insert actors here
            break;
        case Level::koopa:
            cout << "Location 5,10 starts with a koopa" << endl;
            break;
        case Level::goomba:
            cout << "Location 5,10 starts with a goomba" << endl;
                break;
        case Level::peach:
            cout << "Location 5,10 is where Peach starts" << endl;
            // put peach
            break;
        case Level::flag:
            cout << "Location 5,10 is where a flag is" << endl;
            break;
        case Level::block:
            cout << "Location 5,10 holds a regular block" << endl;
            break;
        case Level::star_goodie_block:
            cout << "Location 5,10 has a star goodie block" << endl;
            break;
            // etc…
        }
        return true;
    }
}

bool StudentWorld::isBlockingObjectAt(double x, double y) {
    return false; // dummy
}