#pragma once

#include "ProblemData.h"
#include "Cell.h"

class Cell;
class Woods {
public:

	bool exitable = false;
	int mapsize;

	explicit Woods(int);
	~Woods();

	void generateMap(int);
	void destroyMap();

	int getMapSize() const { return mapsize; };
	void refreshMap();

	Cell* getCell(int, int);
	std::vector< std::vector<Cell*> > * getMap(){ return &map; };

	void setAgentCell(Cell * c);
	Cell* getAgentCell();
	void agentRespawn();

	void setExit(bool b) { exitable = b; }
	bool hasExit() const { return exitable; }

	friend std::ostream& operator<<(std::ostream&, const Woods& );

private:
	std::vector< std::vector < Cell * >> map;
	Cell* agentPosition;
};

