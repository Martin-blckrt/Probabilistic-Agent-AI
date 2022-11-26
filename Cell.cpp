#include "Cell.h"

using namespace std;

/*
 * CELL FONCTIONS
 */

Cell::Cell(Woods *w, int xc, int yc, bool agent, bool forcedPortal) {

	x = xc, y = yc;
	woods = w;
	msize = woods->mapsize;

	bool smgSpawned = false;

	if (agent){
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

	vector<Cell*> neigh = getAdjCell();

	for (auto& cell : neigh) {

		if (bm)
			cell->setStinky(bm);

		if (bc)
			cell->setWindy(bc);
	}
}

vector<Cell *> Cell::getAdjCell() {

	vector<Cell *> neigh;

	if (x + 1 < msize)
		neigh.push_back(woods->getCell(x + 1, y));

	if (x - 1 >= 0)
		neigh.push_back(woods->getCell(x - 1, y));

	if (y + 1 < msize)
		neigh.push_back(woods->getCell(x, y + 1));

	if (y - 1 >= 0)
		neigh.push_back(woods->getCell(x, y - 1));

	neigh.shrink_to_fit();
	return neigh;
}

void Cell::setMonster(bool b) {
	m_monster = b;
	setStinky(b);
}

void Cell::setCrevice(bool b) {
	m_crevice = b;
	setWindy(b);
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
	if(b) reduceExitRate();
}

void Cell::reduceExitRate() {

	for (const auto& r : *woods->getMap())
		for(auto c : r)
			c->exit_rate = 0;
}

void Cell::killMonster() {
	setMonster(false);

	vector<Cell*> neigh = getAdjCell();

	for (auto& cell : neigh) {

		vector<Cell*> cell_neigh = getAdjCell();

		bool monsterNear = false;
		for (auto& cn : cell_neigh){
			if (cn->hasMonster()){
				monsterNear = true;
				break;
			}
		}

		if (!monsterNear)
			cell->setStinky(false);
	}
}

ostream &operator<<(ostream &output, Cell *c) {

	output << "##";

	if (c != nullptr) {

        output << " ";

		if (c->hasMonster())
			output << " M";
		else if (c->hasCrevice())
			output << " C";
		else if (c->hasPortal() && c->isExit())
			output << "EP";
		else if(c->hasPortal() && c->hasAgent())
			output << "P";
        else if (c->hasAgent())
            output << " A";
        else
            output << "  ";

        output << " ";

        if (c->isStinky() && c->isWindy())
            output << "SW";
		else if (c->isStinky())
			output << "S ";
		else if (c->isWindy())
			output << "W ";
        else
            output << "  ";

        output << " ";
	}

	if (c->getCoords().second == c->msize - 1)
		output << "##";

	return output;

}