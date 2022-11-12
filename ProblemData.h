#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <random>

#include "bayes.h"

#define INITIAL_MAPSIZE 3

#define MONSTER_RATE 20
#define CREV_RATE 20
#define PORTAL_RATE 30
#define EXIT_RATE 30

#define MOVE_COST (-1)
#define EXIT_FOUND 10
#define DEATH (-10)
#define ROCK_COST (-10)

#define ROCK_THRESHOLD 0.4

enum Actions {move = MOVE_COST, exited = EXIT_FOUND, death= DEATH, rock = ROCK_COST};