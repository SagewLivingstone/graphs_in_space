/*
Object for a general volume of space, used for containing objects and rendering
*/
#include <string>
#include <iostream>
#include "Space.h"
#include "Helpers.h"

// Factors to calculate depth effect
const float DEPTH_SCALE_FACTOR = 0.34f;
const float DEPTH_OFFSET_FACTOR = 0.1f;

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
		camera_rotation.x -= ONE_DEG;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		camera_rotation.x += ONE_DEG;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		camera_rotation.y += ONE_DEG;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		camera_rotation.y -= ONE_DEG;
	}
}

// Render out nodes in the tree
void Space::Render()
{
	if (m_nodes.empty()) return;

	// Sort nodes by depth before rendering
	std::sort(m_nodes.begin(), m_nodes.end());
	for (auto a : m_nodes)
	{
		//std::cout << a.screen_pos.z << " ";
	}
	std::cout << std::endl;

	// Render all nodes
	for (Node &node : m_nodes)
	{
		drawNode(node);
	}
}

void Space::drawNode(Node& node)
{
	node.view_location = applyCameraRotation(node);

	float scale = depthToScaleFactor(node.view_location.z) * node.m_size / 100;
	float tex_center = t_node_size / 2;

	// ??? : should this just be one global sprite that is drawn many times per frame?
	sf::Sprite tmp_sprite;
	tmp_sprite.setTexture(t_node);
	tmp_sprite.setOrigin(sf::Vector2f(tex_center, tex_center)); // Set origin to center of texture
	tmp_sprite.setScale(sf::Vector2f(scale, scale)); // Scale based on size and distance
	tmp_sprite.setPosition(toScreenSpace(node.view_location)); //Convert pos to screen position
	
	// [] TODO : Set color param

	window->draw(tmp_sprite);
}

sf::Vector2f Space::toScreenSpace(const sf::Vector3f & position)
{
	float depth_offset = ((0.001f * position.z * DEPTH_OFFSET_FACTOR) + 1);
	depth_offset = M::FClamp(depth_offset, 0.f, 100000.f);

	float screen_x = w_center_width + ((position.x / 1000) * w_center_height * depth_offset);
	float screen_y = w_center_height + ((position.y / 1000) * -w_center_height * depth_offset);

	return sf::Vector2f(screen_x, screen_y);
}

float Space::depthToScaleFactor(const float & depth)
{
	return (float) ((0.001 * depth * DEPTH_SCALE_FACTOR) + 1);
}

sf::Vector3f Space::applyCameraRotation(const Node & node)
{
	float x, y, z; // Original xyz coords
	x = node.location.x;
	y = node.location.y;
	z = node.location.z;
	float Rx, Ry, Rz; // Desired rotation
	Rx = camera_rotation.x;
	Ry = camera_rotation.y;
	Rz = camera_rotation.z;
	float Nx, Ny, Nz; // New xyz coords

	Nx = (x * cos(Rx)) + (z * sin(Rx)); // Calc Y axis rotation for desired x rotation
	Ny = y;
	Nz = (-x * sin(Rx)) + (z * cos(Rx));

	// TODO : Maybe handle X rotation later

	return sf::Vector3f(Nx, Ny, Nz);
}
