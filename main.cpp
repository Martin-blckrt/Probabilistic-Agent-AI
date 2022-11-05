#include <iostream>

#include "ProblemData.h"
#include "Woods.h"
#include "Agent.h"

using namespace std;

int main(){

	cout << "Probabilistic agent - TP3 " << endl << endl;

	srand(time(nullptr));

	int msize = INITIAL_MAPSIZE;
	auto* hobbit = new Agent();

	//while (true)
	//{
		auto* sherwood = new Woods(msize);

		cout << "Loading woods of size " << msize << endl;
		cout << "Current woods : " << endl << *sherwood << endl;

		// if exit is reached, do these 2 :
		delete sherwood;
		msize++;
	//}

	return 0;
}