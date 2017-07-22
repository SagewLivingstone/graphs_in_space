#pragma once
#include "Node.h"

class Link
{
public:
	Link(Node* s = nullptr, Node* e = nullptr);

	void Tick(float & delta);
	void UpdateMidpoint();

	Node* a;
	Node* b;

	sf::Vector3f midpoint;

	// Distance
	float max_distance;
	float distance;
	float velocity;

	// Visual
	float thickness;
};