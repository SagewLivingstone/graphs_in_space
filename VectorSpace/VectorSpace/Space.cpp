/*
Object for a general volume of space, used for containing objects and rendering
*/
#include <string>
#include <iostream>
#include "Space.h"

Space::Space()
{
	loadImages();

	// For debugging purposes : test node
	Node testnode = Node();
	m_nodes.push_back(testnode);
}

Space::~Space()
{
}

// Render out nodes in the tree
void Space::Render()
{
	if (m_nodes.empty()) return;

	// Sort nodes by depth before rendering
	std::sort(m_nodes.begin(), m_nodes.end());

	for (const Node &node : m_nodes)
	{
		drawNode(node);
	}
}

void Space::SetWindow(sf::RenderWindow* new_window)
{
	window = new_window;
}

void Space::loadImages()
{
	// Load image for node object
	if (!t_node.loadFromFile("images\\object_ball.png"))
		printf("Could not load node texture!");
	t_node.setSmooth(true);

	t_node_size = (float)t_node.getSize().x;
}

void Space::drawNode(Node node)
{
	float scale = node.m_size / 100;
	float center = t_node_size / 2;

	sf::Sprite tmp_sprite;
	tmp_sprite.setOrigin(sf::Vector2f(center, center));
	tmp_sprite.setTexture(t_node);
	tmp_sprite.setScale(sf::Vector2f(scale, scale));

	// TODO : Convert coords to world pos
	tmp_sprite.setPosition(sf::Vector2f(640, 360));
	
	// TODO : Set color

	window->draw(tmp_sprite);
}
