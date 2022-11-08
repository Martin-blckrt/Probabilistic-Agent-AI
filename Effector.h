#pragma once

#include "ProblemData.h"
#include "Woods.h"

class Effector {
private:
	Woods* woods;
public:

	explicit Effector(Woods* w){

		woods = w;
	}

	void throwRock(Cell * c){
		c->killMonster();
	}

	Actions moveAgent(Cell * c) {

		// give cell to map to update agent pos
		woods->setAgentCell(c);

		// check cell to know how to update perf
		if (c->hasCrevice() || c->hasMonster())
			return Actions::death;

		if (c->hasPortal() && c->isExit())
			return Actions::exited;
	}
};

