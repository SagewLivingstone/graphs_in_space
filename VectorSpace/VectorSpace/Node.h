#pragma once
#include <SFML/Graphics.hpp>

const float DEFAULT_NODE_SIZE = 7;

class Node
{
public:
	Node(float size=DEFAULT_NODE_SIZE, float newx=0, float newy=0, float newz=0);

	bool operator<(Node b);

	sf::Color* m_color;
	float m_size = 100; // Percent of original image

	float x;
	float y;
	float z; // Camera axis (parallel to)
};