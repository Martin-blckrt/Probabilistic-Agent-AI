#include <iostream>

#include "ProblemData.h"
#include "Woods.h"
#include "Agent.h"

#define LIFES 100

using namespace std;

int main() {

    cout << "Probabilistic agent - TP3 " << endl << endl;

    srand(time(nullptr));

    int msize = INITIAL_MAPSIZE;

    auto sherwood = new Woods(msize);
    auto hobbit = new Agent(sherwood);

    vector<vector<double>> perf = {{0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    int index = 0;
    for (auto RR: perf[0]) {
        cout << "Computing performance for rock rate " << RR << " ..." << endl;

        vector<double> perfs_for_rr;

        for (int life = LIFES; life > 0; life--) {
            cout << "Hobbit is on life " << life << endl;
            msize = INITIAL_MAPSIZE;

            while (!hobbit->isDead()) {
                sherwood->generateMap();
                hobbit->wakes(RR);

                //cout << "The woods are changing ! " << "(" << msize << "x" << msize << ")" << endl;
                //cout << "Starting map" << endl;
                //cout << *sherwood << endl;

                while (!hobbit->isDead() && !hobbit->foundExit()) {
                    hobbit->makeMove();
                    //cout << *sherwood << endl;
                }

                //cout << "Agent performance was : " << hobbit->getPerf() << endl;

                if (hobbit->foundExit()) {
                    msize++;
                    hobbit->forgetEverything();
                    sherwood->setMapSize(msize);
                }
            }

            perfs_for_rr.push_back(hobbit->getPerf());
            hobbit->dies(false);
            hobbit->setPerf(0);
        }
        perf[1][index] = accumulate(perfs_for_rr.begin(), perfs_for_rr.end(), 0.0)/LIFES;
        index++;
    }

    for (int i = 0; i < perf[0].size(); i++)
            cout << "Performance for rock rate at " << perf[0][i] << " is : " << perf[1][i] << endl;

    //double m = max_element(perf[1].begin(), perf[1].end())[0];
    //double bestRockRate = perf[][0];


    return 0;
}