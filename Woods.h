#pragma once

#include "ProblemData.h"
#include "Cell.h"

class Cell;
class Woods {
public:

	int mapsize;

	explicit Woods(int);
	~Woods();

	int getMapSize() const { return mapsize; };
	Cell* getCell(int, int);
	std::vector< std::vector<Cell*> > * getMap(){ return &map; };

	friend std::ostream& operator<<(std::ostream&, const Woods& );

private:
	std::vector< std::vector < Cell * >> map;
};

