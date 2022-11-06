#include "Cell.h"

using namespace std;

/*
 * CELL FONCTIONS
 */

Cell::Cell(std::vector< std::vector<Cell*> > * m, int xc, int yc, int ms, bool agent, bool forcedPortal) {

	msize = ms;
	x = xc, y = yc;
	map = m;

	bool smgSpawned = false;

	if (agent)
	{
		setAgent(true);
		return;
	}

	if (forcedPortal){
		setPortal(true);
		return;
	}

	int prob = rand() % 101;

	if (prob < MONSTER_RATE){
		setMonster(true);
		smgSpawned = true;
	}

	prob = rand() % 101;
	if (prob < CREV_RATE && !smgSpawned)
	{
		setCrevice(true);
		smgSpawned = true;
	}

	prob = rand() % 101;
	if (prob < PORTAL_RATE && !smgSpawned)
	{
		setPortal(true);
		// useless : smgSpawned = true;
	}
}

void Cell::setCoords(int xc = -1, int yc = -1) {

	if (xc != -1 && yc != -1) {
		x = xc;
		y = yc;
	}
}

void Cell::updateAdjCell() {

	bool bm = hasMonster(), bc = hasCrevice();

	std::vector<Cell*> neigh = getAdjCell();

	for (auto cell : neigh) {

		cell->setStinky(bm);
		cell->setWindy(bc);
	}
}

std::vector<Cell *> Cell::getAdjCell() {

	std::vector<Cell *> neigh;

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

	setStinky(b);

	if (r == msize && c == msize)
		updateAdjCell();
}

void Cell::setCrevice(bool b) {
	m_crevice = b;

	size_t r = (*map).size();
	size_t c = r != 0 ? (*map)[0].size() : 0;

	setStinky(b);

	if (r == msize && c == msize)
		updateAdjCell();
}

void Cell::setPortal(bool b) {
	m_portal = b;

	if (b)
		tryForExit();
}

bool Cell::tryForExit() {

	bool b = false;
	int prob = rand() % 101;
	
	if(prob < exit_rate)
	{
		b = true;
		setExit(true);
	}

	return b;
}

void Cell::setExit(bool b) {

	m_exit = b;
	if(b) exit_rate = 0;
}

void Cell::killMonster() {
	setMonster(false);
}

std::ostream &operator<<(std::ostream &output, Cell *c) {

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

		if (c->hasPortal() && c->isExit())
			output << " - EP";
		else if(c->hasPortal())
			output << " - NP";
		else
			output << " - 0 ";

		if (c->hasAgent())
			output << " - A";
		else
			output << " - 0";

		output << " (";

		if (c->isStinky())
			output << "S";

		if (c->isWindy())
			output << "W";

		output << ")";
	}

	if (c->getCoords().second == c->msize - 1)
		output << " |";

	return output;
}