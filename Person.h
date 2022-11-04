#pragma once

#include "ProblemData.h"
#include "Woods.h"

class Person {

private:
	bool m_dead = false;

public:

	Person();

	bool isDead() const { return m_dead; }

	std::map<Cell*, std::pair<int, int>> visited;
};
