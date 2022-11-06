#include "Woods.h"

using namespace std;

/*
 * WOODS FONCTIONS
 */

Woods::Woods(int msize) {

	mapsize = msize;

	int probX = rand() % mapsize;
	int probY = rand() % mapsize;

	for (int i = 0; i < mapsize; i++) {
		vector<Cell *> v;

		for (int j = 0; j < msize; j++){

			bool agentHere = probX == i && probY == j;
			bool forcedPortal = !hasExit() && (i == mapsize - 1 && j == mapsize - 1);

			auto c = new Cell(&map, i, j, mapsize, agentHere, forcedPortal);

			if(c->isExit())
				setExit(true);

			v.push_back(c);
		}

		map.push_back(v);
	}

	bool cellUpdated = false, exit_created = false;

	while (!hasExit() || !cellUpdated){

		for (const auto& r : map) {
			for(auto c : r){

				c->updateAdjCell();

				if (c->hasPortal() && !exit_created)
					if (c->tryForExit())
						exit_created = true;

			}
		}

		cellUpdated = true;
	}
}

Woods::~Woods() {

	for (const auto& i: map)
		for (auto &j: i)
			delete j;
}

Cell* Woods::getCell(int x, int y) {

	if ((x >= 0 && x < mapsize) && (y >= 0 && y < mapsize))
		return map[x][y];
	else
		return nullptr;
}

/*
 * OUTPUT FONCTIONS
 */

std::ostream &operator<<(std::ostream &output, const Woods &w) {

	for (const auto &i: w.map) {
		cout << " ------------------------------------------------------------" << endl;
		for (auto j: i)
			output << j << " ";
		output << endl;
	}
	cout << " ------------------------------------------------------------" << endl;

	return output;
}

Cell *Woods::getAgentCell() {
	for(const auto& r : map)
		for(auto c : r)
			if (c->hasAgent())
				return c;
}
