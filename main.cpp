#include <iostream>
#include <unistd.h>
#include <chrono>

#include "ProblemData.h"
#include "Woods.h"
#include "Agent.h"

#define LIFES 10000
#define TEST_DURATION 2s

using namespace std;
using namespace std::chrono;

int main() {

    cout << "Probabilistic agent - TP3 " << endl << endl;

    srand(time(nullptr));

    int msize = INITIAL_MAPSIZE;

    auto sherwood = new Woods(msize);
    auto hobbit = new Agent(sherwood);

    vector<vector<double>> perf = {{0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1},
                                   {0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0}};

    int index = 0;
    for (auto RR: perf[0]) {
        cout << "Computing performance for rock rate " << RR << " ..." << endl;
        auto start = high_resolution_clock::now();
        bool elapsed = false;

        vector<double> perfs_for_rr;
        hobbit->setPerf(0);

        while (!elapsed) {
            msize = INITIAL_MAPSIZE;

            while (!hobbit->isDead()) {
                sherwood->generateMap();
                hobbit->wakes(RR);

                while (!hobbit->isDead() && !hobbit->foundExit())
                    hobbit->makeMove();

                if (hobbit->foundExit()) {
                    msize++;
                    hobbit->forgetEverything();
                    sherwood->setMapSize(msize);
                }
            }

            perfs_for_rr.push_back(hobbit->getPerf());
            hobbit->dies(false);
            auto current_time = high_resolution_clock::now();
            elapsed = duration_cast<seconds>(current_time - start) >= TEST_DURATION;
        }
        perf[1][index] = accumulate(perfs_for_rr.begin(), perfs_for_rr.end(), 0.0) / LIFES;
        index++;
    }

    cout << "\n" << endl;

    for (int i = 0; i < perf[0].size(); i++)
        cout << "Performance for rock rate at " << perf[0][i] << " is : " << perf[1][i] << endl;

    cout << "\nThe best rate is " << perf[0][max_element(perf[1].begin(), perf[1].end()) - perf[1].begin()] << endl;
    double bestRockRate = perf[0][max_element(perf[1].begin(), perf[1].end()) - perf[1].begin()];
    msize = INITIAL_MAPSIZE;
	sherwood->setMapSize(msize);
    cout << "\nPress a key to continue to simualtion" << endl;
    fflush(stdin);
    getchar();


    while (true) {
        sherwood->generateMap();
        hobbit->wakes(bestRockRate);

        cout << "The woods are changing ! " << "(" << msize << "x" << msize << ")" << endl;
        cout << "Starting map" << endl;
        cout << *sherwood << endl;

        while (!hobbit->isDead() && !hobbit->foundExit()) {
            hobbit->makeMove();
            sleep(3);
            cout << *sherwood << endl;
        }

        if (hobbit->foundExit()) {
            msize++;
            cout << "Hobbit found exit ! Moving on...\n" << endl;
        }

        if (hobbit->isDead()) {
            msize = INITIAL_MAPSIZE;
            cout << "Hobbit is dead ! Resetting...\n" << endl;
        }

        hobbit->forgetEverything();
        sherwood->setMapSize(msize);
    }
}