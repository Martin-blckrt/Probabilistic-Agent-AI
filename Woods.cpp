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

Woods::Woods(int msize) {

	map = vector<vector<Cell*>>(msize, vector<Cell*>(msize, new Cell()));
	mapsize = msize;
}

Woods::~Woods() {

	for (auto & i : map)
		for (auto & j : i)
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

	return output;
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
