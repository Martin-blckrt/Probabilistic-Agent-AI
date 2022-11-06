#pragma once

#include "ProblemData.h"

class Sensor {

private:
	Woods* woods;

public:
	explicit Sensor(Woods* w){
		woods = w;
	}

	Cell* locateAgent() {
		return woods->getAgent();
	}
};

