#pragma once
#include <SFML/Graphics.hpp>

const float DEFAULT_NODE_SIZE = 7;

class Node
{
public:
	Node(float size=DEFAULT_NODE_SIZE, float newx=0, float newy=0, float newz=0);

	void Tick(float delta);

	sf::Color* m_color;

	float m_size = 100; // Percent of original image
	sf::Vector3f location; // Physical world location
	sf::Vector3f view_location; // Position after rotated by camera
};

bool CompareNodes(Node * a, Node * b);