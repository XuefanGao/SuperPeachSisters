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
	virtual int init();
	virtual int move();
	virtual void cleanUp();

	// below are added functions
	bool readLevel();  // return false if fails to load a level, true otherwise
	bool isBlockingObjectAt(double x, double y); // returns true if there exists an object in map at x,y
private:
	// Peach pointer
	Peach* m_peach;
	// array of pointers to track all actors
	std::vector<Actor*> actorList;


};

#endif // STUDENTWORLD_H_
