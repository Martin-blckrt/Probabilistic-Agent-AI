#include "Woods.h"

using namespace std;

/*
 * WOODS FONCTIONS
 */

Woods::Woods(int msize) {

	mapsize = msize;
	for (int i = 0; i < msize; i++) {
		vector<Cell *> v;

		for (int j = 0; j < msize; j++)
			v.push_back(new Cell(i, j, msize));

		map.push_back(v);
	}
}

Woods::~Woods() {

	for (auto &i: map)
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
		for (auto j: i)
			output << j << " ";
		output << endl;
	}

	return output;
}
