#pragma once
#include "Node.h"

class Link
{
public:
	Link(Node* s = nullptr, Node* e = nullptr);

	Node* a;
	Node* b;

	float thickness;
};