#pragma once

#include "ProblemData.h"
#include "Woods.h"
#include "Effector.h"
#include "Sensor.h"

class Agent {

private:
	bool m_dead = false;
	bool exitFound = false;

	Sensor * sens;
	Effector * eff;

	int performance = 0;

	Woods * woods;

public:

	explicit Agent(Woods * w = nullptr);
	~Agent();

	bool isDead() const;
	void dies(bool b);
	void wakes();

	void setExitFound(bool b);
	bool foundExit() const;
	int getPerf() const;

	void throwRock(Cell*);
	void makeMove();
    bool isVisited(Cell*);
    double computeCellSafeProb(Cell*);
    double computeCreviceProb(Cell*);
    double computeMonsterProb(Cell*);
    Cell* chooseNextCell();

	std::vector<Cell*> visited;
    std::vector<Cell*> frontier;
};
