#pragma once
#include "Node.h"
#include "Link.h"
#include "UI.h"

struct WindowData
{
	int Width = 1366;
	int Height = 768;
	std::string Title = "Change resolution please";
};

class Space
{
public:
	Space();
	~Space();

	// External
	void SetWindow(sf::RenderWindow* new_window);
	void Zoom(int amount);

	// Getters
	Node* GetNodeByScreenPos(int x, int y);

	// Events
	void EventTick();
	void EventLMB(); // Select
	void EventRMB(); // Drag
	void EventMouseMoved(float x, float y);
	void EventCollision(Node* a, Node* b);

private:
	// Initializing
	void initTime();
	void loadImages();

	// Processing
	void Render();
	void UpdateTime();
	void ProcessItems(); // Tell all nodes to update behaviour and such
	void HandleInput();
	void CheckCollision();
	void UpdateFrameTimer();

	// Time
	sf::Clock runtimeClock;
	sf::Clock deltaClock;
	float runtime;
	float deltatime;

	// UI
	UI* ui;
	void DrawUIObject(UIObject* obj);

	// Rendering
	void drawNode(Node&); // Draw an individual node
	void drawLink(Link&);
	float depthToScaleFactor(const float& depth); // Convert depth to scale
	sf::Vector3f applyCameraRotation(const Node& node); // Apply world camera rotation to location
	sf::Vector2f toScreenSpace(const sf::Vector3f& node); // Convert depth and position to screen position offset

	// Camera
	sf::Vector3f camera_rotation;
	float zoom_factor = 1000;

	// Objects
	std::vector<Node*> m_nodes;
	std::vector<Link*> m_links;

	// Modifiers
	void GenerateNode(Node* instigator); // Actually calculate a new node with parameters
	void AddNode(Node* node);
	void AddChild(Node* parent, Node* child);
	void SplitNode(Node* original, float force);
	void BreakOff(Node* parent);
	void AddLink(Link* link);
	void RemoveNode(Node* node);

	// Frame counter
	double lastTime = runtime;
	int deltaFrames = 0;

	// Node image
	sf::Sprite s_node; // TODO
	sf::Texture t_node;
	float t_node_size;

	// Window
	sf::RenderWindow* window;
	float w_height;
	float w_width;
	float w_center_height;
	float w_center_width;
};