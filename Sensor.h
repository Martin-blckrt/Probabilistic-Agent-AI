#pragma once

#include "ProblemData.h"
#include <algorithm>

class Sensor {

private:
	Woods* woods;

public:
	explicit Sensor(Woods* w){
		woods = w;
	}

	void updateSurroundings(std::vector<Cell*>& v, std::vector<Cell*>& fr)
	{
		auto agentpos = woods->getAgentCell();

		auto it = find(v.begin(), v.end(), agentpos);

		if (it == v.end())
			v.push_back(agentpos);

		for(auto c : agentpos->getAdjCell()) {
			auto itfr = find(fr.begin(), fr.end(), c);

			if (itfr == fr.end())
				fr.push_back(c);
		}
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

