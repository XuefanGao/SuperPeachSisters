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
	// insert here
	Actor(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* world);
	virtual void doSomething() = 0;
	bool isAlive();
	StudentWorld* getWorld();
	void setHp(int h);
	
private:
	
	int m_hp;
	StudentWorld* m_world;
};



// may add public/private functions and private data members
class Peach : public Actor
{
public:
	Peach(int startX, int startY, StudentWorld* world);
	virtual void doSomething();

private:
	bool m_isInvincible;



};


class Block : public Actor 
{
public:
	Block(int startX, int startY, StudentWorld* world);
	virtual void doSomething();
private:

};

class Pipe : public Actor
{
public:
	Pipe(int startX, int startY, StudentWorld* world);
	virtual void doSomething();
private:

};

class Flag : public Actor
{
public:
	Flag(int startX, int startY, StudentWorld* world);
	virtual void doSomething();
private:

};

class Mario : public Actor
{
public:
	Mario(int startX, int startY, StudentWorld* world);
	virtual void doSomething();
private:

};




class Goodie : public Actor
{
public:
	Goodie(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* world);
private:

};

class Flower : public Goodie
{
public:
	Flower(int startX, int startY, StudentWorld* world);
	//virtual void doSomething();
private:

};


class Mushroom : public Goodie
{
public:
	Mushroom(int startX, int startY, StudentWorld* world);
	//virtual void doSomething();
private:

};

class Star : public Goodie
{
public:
	Star(int startX, int startY, StudentWorld* world);
	//virtual void doSomething();
private:

};






class Goomba : public Actor
{
public:
	
};


#endif // ACTOR_H_
