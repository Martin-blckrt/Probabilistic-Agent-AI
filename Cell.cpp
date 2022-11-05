#include "Cell.h"

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

	if (xc != -1 && yc != -1){
		x = xc;
		y = yc;
	}
}

std::vector<Cell *> getAdjCell(){

	

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