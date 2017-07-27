/*
Object for a node in space
*/
#include "Node.h"
#include "Helpers.h"

const float MIN_SWAY_OFFSET = 3.f;
const float MAX_SWAY_OFFSET = 1.5f;
const float DEFAULT_SWAY = 15;

Node::Node(float size, float newx, float newy, float newz) : m_size(size)
{
	location = sf::Vector3f(newx, newy, newz);
	m_sway = DEFAULT_SWAY;
	m_child_color = new sf::Color(GetRandom(0, 255), GetRandom(0, 255), GetRandom(0, 255));
	sway_offset.x = MIN_SWAY_OFFSET + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (MAX_SWAY_OFFSET - MIN_SWAY_OFFSET)));
	sway_offset.y = MIN_SWAY_OFFSET + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (MAX_SWAY_OFFSET - MIN_SWAY_OFFSET)));
	sway_offset.z = MIN_SWAY_OFFSET + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (MAX_SWAY_OFFSET - MIN_SWAY_OFFSET)));
}

void Node::Tick(float & delta)
{
	lifetime += delta;

	if (!IsRoot()) OrbitParent(delta);

	CalcSway(delta);
}

void Node::OrbitParent(float & delta) // Must have a parent!!!
{
	location = RotateAroundPoint(location, sf::Vector3f(orbit_speed * delta, 0, 0), parent->location);
	if (GetDistance3(location, parent->location) < orbit_distance)
		location = ScaleDifference(location, parent->location, 1.01);
}

void Node::CalcSway(float & delta)
{
	location.x += cos(sway_offset.x * lifetime) * m_sway * delta;
	location.y += cos(sway_offset.y * lifetime) * m_sway * delta;
	location.z += cos(sway_offset.z * lifetime) * m_sway * delta;
}

bool Node::IsRoot()
{
	return !parent;
}

void Node::AddChild(Node * child)
{
	child->parent = this;
	children.push_back(child);
}

void Node::RemoveChild(Node * child)
{
	child->parent = NULL;
	children.erase(std::remove(children.begin(), children.end(), child), children.end());
}

bool CompareNodesByDepth(Node* a, Node* b)
{
	return a->view_location.z < b->view_location.z;
}