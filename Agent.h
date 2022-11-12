#pragma once

#include "ProblemData.h"
#include "Woods.h"
#include "Effector.h"
#include "Sensor.h"

class Agent {

private:
	bool m_dead = false;

	Sensor * sens;
	Effector * eff;

	int performance = 0;

	int deathCount = 0;
	int rockUsed = 0;
	int movesMade = 0;
	int exitFound = 0;

	Woods * woods;

public:

	explicit Agent(Woods * w = nullptr);
	~Agent();

	bool isDead() const;
	void dies(bool b);
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
