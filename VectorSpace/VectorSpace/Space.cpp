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
	Node testnode = Node(12, 100, 100);
	m_nodes.push_back(testnode);
}

Space::~Space()
{
}

void Space::SetWindow(sf::RenderWindow* new_window)
{
	window = new_window;

	// Set window specifications
	sf::Vector2u window_size = window->getSize();
	w_height = window_size.y;
	w_width = window_size.x;
	w_center_height = w_height / 2;
	w_center_width = w_width / 2;
}

void Space::loadImages()
{
	// Load image for node object
	if (!t_node.loadFromFile("images\\object_ball.png"))
		printf("Could not load node texture!");
	t_node.setSmooth(true);

	t_node_size = (float)t_node.getSize().x;
}

void Space::HandleInput()
{
	float speed = 4;
	// Debugging - movement controls
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_nodes[0].x += speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_nodes[0].x -= speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_nodes[0].y += speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_nodes[0].y -= speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_nodes[0].z += speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_nodes[0].z -= speed;
	}
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

void Space::drawNode(Node node)
{
	float scale = node.m_size / 100;
	float center = t_node_size / 2;

	sf::Sprite tmp_sprite;
	tmp_sprite.setOrigin(sf::Vector2f(center, center));
	tmp_sprite.setTexture(t_node);
	tmp_sprite.setScale(sf::Vector2f(scale, scale));

	// TODO : Convert coords to world pos
	tmp_sprite.setPosition(toScreenSpace(node));
	
	// TODO : Set color

	window->draw(tmp_sprite);
}

sf::Vector2f Space::toScreenSpace(const Node & node)
{
	float x, y, z;
	x = node.x;
	y = node.y;
	z = node.z;

	float depth_offset = (z / 1000) * .5;
	float screen_x = w_center_width + (x / 1000) * w_center_width;
	float screen_y = w_center_height + (y / 1000) * -w_center_height;

	return sf::Vector2f(screen_x, screen_y);
}
