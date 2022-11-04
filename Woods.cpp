#include "Woods.h"

using namespace std;

/*
 * CELL FONCTIONS
 */

Cell::Cell() {

}

/*
 * WOODS FONCTIONS
 */

Woods::Woods() {

	map = vector<vector<Cell*>>(MAPSIZE, vector<Cell*>(MAPSIZE, new Cell()));
}

Woods::~Woods() {

	for (auto & i : map)
		for (auto & j : i)
			delete j;
}

Cell* Woods::getCell(int x, int y) {

	if ((x >= 0 && x < MAPSIZE) && (y >= 0 && y < MAPSIZE))
		return map[x][y];
	else
		return nullptr;
}

/*
 * OUTPUT FONCTIONS
 */

std::ostream &operator<<(std::ostream & output, const Cell * c) {

	output << "|";

	if(c != nullptr)
	{
		if(c->hasMonster())
			output << "M";
		else
			output << "0";

		if(c->hasCrevice())
			output << "C";
		else
			output << "0";

		if(c->hasPortal())
			output << "P";
		else
			output << "0";
	}
}

std::ostream &operator<<(std::ostream & output, const Woods & w) {

	for (const auto& i : w.map)
	{
		for (auto j : i)
			output << j << " ";
		output << endl;
	}

	return output;
}
