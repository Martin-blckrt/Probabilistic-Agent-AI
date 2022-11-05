#pragma once

#include "ProblemData.h"
#include "Woods.h"

class Agent {

private:
	bool m_dead = false;

public:

	Agent();

	bool isDead() const { return m_dead; }

	std::map<Cell*, std::pair<int, int>> visited;
};
