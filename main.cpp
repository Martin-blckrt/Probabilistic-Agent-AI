#include <iostream>

#include "ProblemData.h"
#include "Woods.h"
#include "Agent.h"

using namespace std;

int main(){

	cout << "Probabilistic agent - TP3 " << endl << endl;

	srand(time(nullptr));

	int msize = INITIAL_MAPSIZE;

	while (true)
	{
		auto* sherwood = new Woods(msize);
		auto* hobbit = new Agent(sherwood);

		cout << "The woods are growing " << "(" << msize << "x" << msize << ")" << endl;
		cout << *sherwood << endl;

		if (!hobbit->isDead())
		{
			// main stuff
		}

		// if exit is reached, do these 2 :
		delete hobbit;
		delete sherwood;

		msize++;
		break;
	}

	return 0;
}