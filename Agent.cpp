#include "Agent.h"

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

void Agent::makeMove() {

	// decide which cell

	//send chosen cell
	Actions curr_action = eff->moveAgent(nullptr);

	if(curr_action == Actions::death) {

		performance += curr_action;
	}

	if(curr_action == Actions::exited)
		performance += curr_action;

	performance += Actions::move;

}



