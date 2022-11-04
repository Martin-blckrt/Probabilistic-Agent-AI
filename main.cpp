#include <iostream>

#include "ProblemData.h"
#include "Woods.h"
#include "Person.h"

using namespace std;

int main(){

	int msize = INITIAL_MAPSIZE;
	auto* hobbit = new Person();

	while (true)
	{
		auto* sherwood = new Woods(msize);

		cout << "Loading woods of size " << msize << endl;

		// if exit is reached, do these 2 :
		delete sherwood;
		msize++;
	}

	return 0;
}