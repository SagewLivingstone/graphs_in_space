/*
Object for a general volume of space, used for containing objects and rendering
*/
#include <string>
#include <iostream>
#include "Space.h"
#include "Helpers.h"

// Factors to calculate depth effect
const float DEPTH_SCALE_FACTOR = 0.34f;
const float DEPTH_OFFSET_FACTOR = 0.3f;

const float CAMERA_TURN_SPEED = 1.5f;

const bool SHOW_FRAME_COUNTER = true;

const std::string NODE_IMAGE = "images\\node_item.png";

Space::Space()
{
	initTime();
	loadImages();

	// For debugging purposes : test node
	Node* testnode = new Node(12, 0, 0);
	testnode->m_color = new sf::Color(255, 0, 0);
	m_nodes.push_back(testnode);

	// Debug : square of nodes
	Node* a = new Node(8, 400, 400, 400);
	a->m_color = new sf::Color(0, 0, 255);
	Node* b = new Node(8, -400, 400, 400);
	Node* c = new Node(8, 400, 400, -400);
	c->m_color = new sf::Color(0, 255, 0);
	Node* d = new Node(8, -400, 400, -400);
	Node* e = new Node(8, 400, -400, 400);
	e->m_color = new sf::Color(255, 150, 0);
	Node* f = new Node(8, -400, -400, 400);
	Node* g = new Node(8, 400, -400, -400);
	g->m_color = new sf::Color(255, 0, 255);
	Node* h = new Node(8, -400, -400, -400);
	m_nodes.push_back(a);
	m_nodes.push_back(b);
	m_nodes.push_back(c);
	m_nodes.push_back(d);
	m_nodes.push_back(e);
	m_nodes.push_back(f);
	m_nodes.push_back(g);
	m_nodes.push_back(h);
	// Debug : test links
	Link* testlink = new Link(testnode, e);
	Link* la = new Link(a, g);
	Link* lb = new Link(b, d);
	Link* lc = new Link(c, b);
	Link* ld = new Link(f, e);
	Link* le = new Link(h, b);
	Link* lf = new Link(f, a);
	m_links.push_back(testlink);
	m_links.push_back(la);
	m_links.push_back(lb);
	m_links.push_back(lc);
	m_links.push_back(ld);
	m_links.push_back(le);
	m_links.push_back(lf);
}

Space::~Space()
{
}

void Space::Tick() // Main tick function of space : called every update
{
	UpdateTime();
	Render();
	HandleInput();
	ProcessItems();
	if (SHOW_FRAME_COUNTER) UpdateFrameTimer();
}

void Space::initTime()
{
	runtimeClock.restart();
	deltaClock.restart();
	printf("Space: Time initialized\n");
}

void Space::loadImages()
{
	// Load image for node object
	if (!t_node.loadFromFile(NODE_IMAGE))
		printf("Could not load node texture!");
	t_node.setSmooth(true);

	t_node_size = (float)t_node.getSize().x;
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

void Space::UpdateTime()
{
	runtime = runtimeClock.getElapsedTime().asMilliseconds() / 1000.f;
	deltatime = deltaClock.getElapsedTime().asMilliseconds() / 1000.f;
	deltaClock.restart();
}

void Space::ProcessItems()
{
	for (Node* node : m_nodes)
	{
		node->Tick(deltatime);
	}
}

void Space::HandleInput()
{
	float speed = 4;
	// Debugging - movement controls
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		camera_rotation.x += CAMERA_TURN_SPEED * deltatime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		camera_rotation.x -= CAMERA_TURN_SPEED * deltatime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		camera_rotation.y += CAMERA_TURN_SPEED * deltatime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		camera_rotation.y -= CAMERA_TURN_SPEED * deltatime;
	}
}

// Render out nodes in the tree
void Space::Render()
{
	if (m_nodes.empty()) return;

	std::sort(m_nodes.begin(), m_nodes.end(), CompareNodes); // Sort nodes by depth before rendering

	for (Node* node : m_nodes) // Render all nodes
	{
		drawNode(*node);
	}
	for (Link* link : m_links) // Render all links
	{
		drawLink(*link);
	}
}

void Space::UpdateFrameTimer()
{
	double currentTime = runtime;
	deltaFrames++;
	if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
		float secondsPerFrame = 1000.0 / double(deltaFrames);
		int framerate = (1 / secondsPerFrame) * 1000;
		printf("%f ms/frame (%d FPS)\n", secondsPerFrame, framerate);
		deltaFrames = 0;
		lastTime += 1.0;
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
	sf::Vector2f screen_position = toScreenSpace(node.view_location);
	node.view_location = sf::Vector3f(screen_position.x, screen_position.y, node.view_location.z);
	tmp_sprite.setPosition(screen_position); //Convert pos to screen position

	if (node.m_color) tmp_sprite.setColor(*node.m_color);

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

void Space::drawLink(Link & link)
{
	if (!link.a || !link.b) return; // Don't draw if link is broken. TODO [handle broken link]

	sf::Vector3f pos_a = link.a->view_location;
	sf::Vector3f pos_b = link.b->view_location;
	sf::Vector3f midpt = CalcMidpoint(pos_a, pos_b);

	float distance = GetDistance(sf::Vector2f(pos_a.x, pos_a.y), sf::Vector2f(pos_b.x, pos_b.y)) - 50;
	float angle = GetAngle(sf::Vector2f(pos_a.x, pos_a.y), sf::Vector2f(pos_b.x, pos_b.y));

	sf::RectangleShape line(sf::Vector2f(link.thickness, distance));
	line.setOrigin(sf::Vector2f(link.thickness / 2, distance / 2));
	line.setFillColor(sf::Color(255, 255, 255, 100));
	line.setRotation(angle);

	line.setPosition(sf::Vector2f(midpt.x, midpt.y));

	window->draw(line);
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
	float Nx, Ny, Nz; // New xyz coords from Y axis rotation
	float Mx, My, Mz; // New xyz coords from X axis rotation

	Nx = (x * cos(Rx)) + (z * sin(Rx)); // Calc Y axis rotation for desired x rotation
	Ny = y;
	Nz = (-x * sin(Rx)) + (z * cos(Rx));

	Mx = Nx;                            // Calc X axis rotation for desired y rotation
	My = (Ny * cos(Ry)) - (Nz * sin(Ry));
	Mz = (Ny * sin(Ry)) + (Nz * cos(Ry));

	return sf::Vector3f(Mx, My, Mz);
}
