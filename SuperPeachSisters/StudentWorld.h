#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include <string>
// below are added includes
#include "Actor.h"
#include <vector>
#include "Level.h"

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp
// may add public/private funcs and private data members

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetPath);
	~StudentWorld();
	virtual int init();
	virtual int move();
	virtual void cleanUp();

	// accessor 
	Actor* getActor(int index);
	Peach* getPeach();
	int getPeachDirection();

	// below are added functions
	bool readLevel();  // return false if fails to load a level, true otherwise
	bool isObjectAt(int x, int y); // helper, returns true if x,y exists an object(except peach)
	//bool getBlocked(double a, double b); // return true if actor at a,b will get blocked by an object (except peach)
	bool isBlockObjectAt(int x, int y);
	int overlapActor(double a, double b);
	int overlapBlockActor(double a, double b);
	int overlapDamageableActor(double a, double b);
	bool overlapPeach(double a, double b); // retuen true if actor at a, b overlap with peach
	void pushActorList(Actor* a); // push a new actor to world's actorList

	// private
	void updatesStatusLine();
	bool peachReachFlagAt(double x, double y); 
private:
	// Peach pointer
	Peach* m_peach;
	// array of pointers to track all actors
	std::vector<Actor*> m_actorList;


};

#endif // STUDENTWORLD_H_
