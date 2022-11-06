#pragma once

#include "ProblemData.h"
#include "Woods.h"

class Cell {

private:
	int x; int y;
	int msize;
	int exit_rate = EXIT_RATE;

	bool m_agent = false;
	bool m_monster = false;
	bool m_stink = false;

	bool m_crevice = false;
	bool m_windy = false;

	bool m_portal = false;
	bool m_exit = false;

	std::vector< std::vector<Cell*> > *map;

public:
	Cell(std::vector< std::vector<Cell*> > *, int, int, int, bool, bool);

	void setCoords(int x, int y);
	std::pair<int, int> getCoords() { return std::make_pair(x, y); }

	void updateAdjCell();
	std::vector<Cell *> getAdjCell();

	bool hasAgent() const{ return m_agent; };
	bool hasMonster() const{ return m_monster; };
	bool hasCrevice() const{ return m_crevice; };
	bool hasPortal() const{ return m_portal; };

	bool isStinky() const{ return m_stink; };
	bool isWindy() const{ return m_windy; };
	bool isExit() const{ return m_exit; };

	void setAgent(bool b) { m_agent = b; };
	void setMonster(bool b);
	void setCrevice(bool b);
	void setPortal(bool b);

	void setStinky(bool b){ m_stink = b; };
	void setWindy(bool b){ m_windy = b; };

	bool tryForExit();
	void setExit(bool b);

	void killMonster();

	friend std::ostream& operator<<(std::ostream&, Cell*);
};