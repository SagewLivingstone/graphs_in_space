/*
Object for a node in space
*/
#include "Node.h"

Node::Node(float size, float newx, float newy, float newz) : m_size(size)
{
	location = sf::Vector3f(newx, newy, newz);
}

bool Node::operator<(Node b)
{
	return view_location.z < b.view_location.z;
}
