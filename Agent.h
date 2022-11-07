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

	Woods * woods;

public:

	explicit Agent(Woods * w = nullptr);
	~Agent();

	bool isDead() const;
	void move();

	std::map<Cell*, std::pair<int, int>> visited;
};
