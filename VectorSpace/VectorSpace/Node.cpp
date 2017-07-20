/*
Object for a node in space
*/
#include "Node.h"

Node::Node(float size, float newx, float newy, float newz) :
	m_size(size), x(newx), y(newy), z(newz)
{
}

bool Node::operator<(Node b)
{
	return z < b.z;
}
