#include "Actor.h"
#include "StudentWorld.h"
// added
#include <time.h> 
#include <iostream>

// ==============================================================
// ==========  Actor  ===========================================
// ==============================================================
Actor::Actor(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* world)
    :GraphObject(imageID, startX, startY, dir, depth, size)
{
    m_hp = 1;
    m_canBlock = true;
    m_world = world;
    m_damageable = true;
}

int Actor::getHp() {
    return m_hp;
}

void Actor::setHp(int h) {
    m_hp = h;
}

bool Actor::canBlock() {
    return m_canBlock;
}

void Actor::setCanBlock(bool blk) {
    m_canBlock = blk;
}

bool Actor::isDamageable() {
    return m_damageable;
}

void Actor::setDamageable(bool dmg) {
    m_damageable = dmg;
}

bool Actor::isAlive() {
    if (m_hp > 0)
        return true;
    return false;
}

StudentWorld* Actor::getWorld() {
    return m_world;
}

void Actor::reverseDirection() {
    if (getDirection() == 0)
        setDirection(180);
    else if (getDirection() == 180)
        setDirection(0);
}




// ==============================================================
// ==========  Peach  ===========================================
// ==============================================================
Peach::Peach(int startX, int startY, StudentWorld* world)
    : Actor(IID_PEACH, startX, startY, 0, 0, 1.0, world) {
    setCanBlock(false);
    setHp(1);
    // alive
    m_invicible_tick = 0;

    //bool m_isTempInvisible;
    m_temp_invicible_tick = 0;

    //bool m_isRecharge;
    time_to_recharge_before_next_fire = 0;  ///////
    m_canShoot = false;
    remaining_jump_distance = 0;
    m_canMoveUp = true;
    
    // no special power
    m_isFalling = false;

    m_hasJumpPower = false;
    m_hasShootPower = false;
    
}

void Peach::doSomething() {
    if (isAlive() == false) {
        return;
    }


    // 2. Peach must check if she is currently invincible (Star Power)
    if (m_invicible_tick > 0) {
        // decrement the number of remaining game ticks before she loses this invincibility power.
        m_invicible_tick -= 1;

        // If this tick count reaches zero, Peach must set her invincibility status to off.
        if (m_invicible_tick == 0) {
            //m_isInvincible = false;
        }
    
    }


    // 3. check temporarily invincible
    // Peach must check if she is currently temporarily invincible  (Peach gains temporary invincibility if she overlaps with an enemy while
    //        she has Jump Power or Fire Power.)
    if (m_temp_invicible_tick > 0) {
        // decrement the number of remaining game ticks before she loses temporary invincibility
        m_temp_invicible_tick -= 1; 
        // If this tick count reaches zero, Peach must set her temporary invincibility status to false.
        if (m_temp_invicible_tick == 0) {
            // m_temp_invicible_tick = 0;
        }
    }
    
    // 4. check recharge mode
    // Peach must check if she is currently in “recharge” mode before she can fire again. 
    if (time_to_recharge_before_next_fire > 0) {
        time_to_recharge_before_next_fire -= 1;
    }
    if (time_to_recharge_before_next_fire == 0) {
        // Peach may again shoot a fireball(if she has Shoot Power).
        m_canShoot = true;     //if has shoot power
    }

    
    // 5. check overlap
    int overlapIndex = overlap();
    if (overlapIndex != -1) {
        // bonk the overlap object
        getWorld()->getActor(overlapIndex)->bonk();
    }



    
    // ??? does ramaining distance > 0 mean isJumping?
    // 6.  if peach previously initiated a jump and her remaining_jump_distance is > 0
    if ( remaining_jump_distance > 0) {
        // try to move upward by four pixels during the current tick
        // first calculate target x,y
        double x = getX();
        double y = getY();
        double xnew = x;
        double ynew = y+4;
        // if there is object at xnew,ynew
        overlapIndex = getWorld()->overlapActor(xnew, ynew);
        if (overlapIndex != -1) {
            // bonk();
            getWorld()->getActor(overlapIndex)->bonk();
            // abort moving to xnew,ynew
            remaining_jump_distance = 0;
            m_canMoveUp = false;
        }
        else {
            moveTo(xnew, ynew);
            remaining_jump_distance -= 1;   // 1 step closer to reaching the top of her jump

        }
    }


    
    // 7. is not jumping
    else{
    //else if(m_isFalling){
        // check if there is an object that blocks movement between 0 and 3
        // (inclusive)pixels directly below her
        int x = getX();
        int y = getY();
        bool canFall = true;
        for (int i = x; i < x + SPRITE_WIDTH; i++) {
            for (int j = y; j >= y - 3; j--) {
                if (getWorld()->isObjectAt(i, j))
                    canFall = false;
                    //std::cout << canFall;
            }
        }
        
        
        // If not, then Peach must update her y position by -4 pixels (so she is falling downward)
        if (canFall == true) {
            moveTo(double(x), y - 4.0);
        }
    }
    
    // 8. if player pressed a key
    int key;
    bool hasSupport;
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
            overlapIndex = getWorld()->overlapActor(xnew, ynew);
            if (overlapIndex != -1) {
                //peach bonk
                getWorld()->getActor(overlapIndex)->bonk();
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

            overlapIndex = getWorld()->overlapActor(xnew, ynew);
            if (overlapIndex != -1) {
                //peach bonk
                getWorld()->getActor(overlapIndex)->bonk();
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

            // check if there is object that block movement one pixel below her
            hasSupport = false;
            for (int i = x; i < x + SPRITE_WIDTH; i++) {
                if (getWorld()->isObjectAt(i, y - 1))
                    hasSupport = true;
            }
            if (hasSupport == true) {
                // set her remaining_jump_distance to the appropriate value
                if (!m_hasJumpPower)
                    remaining_jump_distance = 8;
                if (m_hasJumpPower)
                    remaining_jump_distance = 12;

                getWorld()->playSound(SOUND_PLAYER_JUMP);
            }
            break;

        case KEY_PRESS_SPACE:
            if (!m_hasShootPower) {
                // do nothing
            }
            else if (time_to_recharge_before_next_fire > 0) {
                // do nothing
            }
            else {
                getWorld()->playSound(SOUND_PLAYER_FIRE);
                time_to_recharge_before_next_fire = 8;
                // xnew, ynew = 4 pixels away in direction she's facing 
                getPositionInThisDirection(getDirection(), 4, xnew, ynew);
                // construct Fireball at xnew, ynew, dir = peach.dir
                getWorld()->pushActorList(new PeachFireball(xnew, ynew, getDirection(), getWorld()));
            }
            break;
        }
        
    }


}

void Peach::bonk() {
    // if Peach either has Star Power (invincibility) or temporary invincibility
    if (m_invicible_tick > 0 || m_temp_invicible_tick > 0) {
        // then do nothing
    }
    else {
        // hp - 1
        setHp(getHp() - 1);
        m_temp_invicible_tick = 10;
        if (m_hasShootPower)
            m_hasShootPower = false;
        if (m_hasJumpPower)
            m_hasJumpPower = false;
        if (getHp() >= 1)
            getWorld()->playSound(SOUND_PLAYER_HURT);
        //if(getHp() <= 0)
            // set peach to dead state
    }
}

void Peach::damage() {

}

void Peach::giveStarPower(int ticks) {
    // made invincible for a specified number of ticks
    m_invicible_tick += ticks;
}


void Peach::giveJumpPower() {
    // able to jump 50% higher until Peach is bonked by an enemy or piranha - fired fireball
    m_hasJumpPower = true;
}


void Peach::giveShootPower() {
    // able to shoot fireballs until Peach is bonked by an enemy or piranha - fired fireball
    m_hasShootPower = true;
}

int Peach::overlap() {
    return getWorld()->overlapActor(getX(), getY());
}


// ==============================================================
// ==========  Block  ===========================================
// ==============================================================
Block::Block(int startX, int startY, StudentWorld* world) 
    :Actor(IID_BLOCK, startX, startY, 0, 2, 1.0, world)
{
    setHp(1);
    hasGoodie = false;
    setDamageable(false);
}

void Block::doSomething() {}

void Block::bonk() {
    getWorld()->playSound(SOUND_PLAYER_BONK);
}

void Block::damage() {} // does nothing
// ==============================================================
// ==========  Pipe  ============================================
// ==============================================================

Pipe::Pipe(int startX, int startY, StudentWorld* world)
    : Actor(IID_PIPE, startX, startY, 0, 2, 1.0, world)
{
    setHp(1);

}

void Pipe::doSomething() {} // does nothing
void Pipe::bonk() {} // nothing happens 
void Pipe::damage() {} // Pipe not damageable

// ==============================================================
// ==========  Flag  ============================================
// ==============================================================

Flag::Flag(int startX, int startY, StudentWorld* world)
    : Actor(IID_FLAG, startX, startY, 0, 1, 1.0, world)
{
    setCanBlock(false);
    setDamageable(false);
    setHp(1);
}

void Flag::doSomething() {
    // if flag is not alive, do nothing
    if (isAlive() == false) {
        return;
    }
    // if flag overlap with peach
    if (getWorld()->overlapPeach(getX(), getY())) {
        getWorld()->increaseScore(1000);
        setHp(0);
        getWorld()->advanceToNextLevel();////////////////////////////////////////////////
    }

}

void Flag::bonk() { } // does nothing when bonked
void Flag::damage() {} // Flag is not damageable
// ==============================================================
// ==========  Mario  ===========================================
// ==============================================================
Mario::Mario(int startX, int startY, StudentWorld* world)
    : Actor(IID_MARIO, startX, startY, 0, 1, 1.0, world)
{
    setCanBlock(false);
    setDamageable(false);
    setHp(1);
}

void Mario::doSomething() {
    // if mario is not alive, do nothing
    if (isAlive() == false) {
        return;
    }
    // if mario overlap with peach
    if (getWorld()->overlapPeach(getX(), getY())) {
        getWorld()->increaseScore(1000);
        setHp(0);
        getWorld()->advanceToNextLevel();//////////////////////////////////
    }
}

void Mario::bonk() {

}

void Mario::damage() {}

// ==============================================================
// ==========  Goodie  ==========================================
// ==============================================================
Goodie::Goodie(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* world)
    : Actor(imageID, startX, startY, dir, depth, size, world)
{
    setHp(1);
    setCanBlock(false);
    setDamageable(false);
}

//void Goodie::doSomething() {}
void Goodie::bonk() {}
void Goodie::damage() {}


// returns true if there is an object just beneath it that would block it 
// from falling two pixels downward
bool Goodie::beneth() {
    int x = getX();
    int y = getY();
    for (int i = x; i < x + SPRITE_WIDTH; i++) {
        for (int j = y - 2; j < y; j++) {
            if (getWorld()->isObjectAt(i, j)) {
                return true;
            }
        }
    }
    return false;
}

// determine what direction it is facing, try to move in that direction by 2 pixels
void Goodie::moveTwo() {
    // calculate target xnew, ynew
    double xnew, ynew;
    getPositionInThisDirection(getDirection(), 2, xnew, ynew);
    // if there is object block movement to xnew, ynew
    if (getWorld()->isObjectAt(int(xnew), int(ynew))) {
        reverseDirection();
        return;
    }
    else {
        moveTo(xnew, ynew);
    }
}

void Goodie::badMoveTwo() {
    // calculate target xnew, ynew
    double xnew, ynew;
    getPositionInThisDirection(getDirection(), 2, xnew, ynew);
    // if there is object block movement to xnew, ynew
    if (getWorld()->isObjectAt(int(xnew), int(ynew))) {
        setHp(0);
        return;
    }
    else {
        moveTo(xnew, ynew);
    }
}


// ==============================================================
// ==========  Flower  ==========================================
// ==============================================================
Flower::Flower(int startX, int startY, StudentWorld* world)
    : Goodie(IID_FLOWER, startX, startY, 0, 1, 1.0, world)
{
    
}

void Flower::doSomething() {
    if (getWorld()->overlapPeach(getX(), getY())) {
        getWorld()->increaseScore(50);
        getWorld()->getPeach()->giveShootPower();
        getWorld()->getPeach()->setHp(2);
        setHp(0);
        getWorld()->playSound(SOUND_PLAYER_POWERUP);
        return;
    }
    else {
        if (!beneth()) {
            moveTo(getX(), getY() - 2);
        }
    }
    moveTwo();
}

void Flower::bonk() {}
void Flower::damage() {}

// ==============================================================
// ==========  Mushroom  ========================================
// ==============================================================
Mushroom::Mushroom(int startX, int startY, StudentWorld* world)
    : Goodie(IID_MUSHROOM, startX, startY, 0, 1, 1.0, world)
{
    setHp(1);
}
void Mushroom::doSomething() {
    if (getWorld()->overlapPeach(getX(), getY())) {
        getWorld()->increaseScore(75);
        getWorld()->getPeach()->giveJumpPower();
        getWorld()->getPeach()->setHp(2);
        setHp(0);
        getWorld()->playSound(SOUND_PLAYER_POWERUP);
        return;
    }
    else {
        if (!beneth()) {
            moveTo(getX(), getY() - 2);
        }
    }
    moveTwo();
}

void Mushroom::bonk() {}
void Mushroom::damage() {}
// ==============================================================
// ==========  Star  ============================================
// ==============================================================
Star::Star(int startX, int startY, StudentWorld* world)
    : Goodie(IID_STAR, startX, startY, 0, 1, 1.0, world)
{
    setHp(1);
}
void Star::doSomething() {
    if (getWorld()->overlapPeach(getX(), getY())) {
        getWorld()->increaseScore(100);
        getWorld()->getPeach()->giveStarPower(150);
        setHp(0);
        getWorld()->playSound(SOUND_PLAYER_POWERUP);
        return;
    }
    //else {
        if (!beneth()) {
            moveTo(getX(), getY() - 2);
        }
    //}
    moveTwo();
}

void Star::bonk() {}
void Star::damage() {}


// ==============================================================
// ==========  Piranha Fireball  ==================================
// ==============================================================
PiranhaFireball::PiranhaFireball(int startX, int startY, int dir, StudentWorld* world)
    : Goodie(IID_PIRANHA_FIRE, startX, startY, dir, 1, 1, world)
{
    
    setHp(1);
}

void PiranhaFireball::doSomething() {
    // check if overlap with peach
    if (getWorld()->overlapPeach(getX(), getY())) {
        getWorld()->getPeach()->damage();
        setHp(0);
        return;
    }
    if (!beneth()) {
        moveTo(getX(), getY() - 2);
    }
    badMoveTwo();
}

void PiranhaFireball::bonk() {}

void PiranhaFireball::damage() {}


// ==============================================================
// ==========  Peach Fireball  ==================================
// ==============================================================
PeachFireball::PeachFireball(int startX, int startY, int dir, StudentWorld* world)
    : Goodie(IID_PEACH_FIRE, startX, startY, dir, 1, 1, world)
{
}

void PeachFireball::doSomething() {
    // if overlaps damageable obj
    int index = getWorld()->overlapDamageableActor(getX(), getY());
    if (index != -1) {
        getWorld()->getActor(index)->damage();
        setHp(0);
        return;
    }
    if (!beneth()) {
        moveTo(getX(), getY() - 2);
    }
    badMoveTwo();
}

void PeachFireball::bonk() {}
void PeachFireball::damage() {}



// ==============================================================
// ==========  Shell  ===========================================
// ==============================================================
Shell::Shell(int startX, int startY, int dir, StudentWorld* world)
    : Goodie(IID_SHELL, startX, startY, dir, 1, 1, world)
{
    setHp(1);
}

void Shell::doSomething() {
    // check if overlap with damageable obj
    int index = getWorld()->overlapDamageableActor(getX(), getY());
    if (index != -1) {
        getWorld()->getActor(index)->damage();
        setHp(0);
        return;
    }
    if (!beneth()) {
        moveTo(getX(), getY() - 2);
    }
    badMoveTwo();
}

void Shell::bonk() {}
void Shell::damage() {}

// ==============================================================
// ==========  Goomba  ==========================================
// ==============================================================
Goomba::Goomba(int startX, int startY, StudentWorld* world)
    : Actor(IID_GOOMBA, startX, startY, (rand() % 2)*180, 1, 0, world)
{
    setHp(1);
}
void Goomba::doSomething() {

}

void Goomba::bonk() {

}

void Goomba::damage() {}
// ==============================================================
// ==========  Koopa  ===========================================
// ==============================================================
Koopa::Koopa(int startX, int startY, StudentWorld* world)
    : Actor(IID_KOOPA, startX, startY, (rand() % 2) * 180, 1, 0, world)
{
    //setHp(1);
}
void Koopa::doSomething() {

}

void Koopa::bonk() {

}

void Koopa::damage() {}
// ==============================================================
// ==========  Piranha  =========================================
// ==============================================================
Piranha::Piranha(int startX, int startY, StudentWorld* world)
    : Actor(IID_PIRANHA, startX, startY, (rand() % 2) * 180, 1, 0, world)
{
    //setHp(1);
}
void Piranha::doSomething() {

}

void Piranha::bonk() {

}

void Piranha::damage() {}
