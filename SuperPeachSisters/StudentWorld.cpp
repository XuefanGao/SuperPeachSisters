#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

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
    // load level data from level file
    m_peach_reach_flag = false;
    m_peach_reach_mario = false;
    bool rl = readLevel();
    if ( rl == false) {
        return GWSTATUS_LEVEL_ERROR;
    }

    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    // ask all actors to doSomething
    

    // 1. ask all actors to do something
    if (m_peach->isAlive())
        m_peach->doSomething();
    for (auto it = std::begin(m_actorList); it != std::end(m_actorList); ++it) {
        if((*it)->isAlive())
            (*it)->doSomething();
        if (m_peach->isAlive() == false) {
            decLives();
            playSound(SOUND_PLAYER_DIE);
            decLives();
            return GWSTATUS_PLAYER_DIED;
        }
    }
    

    // 2. if peach reach flag, advance to next level
    if (m_peach_reach_flag) {
        playSound(SOUND_FINISHED_LEVEL);
        return GWSTATUS_FINISHED_LEVEL;
    }
        
    // 3. if peach reach mario
    if (m_peach_reach_mario) {
        playSound(SOUND_GAME_OVER);
        return GWSTATUS_PLAYER_WON;
    }

    // 4. delete dead during tick
    for (auto it = std::begin(m_actorList); it != std::end(m_actorList); ++it) {
        if ((*it)->isAlive() == false) {
            m_actorList.vector::erase(it);
            it++;
        }
    }

    // update status text
    updatesStatusLine();

    if(m_peach->isAlive() && !m_peach_reach_flag && !m_peach_reach_mario)
        return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    for (auto it = std::begin(m_actorList); it != std::end(m_actorList); ++it) {
        m_actorList.vector::erase(it);
        it++;
    }
    if (m_peach != nullptr){
        delete m_peach;
        m_peach = nullptr;
    }
    if (getLives() > 0) {
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
    string level_file;
    switch (getLevel()) {
    case 1:
        level_file = "level01.txt";
        break;
    case 2:
        level_file = "level02.txt";
        break;
    case 3:
        level_file = "level03.txt";
        break;
    }
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
                    m_actorList.push_back(new Block(x * SPRITE_WIDTH, y * SPRITE_HEIGHT, noGoodie, this));
                    break;

                case Level::pipe:
                    m_actorList.push_back(new Pipe(x * SPRITE_WIDTH, y * SPRITE_HEIGHT, this));
                    break;

                case Level::mushroom_goodie_block:
                    m_actorList.push_back(new Block(x * SPRITE_WIDTH, y * SPRITE_HEIGHT, mushroom, this));
                    break;

                case Level::flower_goodie_block:
                    m_actorList.push_back(new Block(x * SPRITE_WIDTH, y * SPRITE_HEIGHT, flower, this));
                    break;

                case Level::star_goodie_block:
                    m_actorList.push_back(new Block(x * SPRITE_WIDTH, y * SPRITE_HEIGHT, star, this));
                    break;

                case Level::flag:
                    m_actorList.push_back(new Flag(x * SPRITE_WIDTH, y * SPRITE_HEIGHT, this));
                    break;

                case Level::mario:
                    m_actorList.push_back(new Mario(x * SPRITE_WIDTH, y * SPRITE_HEIGHT, this));
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
    else
        return false;
}

// returns true if pixel(x,y) is occupied by an object
bool StudentWorld::isObjectAt(int x, int y) {
    for (auto it = std::begin(m_actorList); it != std::end(m_actorList); ++it) {
        int xx = (*it)->getX();
        int yy = (*it)->getY();
        if (x - SPRITE_WIDTH < xx && xx < x + 1 && y - SPRITE_HEIGHT < yy && yy < y + 1)
            return true;
    }
    return false;
}


bool StudentWorld::isBlockObjectAt(int x, int y) {
    for (auto it = std::begin(m_actorList); it != std::end(m_actorList); ++it) {
        if ((*it)->canBlock() == false)
            continue;
        int xx = (*it)->getX();
        int yy = (*it)->getY();
        if (x - SPRITE_WIDTH < xx && xx < x + 1 && y - SPRITE_HEIGHT < yy && yy < y + 1)
            return true;
    }
    return false;
}

// if actor exist at a,b will overlap an actor (except peach), return the index of the object 
// otherwise, won't get blocked, return -1
int StudentWorld::overlapActor(double a, double b) {
    for (int i = 0; i < m_actorList.size(); i++) {
        
        int x = m_actorList[i]->getX();
        int y = m_actorList[i]->getY();
        if (a - SPRITE_WIDTH < x && x < a + SPRITE_WIDTH && b - SPRITE_HEIGHT < y && y < b + SPRITE_HEIGHT)
            return i;
    }
    return -1;
}

int StudentWorld::overlapBlockActor(double a, double b) {
    for (int i = 0; i < m_actorList.size(); i++) {
        if (m_actorList[i]->canBlock() == false)
            continue;
        int x = m_actorList[i]->getX();
        int y = m_actorList[i]->getY();
        if (a - SPRITE_WIDTH < x && x < a + SPRITE_WIDTH && b - SPRITE_HEIGHT < y && y < b + SPRITE_HEIGHT)
            return i;
    }
    return -1;
}

int StudentWorld::overlapDamageableActor(double a, double b) {
    for (int i = 0; i < m_actorList.size(); i++) {
        if (m_actorList[i]->isDamageable() == false)
            continue;
        int x = m_actorList[i]->getX();
        int y = m_actorList[i]->getY();
        if (a - SPRITE_WIDTH < x && x < a + SPRITE_WIDTH && b - SPRITE_HEIGHT < y && y < b + SPRITE_HEIGHT)
            return i;
    }
    return -1;
}



// returns true if object at a,b will overlap with peach
bool StudentWorld::overlapPeach(double a, double b) {
  
    double peachX = m_peach->getX();
    double peachY = m_peach->getY();

    if (peachX - 4 < a && a < peachX + 4 && peachY - 4 < b && b < peachY + 4)
        return true;
    return false;
}

void StudentWorld::pushActorList(Actor* a) {
    m_actorList.push_back(a);
}

// ========== private =====================




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

void StudentWorld::setPeachReachFlag() {
    m_peach_reach_flag = true;
}

void StudentWorld::setPeachReachMario() {
    m_peach_reach_mario = true;
}
