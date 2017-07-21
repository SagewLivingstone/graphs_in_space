/*
Object for a node in space
*/
#include "Node.h"

Node::Node(float size, float newx, float newy, float newz) : m_size(size)
{
	location = sf::Vector3f(newx, newy, newz);
}

bool CompareNodes(Node* a, Node* b)
{
	return a->view_location.z < b->view_location.z;
}