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
		return woods->getAgentCell();
	}

    bool feelWind(Cell* cell) {
        return cell->isWindy();
    }

    bool smellStink(Cell* cell) {
        return cell->isStinky();
    }
};

