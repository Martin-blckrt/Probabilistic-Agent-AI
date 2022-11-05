#pragma once

#include "ProblemData.h"

class Cell {
	friend class Woods;

private:
	int x; int y; int msize;

	bool m_monster = false;
	bool m_stink = false;

	bool m_crevice = false;
	bool m_windy = false;

	bool m_portal = false;
	bool m_exit = false;

public:
	Cell(int, int, int);

	void setCoords(int x, int y);
	std::pair<int, int> getCoords() { return std::make_pair(x, y); }

	bool hasMonster() const{ return m_monster; };
	bool hasCrevice() const{ return m_crevice; };
	bool hasPortal() const{ return m_portal; };

	bool isStinky() const{ return m_stink; };
	bool isWindy() const{ return m_windy; };

	void setMonster(bool b);
	void setCrevice(bool b);
	void setPortal(bool b){ m_portal = b; };

	void setStinky(bool b){ m_stink = b; };
	void setWindy(bool b){ m_windy = b; };

	void killMonster();

	friend std::ostream& operator<<(std::ostream&, const Cell*);
};

class Woods {
public:

	int mapsize;

	explicit Woods(int);
	~Woods();

	int getMapSize() { return mapsize; };
	Cell* getCell(int, int);

	friend std::ostream& operator<<(std::ostream&, const Woods& );

private:
	std::vector< std::vector<Cell*> > map;
};

