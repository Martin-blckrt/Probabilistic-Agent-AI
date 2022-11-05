#include "Cell.h"

using namespace std;

/*
 * CELL FONCTIONS
 */

Cell::Cell(std::vector< std::vector<Cell*> > * m, int xc, int yc, int ms) {

	msize = ms;
	x = xc, y = yc;
	map = m;

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

	if (xc != -1 && yc != -1) {
		x = xc;
		y = yc;
	}
}

void Cell::updateAdjCell() {

	bool b;
	std::vector<Cell*> neigh = getAdjCell();

	for (auto cell : neigh) {
		b = hasMonster();
		cell->setStinky(b);

		b = hasCrevice();
		cell->setWindy(b);
	}
}

std::vector<Cell *> Cell::getAdjCell() {

	std::vector<Cell *> neigh(4);

	if (x + 1 < msize)
		neigh.push_back((*map)[x + 1][y]);

	if (x - 1 >= 0)
		neigh.push_back((*map)[x - 1][y]);

	if (y + 1 < msize)
		neigh.push_back((*map)[x][y + 1]);

	if (y - 1 >= 0)
		neigh.push_back((*map)[x][y - 1]);

	neigh.shrink_to_fit();
	return neigh;
}

void Cell::setMonster(bool b) {
	m_monster = b;

	size_t r = (*map).size();
	size_t c = r != 0 ? (*map)[0].size() : 0;

	if (r == msize && c == msize)
		updateAdjCell();
}

void Cell::setCrevice(bool b) {
	m_crevice = b;

	size_t r = (*map).size();
	size_t c = r != 0 ? (*map)[0].size() : 0;

	if (r == msize && c == msize)
		updateAdjCell();
}

void Cell::killMonster() {
	setMonster(false);
}

std::ostream &operator<<(std::ostream &output, const Cell *c) {

	output << "|";

	if (c != nullptr) {
		if (c->hasMonster())
			output << " M";
		else
			output << " 0";

		if (c->hasCrevice())
			output << " - C";
		else
			output << " - 0";

		if (c->hasPortal())
			output << " - P";
		else
			output << " - 0";
	}

	output << " |";

	return output;
}