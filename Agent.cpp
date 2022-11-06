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

bool Agent::isDead() {
	return false;
}



