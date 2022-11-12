#include "Agent.h"
#include <algorithm>

using namespace std;

Agent::Agent(Woods * w) {

	woods = w;

	eff = new Effector(w);
	sens = new Sensor(w);
}

Agent::~Agent() {

	delete eff;
	delete sens;
}

bool Agent::isDead() const {
	return m_dead;
}

void Agent::dies(bool b) {
	m_dead = b;

	if(b)
	{
		visited.clear();
		woods->agentRespawn();
	}
}

void Agent::throwRock(){

	// decide if we kill

	eff->throwRock(nullptr);
	performance += Actions::rock;
}

bool Agent::isVisited(Cell* cell) {
    auto it = find(visited.begin(), visited.end(), cell);
    return (it != visited.end());
}

double Agent::computeCellSafeProb(Cell* cell) {
    int stinkCount = 0;
    int windCount = 0;
    bool hasMonster = false;
    bool hasCrevice = false;
    vector<Cell*> neigh = cell->getAdjCell();
    for (auto n : neigh) {
        if (isVisited(n)) {
            if (n->isStinky())
                stinkCount++;
            if (n->isWindy())
                windCount++;
        }
    }
}

Cell* Agent::chooseNextCell() {
    pair <Cell*, double> safestCell;
    for (auto c : frontier) {
        if (computeCellSafeProb(c) > safestCell.second)
            safestCell = make_pair(c, computeCellSafeProb(c));
        else if (computeCellSafeProb(c) == safestCell.second) {
            //check for monster val or other departaging
            // if better swap
        }
    }
    return safestCell.first;
}

void Agent::makeMove() {

    // decide which cell
    Cell *cell = chooseNextCell();

    //send chosen cell
    Actions curr_action = eff->moveAgent(cell);

    if (curr_action == Actions::death || curr_action == Actions::exited) {
        if (curr_action == Actions::death)
            performance += curr_action;

        if (curr_action == Actions::exited)
            performance += curr_action;

    } else {
        visited.push_back(cell);
        for (auto n: cell->getAdjCell())
            if (!isVisited(n))
                frontier.push_back(n);
    }

    performance += Actions::move;
}



