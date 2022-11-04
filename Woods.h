#pragma once

#include "ProblemData.h"

class Cell {
	friend class Woods;

private:
	bool m_monster = false;
	bool m_stink = false;

	bool m_crevice = false;
	bool m_windy = false;

	bool m_portal = false;
	bool m_exit = false;

public:
	Cell();

	bool hasMonster() const{ return m_monster; };
	bool hasCrevice() const{ return m_crevice; };
	bool hasPortal() const{ return m_portal; };

	bool isStinky() const{ return m_stink; };
	bool isWindy() const{ return m_windy; };
	bool isExit() const{ return m_exit; };

	void setMonster(bool b){
		m_monster = b;
		// smell logic
	};

	void setCrevice(bool b){
		m_crevice = b;
		// windy logic
	};

	void setPortal(bool b){
		m_portal = b;
	};

	void killMonster(){ setMonster(false); }

	friend std::ostream& operator<<(std::ostream&, const Cell*);

};

class Woods {
public:

	int mapsize;

	Woods(int);
	~Woods();

	int getMapSize() const { return mapsize; };
	Cell* getCell(int, int);

	friend std::ostream& operator<<(std::ostream&, const Woods& );

private:
	std::vector< std::vector<Cell*> > map;
};

