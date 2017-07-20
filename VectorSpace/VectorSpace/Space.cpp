/*
Object for a general volume of space, used for containing objects and rendering
*/
#include <string>
#include <iostream>
#include "Space.h"
#include "Helpers.h"

Space::Space()
{
	loadImages();

	// For debugging purposes : test node
	Node testnode = Node(12, 0, 0);
	m_nodes.push_back(testnode);

	// Debug : square of nodes
	Node a = Node(8, 400, 400, 400);
	Node b = Node(8, -400, 400, 400);
	Node c = Node(8, 400, 400, -400);
	Node d = Node(8, -400, 400, -400);
	Node e = Node(8, 400, -400, 400);
	Node f = Node(8, -400, -400, 400);
	Node g = Node(8, 400, -400, -400);
	Node h = Node(8, -400, -400, -400);
	m_nodes.push_back(a);
	m_nodes.push_back(b);
	m_nodes.push_back(c);
	m_nodes.push_back(d);
	m_nodes.push_back(e);
	m_nodes.push_back(f);
	m_nodes.push_back(g);
	m_nodes.push_back(h);
}

Space::~Space()
{
}

void Space::SetWindow(sf::RenderWindow* new_window)
{
	window = new_window;

	// Set window specifications
	sf::Vector2u window_size = window->getSize();
	w_height = (float)window_size.y;
	w_width = (float)window_size.x;
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
		camera_rotation.x -= .017;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		camera_rotation.x += .017;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		camera_rotation.y += .017;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		camera_rotation.y -= .017;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp))
	{
		std::cout << "Node Depth (z): " << m_nodes[0].z << std::endl;
		m_nodes[0].z += speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown))
	{
		std::cout << "Node Depth (z): " << m_nodes[0].z << std::endl;
		m_nodes[0].z -= speed;
	}
}

// Render out nodes in the tree
void Space::Render()
{
	if (m_nodes.empty()) return;

	// Sort nodes by depth before rendering
	std::sort(m_nodes.begin(), m_nodes.end());

	// Render all nodes
	for (const Node &node : m_nodes)
	{
		drawNode(node);
	}
}

void Space::drawNode(Node node)
{
	sf::Vector3f position = applyCameraRotation(node);

	float scale = depthToScaleFactor(position.z) * node.m_size / 100;
	float tex_center = t_node_size / 2;

	// ??? : should this just be one global sprite that is drawn many times per frame?
	sf::Sprite tmp_sprite;
	tmp_sprite.setTexture(t_node);
	// Center origin to texture
	tmp_sprite.setOrigin(sf::Vector2f(tex_center, tex_center));
	// Scale based on size and distance
	tmp_sprite.setScale(sf::Vector2f(scale, scale));

	// WIP : Convert coords to world pos
	tmp_sprite.setPosition(toScreenSpace(position));
	
	// [] TODO : Set color

	window->draw(tmp_sprite);
}

sf::Vector2f Space::toScreenSpace(const sf::Vector3f & position)
{
	float depth_offset = ((0.001f * position.z * 0.3f) + 1);
	depth_offset = M::FClamp(depth_offset, 0.f, 100000.f);
	//depth_offset = 1; // Disable unless testing

	float screen_x = w_center_width + ((position.x / 1000) * w_center_height * depth_offset);
	float screen_y = w_center_height + ((position.y / 1000) * -w_center_height * depth_offset);

	return sf::Vector2f(screen_x, screen_y);
}

float Space::depthToScaleFactor(const float & depth)
{
	return (float) ((0.001 * depth * .4f) + 1);
}

sf::Vector3f Space::applyCameraRotation(const Node & node)
{
	float x, y, z;
	x = node.x;
	y = node.y;
	z = node.z;
	float Rx, Ry, Rz;
	Rx = camera_rotation.x;
	Ry = camera_rotation.y;
	Rz = camera_rotation.z;
	float Nx, Ny, Nz; // New coords

	// Y axis rotation for x rot
	Nx = (x * cos(Rx)) + (z * sin(Rx));
	Ny = y;
	Nz = (-x * sin(Rx)) + (z * cos(Rx));

	// Maybe handle X rotation later

	return sf::Vector3f(Nx, Ny, Nz);
}
