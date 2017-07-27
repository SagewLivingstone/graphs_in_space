#pragma once
#include "SFML\Graphics.hpp"

const float DEFAULT_NODE_SIZE = 7;

class Node
{
public:
	Node(float size=DEFAULT_NODE_SIZE, float newx=0, float newy=0, float newz=0);

	void Tick(float & delta);

	void OrbitParent(float & delta);
	void CalcSway(float & delta);

	bool IsRoot(); // Is this node the root of a system?

	void AddChild(Node* child);
	void RemoveChild(Node* child);

	float lifetime = 0;
	bool bIsDead = false;

	// Graph props

	// Tree Props
	Node* parent;
	std::vector<Node*> children;
	float orbit_speed = 5;
	float orbit_distance = 200;

	sf::Color* m_color;
	sf::Color* m_child_color;
	float m_sway;
	sf::Vector3f sway_offset;
	float m_size = 100; // Percent of original image size

	sf::Vector3f location; // Physical world location
	sf::Vector3f view_location; // Position after rotated by camera
};

bool CompareNodesByDepth(Node * a, Node * b);