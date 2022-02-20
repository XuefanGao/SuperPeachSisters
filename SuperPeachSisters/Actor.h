#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
//below is added
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor : public GraphObject {
public:
	// insert here
	Actor(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* world);
	virtual void doSomething() = 0;
	bool isAlive();
	StudentWorld* getWorld();
	
private:
	
	int m_hp;
	StudentWorld* m_world;
};



// may add public/ private data members
class Peach : public Actor
{
public:
	Peach(int startX, int startY, StudentWorld* world);
	virtual void doSomething();

private:
	bool m_isInvincible;



};



class Goomba : public Actor
{
public:
	
};

class Goodie : public Actor
{
public:
	
};
#endif // ACTOR_H_
