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

void Agent::wakes() {
	m_dead = false;
	setExitFound(false);
	sens->updateSurroundings(visited, frontier);
}

void Agent::dies(bool b) {
	m_dead = b;

	if(b)
	{
		visited.clear();
		frontier.clear();

		performance = 0;
	}
}

void Agent::throwRock(Cell* cell){

	eff->throwRock(cell);
	performance += Actions::rock;
}

bool Agent::isVisited(Cell* cell) {
    auto it = find(visited.begin(), visited.end(), cell);
    return (it != visited.end());
}

double Agent::computeCellSafeProb(Cell* cell) {
    double monster_prob = computeMonsterProb(cell);
    double crev_prob = computeCreviceProb(cell);
    return (1-monster_prob) * (1-crev_prob);
}

double Agent::computeCreviceProb(Cell* cell) {
    int windCount = 0;
    vector<Cell*> neigh = cell->getAdjCell();
    for (auto n : neigh) {
        if (isVisited(n)) {
            if (n->isWindy())
                windCount++;
        }
    }
    double crev_prob = (CREV_RATE/100)*windCount;
    return crev_prob;
}

double Agent::computeMonsterProb(Cell* cell) {
    int stinkCount = 0;
    vector<Cell*> neigh = cell->getAdjCell();
    for (auto n : neigh) {
        if (isVisited(n)) {
            if (n->isStinky())
                stinkCount++;
        }
    }
    double monster_prob = (MONSTER_RATE/100)*stinkCount;
    return monster_prob;
}

Cell* Agent::chooseNextCell() {

    pair <Cell*, double> safestCell;

	for (auto c : frontier) {

        if (computeCellSafeProb(c) > safestCell.second)
            safestCell = make_pair(c, computeCellSafeProb(c));

        else if (computeCellSafeProb(c) == safestCell.second && safestCell.second != 0) {

            if (computeCreviceProb(c) < computeCreviceProb(safestCell.first))
                safestCell = make_pair(c, computeCellSafeProb(c));
        }
    }

    return safestCell.first;
}

void Agent::setExitFound(bool b) {
	exitFound = b;
}

bool Agent::foundExit() const {
	return exitFound;
}

int Agent::getPerf() const {
	return performance;
}

void Agent::makeMove() {

    // decide which cell
    Cell *cell = chooseNextCell();

	auto coords = cell->getCoords();
	cout << "I chose " << coords.first << ", " << coords.second << endl;

    if (computeMonsterProb(cell) > ROCK_THRESHOLD)
        throwRock(cell);

    //send chosen cell
    Actions curr_action = eff->moveAgent(cell);

    if (curr_action == Actions::death || curr_action == Actions::exited) {
        if (curr_action == Actions::death) {
            dies(true);
            performance += curr_action;
			cout << "I died !" << endl;
        }

        if (curr_action == Actions::exited) {
	        setExitFound(true);
            performance += curr_action;
	        cout << "I am out !" << endl;
		}

    } else {
        visited.push_back(cell);
	    remove(frontier.begin(), frontier.end(),cell);

        for (auto n: cell->getAdjCell())
            if (!isVisited(n))
                frontier.push_back(n);
    }

    performance += Actions::move;
}



