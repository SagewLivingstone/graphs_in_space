#pragma once
#include "Node.h"
#include "Link.h"

struct WindowData
{
	int Width = 2560;
	int Height = 1440;
	std::string Title = "Change resolution please";
};

class Space
{
public:
	Space();
	~Space();

	void SetWindow(sf::RenderWindow* new_window);

	void Process(); // Tell all nodes to update behaviour and such
	void HandleInput();
	void Render();

private:
	void loadImages(); // Load images on init

	void drawNode(Node&); // Draw an individual node
	float depthToScaleFactor(const float& depth); // Convert depth to scale
	sf::Vector3f applyCameraRotation(const Node& node); // Apply world camera rotation to location
	sf::Vector2f toScreenSpace(const sf::Vector3f& node); // Convert depth and position to screen position offset

	void drawLink(Link&);

	sf::RenderWindow* window;
	std::vector<Node*> m_nodes;
	std::vector<Link*> m_links;
	sf::Vector3f camera_rotation = sf::Vector3f(0,0,0);

	sf::Texture t_node;
	float t_node_size;

	float w_height;
	float w_width;
	float w_center_height;
	float w_center_width;
};