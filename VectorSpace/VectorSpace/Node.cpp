/*
Object for a node in space
*/
#include "Node.h"

const float MIN_SWAY_OFFSET = 3.f;
const float MAX_SWAY_OFFSET = 1.5f;
const float DEFAULT_SWAY = 15;

Node::Node(float size, float newx, float newy, float newz) : m_size(size)
{
	location = sf::Vector3f(newx, newy, newz);
	m_sway = DEFAULT_SWAY;
	sway_offset.x = MIN_SWAY_OFFSET + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (MAX_SWAY_OFFSET - MIN_SWAY_OFFSET)));
	sway_offset.y = MIN_SWAY_OFFSET + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (MAX_SWAY_OFFSET - MIN_SWAY_OFFSET)));
	sway_offset.z = MIN_SWAY_OFFSET + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (MAX_SWAY_OFFSET - MIN_SWAY_OFFSET)));
}

void Node::Tick(float & delta)
{
	lifetime += delta;

	CalcSway(delta);
}

void Node::CalcSway(float & delta)
{
	location.x += cos(sway_offset.x * lifetime) * m_sway * delta;
	location.y += cos(sway_offset.y * lifetime) * m_sway * delta;
	location.z += cos(sway_offset.z * lifetime) * m_sway * delta;
}

bool CompareNodesByDepth(Node* a, Node* b)
{
	return a->view_location.z < b->view_location.z;
}