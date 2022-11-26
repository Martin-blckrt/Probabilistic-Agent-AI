#include "Woods.h"

using namespace std;

/*
 * WOODS FONCTIONS
 */

Woods::Woods(int msize) {
	mapsize = msize;
}

void Woods::generateMap() {

	if (!map.empty())
		destroyMap();

    exitable = false;

	int probX = rand() % mapsize;
	int probY = rand() % mapsize;

	for (int i = 0; i < mapsize; i++) {
		vector<Cell *> v;

		for (int j = 0; j < mapsize; j++){

			bool agentHere = probX == i && probY == j;
			bool forcedPortal = !hasExit() && (i == mapsize - 1 && j == mapsize - 1);

			auto c = new Cell(this, i, j, agentHere, forcedPortal);

			if (agentHere)
				agentPosition = c;

			if(c->isExit())
				setExit(true);

			v.push_back(c);
		}

		map.push_back(v);
	}

	bool exit_created = false;

	while (!hasExit()){

		for (const auto& r : map) {
			for(auto c : r){

				if (c->hasPortal() && !exit_created)
					if (c->tryForExit()){
						setExit(true);
						exit_created = true;
					}
			}
		}
        cout << "let me ouuuut" << endl;
	}

	refreshMap();
}

Woods::~Woods() {

	destroyMap();
}

void Woods::destroyMap() {

	for (auto i: map) {
		for (auto j : i)
			delete j;
		i.clear();
	}

	map.clear();
}

void Woods::refreshMap() {

	for (auto& r : map)
		for (auto& c : r)
			c->updateAdjCell();

}

Cell* Woods::getCell(int x, int y) {

	if ((x >= 0 && x < mapsize) && (y >= 0 && y < mapsize))
		return map[x][y];
	else
		return nullptr;
}

void Woods::setAgentCell(Cell * c) {

	agentPosition->setAgent(false);
	agentPosition = c;
	agentPosition->setAgent(true);
}

Cell *Woods::getAgentCell() {

	Cell* agentCell = nullptr;

	for(const auto& r : map)
		for(auto c : r)
			if (c->hasAgent())
				agentCell = c;

	return agentCell;
}

/*
 * OUTPUT FONCTIONS
 */

ostream &operator<<(ostream &output, const Woods &w) {

	for (const auto &i: w.map) {
        for (auto t = 0; t < w.mapsize; t++)
            cout << "#########";
		cout << "##" << endl;
		for (auto j: i)
			output << j ;
		output << endl;
	}
    for (auto t = 0; t < w.mapsize; t++)
        cout << "#########";
    cout << "##" << endl;
	return output;

}

