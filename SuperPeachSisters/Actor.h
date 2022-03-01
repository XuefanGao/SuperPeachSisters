#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
//below is added
class StudentWorld;
#include "GameController.h"
#include "GameWorld.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor : public GraphObject {
public:
	// Constructor
	Actor(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* world);
	
	// accessors and mutators
	int getHp();
	void setHp(int h);
	StudentWorld* getWorld();
	bool canBlock();
	void setCanBlock(bool blk);
	bool isDamageable();
	void setDamageable(bool dmg);
	bool isAlive();  // returns true if hp > 0

	// virtual functions
	virtual void doSomething() = 0;
	virtual void bonk() = 0;  
	virtual void damage() = 0;

	// helper functions
	void reverseDirection();
	int facePeach(); // returns the direction if actor is facing peach
private:
	int m_hp;
	bool m_canBlock;  // returns true if can block others, initialized to true
	bool m_damageable; // returns true if can be damaged, default true
	StudentWorld* m_world;

	
};



// may add public/private functions and private data members
class Peach : public Actor
{
public:
	Peach(int startX, int startY, StudentWorld* world);

	// accessors and mutators
	bool hasStar();
	bool m_canShoot();            // true when peach has shoot power and recharging <= 0
	void giveStarPower(int ticks);
	void giveJumpPower();
	void giveShootPower();
	
	virtual void doSomething();
	virtual void bonk();
	virtual void damage();

private:
	// star power
	int m_invicible_tick;
	int m_temp_invicible_tick;

	// shoot power
	bool m_hasShootPower;
	int time_to_recharge_before_next_fire;
	

	// jump power
	bool m_hasJumpPower;           
	int remaining_jump_distance;

	bool m_isFalling;

};

class Block : public Actor 
{
public:
	
	Block(int startX, int startY, int goodie, StudentWorld* world);
	virtual void doSomething();
	virtual void bonk();
	virtual void damage();
private:
	int m_goodie;  // enum goodieType
	bool m_released;
};

class Pipe : public Actor
{
public:
	Pipe(int startX, int startY, StudentWorld* world);
	virtual void doSomething();
	virtual void bonk();
	virtual void damage();
private:

};

class Flag : public Actor
{
public:
	Flag(int startX, int startY, StudentWorld* world);
	virtual void doSomething();
	virtual void bonk();
	virtual void damage();
private:

};

class Mario : public Actor
{
public:
	Mario(int startX, int startY, StudentWorld* world);
	virtual void doSomething();
	virtual void bonk();
	virtual void damage();
private:

};




class Goodie : public Actor
{
public:
	Goodie(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* world);
	virtual void doSomething() = 0;
	virtual void bonk();
	virtual void damage();
	bool beneth();   //returns true if there is an object just beneath it two pixels downward
	void moveTwo();
	void badMoveTwo();
private:

};

class Flower : public Goodie
{
public:
	Flower(int startX, int startY, StudentWorld* world);
	virtual void doSomething();
	virtual void bonk();
	virtual void damage();
private:

};


class Mushroom : public Goodie
{
public:
	Mushroom(int startX, int startY, StudentWorld* world);
	virtual void doSomething();
	virtual void bonk();
	virtual void damage();
private:

};

class Star : public Goodie
{
public:
	Star(int startX, int startY, StudentWorld* world);
	virtual void doSomething();
	virtual void bonk();
	virtual void damage();
private:

};

class PiranhaFireball : public Goodie
{
public:
	PiranhaFireball(int startX, int startY, int dir, StudentWorld* world);
	virtual void doSomething();
	virtual void bonk();
	virtual void damage();
private:
};

class PeachFireball : public Goodie
{
public:
	PeachFireball(int startX, int startY, int dir, StudentWorld* world);
	virtual void doSomething();
	virtual void bonk();
	virtual void damage();
private:
};

class Shell : public Goodie
{
public:
	Shell(int startX, int startY, int dir, StudentWorld* world);
	virtual void doSomething();
	virtual void bonk();
	virtual void damage();
private:
};


class Monster : public Actor
{
public:
	Monster(int imageID, int startX, int startY, StudentWorld* world);
	virtual void doSomething();
	virtual void bonk();
	virtual void damage();
private:

};
class Goomba : public Monster
{
public:
	Goomba(int startX, int startY, StudentWorld* world);
	//virtual void doSomething();
	// virtual void bonk();
	// virtual void damage();
private:

};

class Koopa : public Monster
{
public:
	Koopa(int startX, int startY, StudentWorld* world);
	//virtual void doSomething();
	//virtual void bonk();
	//virtual void damage();
private:
};


class Piranha : public Monster
{
public:
	Piranha(int startX, int startY, StudentWorld* world);
	virtual void doSomething();
	// virtual void bonk();
	// virtual void damage();
private:
	int m_fire_delay;
};



#endif // ACTOR_H_
