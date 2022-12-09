#include "Agent.h"
#include <algorithm>
#include <cstdlib>

using namespace std;

Agent::Agent(Woods *w) {

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

void Agent::wakes(double rr) {
    m_dead = false;
    setExitFound(false);
    forgetEverything();
    sens->updateSurroundings(visited, frontier);
    rock_rate = rr;
}

void Agent::forgetEverything() {
    visited.clear();
    frontier.clear();
}

void Agent::dies(bool b) {
    m_dead = b;

    if (b)
        forgetEverything();
}

void Agent::throwRock(Cell *cell) {

    eff->throwRock(cell);
    performance += Actions::rock;
}

bool Agent::isVisited(Cell *cell) {
    auto it = find(visited.begin(), visited.end(), cell);
    return (it != visited.end());
}

double Agent::computeCellSafeProb(Cell *cell) {
    double monster_prob = computeMonsterProb(cell);
    double crev_prob = computeCreviceProb(cell);
    return (1 - monster_prob) * (1 - crev_prob);
}

double Agent::computeCreviceProb(Cell *cell) {
    double windCount = 0;
    vector<Cell *> neigh = cell->getAdjCell();
    for (auto n: neigh) {
        if (isVisited(n)) {
            if (n->isWindy())
                windCount++;
        }
    }
    double crev_prob = ((double) CREV_RATE / 100) * windCount;
    return crev_prob;
}

double Agent::computeMonsterProb(Cell *cell) {
    double stinkCount = 0;
    vector<Cell *> neigh = cell->getAdjCell();
    for (auto n: neigh) {
        if (isVisited(n)) {
            if (n->isStinky())
                stinkCount++;
        }
    }
    double monster_prob = ((double) MONSTER_RATE / 100) * stinkCount;
    return monster_prob;
}

Cell *Agent::chooseNextCell() {

    pair<Cell *, double> safestCell;

    for (auto c: frontier) {
        if (computeCellSafeProb(c) > safestCell.second)
            safestCell = make_pair(c, computeCellSafeProb(c));

        else if (computeCellSafeProb(c) == safestCell.second && safestCell.second != 0) {

            if (computeCreviceProb(c) < computeCreviceProb(safestCell.first))
                safestCell = make_pair(c, computeCellSafeProb(c));
        }
    }
    if (safestCell.first)
        return safestCell.first;
}

void Agent::setExitFound(bool b) {
    exitFound = b;
}

bool Agent::foundExit() const {
    return exitFound;
}

void Agent::setPerf(int p) {
    performance = p;
}

int Agent::getPerf() const {
    return performance;
}

double Agent::getRR() const {
    return rock_rate;
}

void Agent::makeMove() {

    // decide which cell
    Cell *cell = chooseNextCell();

    if (cell != nullptr) {
        auto coords = cell->getCoords();
        //cout << "I chose " << coords.first << ", " << coords.second << endl;

        if (computeMonsterProb(cell) > rock_rate)
            throwRock(cell);

        auto agCellCoords = woods->getAgentCell()->getCoords();
        int manhattan = abs(agCellCoords.first - coords.first) + abs(agCellCoords.second - coords.second);

        // send chosen cell
        Actions curr_action = eff->moveAgent(cell);

        if (curr_action == Actions::death || curr_action == Actions::exited) {
            int sz = woods->getMapSize();

            if (curr_action == Actions::death)
                dies(true);

            if (curr_action == Actions::exited)
                setExitFound(true);

            performance += curr_action * (sz * sz);

        } else {
            frontier.erase(find(frontier.begin(), frontier.end(), cell));
            visited.push_back(cell);

            for (auto n: cell->getAdjCell())
                if (!isVisited(n))
                    frontier.push_back(n);
        }

        performance += Actions::move * manhattan;
    }

}



