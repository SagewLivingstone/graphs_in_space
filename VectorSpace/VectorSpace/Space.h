#pragma once
#include "Node.h"

struct WindowData
{
	int Width = 1280;
	int Height = 720;
	std::string Title = "Graphs in Space";
};

class Space
{
public:
	Space();
	~Space();

	void SetWindow(sf::RenderWindow* new_window);

	void Process(); // Tell all nodes to update behaviour and such
	void Render();

private:
	void loadImages();

	void drawNode(Node);
	sf::Vector2f locationToScreenPos(const Node& node); // Convert depth to screen position offset
	float depthToScale(const Node& node); // Convert depth to scale

	sf::RenderWindow* window;
	std::vector<Node> m_nodes;

	sf::Texture t_node;
	float t_node_size;
};