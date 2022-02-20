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

Peach::Peach(int startX, int startY, StudentWorld* world)
    : Actor(IID_PEACH, startX, startY, 0, 0, 1.0, world) {
    // hp = 1
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
        switch (key) {
        case KEY_PRESS_LEFT:
            setDirection(180);
            moveTo(x - 4, y);
            break;


        case KEY_PRESS_RIGHT:
            break;

        case KEY_PRESS_UP:
            break;

        case KEY_PRESS_DOWN:
            break;

        }
        //....
    }


}