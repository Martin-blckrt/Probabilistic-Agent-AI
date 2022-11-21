#include <iostream>

#include "ProblemData.h"
#include "Woods.h"
#include "Agent.h"

using namespace std;

int main(){

	cout << "Probabilistic agent - TP3 " << endl << endl;

	srand(time(nullptr));

	int msize = INITIAL_MAPSIZE;

	auto sherwood = new Woods(msize);
	auto hobbit = new Agent(sherwood);

	while (true)
	{
		sherwood->generateMap();
		hobbit->wakes();

		cout << "The woods are changing ! " << "(" << msize << "x" << msize << ")" << endl;
		cout << "Starting map" << endl;
		cout << *sherwood << endl;

		while (!hobbit->isDead() && !hobbit->foundExit()) {
			hobbit->makeMove();
			cout << *sherwood << endl;
		}

		if (hobbit->isDead())
			msize = sherwood->mapsize;

		if (hobbit->foundExit())
			msize++;

		hobbit->forgetEverything();
		sherwood->setMapSize(msize);

		cout << "Agent performance was : " << hobbit->getPerf() << endl;
	}

	return 0;
}