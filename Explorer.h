#pragma once

#include "ProblemData.h"
#include "Woods.h"

class Node{
	friend class Explorer;

private:
	float m_proba = 0.0;
	Node* parent = nullptr;

public:
	Node();
	~Node();

	float getProba() const { return m_proba; }
	Node* getParent() { return parent; }

	std::vector<Node*> children;
};
typedef Node * Child;

class Explorer {

private:
	Woods * map;

public:
	Explorer(Woods*);
	~Explorer();
};

