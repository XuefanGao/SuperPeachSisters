#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
Actor::Actor(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* world)
    :GraphObject(imageID, startX, startY, dir, depth, size)
{
    // alive
    m_world = world;
    
}

bool Actor::isAlive() {
    if (m_hp > 0)
        return true;
    return false;
}

StudentWorld* Actor::getWorld() {
    return m_world;
}

void Actor::setHp(int h) {
    m_hp = h;
}


Peach::Peach(int startX, int startY, StudentWorld* world)
    : Actor(IID_PEACH, startX, startY, 0, 0, 1.0, world) {
    setHp(1);
    // alive
    m_isInvincible = false;
    
    // no special power
    
}

void Peach::doSomething() {
    if (isAlive() == false) {
        return;
    }
    if (m_isInvincible == true) {
        // decrement the number of remaining game ticks before she loses this invincibility power.If this tick count reaches zero, Peach must set her invincibility status to off.
    }
    // 3. check temporarily invincible

    // 4. check recharge mode

    // 5. check overlap

    // 6. 

    // 7. 

    // 8. if player pressed a key
    int key;
    if (getWorld()->getKey(key) == true) {
        double x = getX();
        double y = getY();
        double xnew;
        double ynew;
        switch (key) {
        case KEY_PRESS_LEFT:
            setDirection(180);
            xnew = x - 4;
            ynew = y;
            if (getWorld()->isBlockingObjectAt(xnew, ynew)) {
                //peach bonk
                // peach doesn't move
            }  
            else {
                moveTo(xnew, ynew);
            }
            break;


        case KEY_PRESS_RIGHT:
            setDirection(0);
            xnew = x + 4;
            ynew = y;
            if (getWorld()->isBlockingObjectAt(xnew, ynew)) {
                //peach bonk
                // peach doesn't move
            }
            else {
                moveTo(xnew, ynew);
            }
            break;

        case KEY_PRESS_UP:
            //setDirection(180);
            xnew = x;
            ynew = y + 4;
            getWorld()->playSound(SOUND_PLAYER_JUMP);
            if (getWorld()->isBlockingObjectAt(xnew, ynew)) {
                //peach bonk
                // peach doesn't move
            }
            else {
                moveTo(xnew, ynew);
            }
            break;
        }
        //....
    }


}


Block::Block(int startX, int startY, StudentWorld* world) 
    :Actor(IID_BLOCK, startX, startY, 0, 2, 1.0, world)
{
    setHp(1);
}

void Block::doSomething() {

}

Pipe::Pipe(int startX, int startY, StudentWorld* world)
    : Actor(IID_PIPE, startX, startY, 0, 2, 1.0, world)
{
    setHp(1);
}

void Pipe::doSomething() {

}

Flag::Flag(int startX, int startY, StudentWorld* world)
    : Actor(IID_FLAG, startX, startY, 0, 1, 1.0, world)
{
    setHp(1);
}

void Flag::doSomething() {

}

Mario::Mario(int startX, int startY, StudentWorld* world)
    : Actor(IID_MARIO, startX, startY, 0, 1, 1.0, world)
{
    setHp(1);
}

void Mario::doSomething() {

}


//---------------------
Goodie::Goodie(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* world)
    : Actor(imageID, startX, startY, dir, depth, size, world)
{
    
}


Flower::Flower(int startX, int startY, StudentWorld* world)
    : Goodie(IID_FLOWER, startX, startY, 0, 1, 1.0, world)
{
    setHp(1);
}

Mushroom::Mushroom(int startX, int startY, StudentWorld* world)
    : Goodie(IID_MUSHROOM, startX, startY, 0, 1, 1.0, world)
{
    setHp(1);
}

Star::Star(int startX, int startY, StudentWorld* world)
    : Goodie(IID_STAR, startX, startY, 0, 1, 1.0, world)
{
    setHp(1);
}

