#pragma once

#include "ProblemData.h"
#include "Woods.h"

class Person {

private:
	bool m_dead = false;

public:

	Person();
	~Person();

	bool isDead() const { return m_dead; }
};
