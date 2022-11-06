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

	Map * map;

public:

	Agent();

	bool isDead() const { return m_dead; }
	void move();

	std::map<Cell*, std::pair<int, int>> visited;
};
