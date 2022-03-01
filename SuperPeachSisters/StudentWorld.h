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

	enum goodieType { noGoodie, mushroom, flower, star };

	// accessor and mutator
	Actor* getActor(int index);
	Peach* getPeach();
	int getPeachDirection();
	void setPeachReachFlag();
	void setPeachReachMario();

	// below are added functions
	bool readLevel();  // return false if fails to load a level, true otherwise
	bool isObjectAt(int x, int y); // returns true if x,y exists an object(except peach)
	//bool getBlocked(double a, double b); // return true if actor at a,b will get blocked by an object (except peach)
	bool isBlockObjectAt(int x, int y);
	int overlapActor(double a, double b);
	int overlapBlockActor(double a, double b);
	int overlapDamageableActor(double a, double b);
	bool overlapPeach(double a, double b); // retuen true if actor at a, b overlap with peach
	void pushActorList(Actor* a); // push a new actor to world's actorList

	// private
	void updatesStatusLine();
private:
	
	Peach* m_peach;    // Peach pointer
	std::vector<Actor*> m_actorList;    // array of pointers to track all actors

	bool m_peach_reach_flag;       // initialized to false
	bool m_peach_reach_mario;     // initialized to flase

};

#endif // STUDENTWORLD_H_
