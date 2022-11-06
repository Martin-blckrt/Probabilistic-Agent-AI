#pragma once

#include "ProblemData.h"
#include "Woods.h"

class Effector {
private:
	Woods* woods;
public:

	explicit Effector(Woods* w){

		woods = w;
	}

	void move() {

	}
};

