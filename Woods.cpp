#include "Woods.h"

using namespace std;

/*
 * CELL FONCTIONS
 */

Cell::Cell(int xc, int yc, int ms) {

	msize = ms;
	x = xc, y = yc;
	setCoords(xc, yc);

	int prob = rand() % 101;

	if (prob < MONSTER_RATE)
		setMonster(true);

	prob = rand() % 101;

	if (prob < CREV_RATE)
		setCrevice(true);

	prob = rand() % 101;

	if (prob < PORTAL_RATE)
		setPortal(true);
}

void Cell::setCoords(int xc = -1, int yc = -1) {

	if (xc != -1)
		x = xc;

	if (yc != -1)
		y = yc;
}

void Cell::setMonster(bool b) {
	m_monster = b;
	/*std::vector<Cell*> neigh = getNeighbours();

	for (auto cell : neigh) {
		cell->setStinky(b);
	}*/
}

void Cell::setCrevice(bool b) {
	m_crevice = b;
	/*std::vector<Cell*> neigh = getNeighbours();

	for (auto cell : neigh) {
		cell->setWindy(b);
	}*/
}

void Cell::killMonster() {
	setMonster(false);
}

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

std::ostream &operator<<(std::ostream &output, const Cell *c) {

	output << "|";

	if (c != nullptr) {
		if (c->hasMonster())
			output << "M";
		else
			output << "0";

		if (c->hasCrevice())
			output << " - C";
		else
			output << " - 0";

		if (c->hasPortal())
			output << "- P";
		else
			output << "- 0";
	}

	return output;
}

std::ostream &operator<<(std::ostream &output, const Woods &w) {

	for (const auto &i: w.map) {
		for (auto j: i)
			output << j << " ";
		output << endl;
	}

	return output;
}
