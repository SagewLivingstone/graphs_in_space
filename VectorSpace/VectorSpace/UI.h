#pragma once
#include "Node.h"
#include "UIObject.h"

class UI
{
public:
	UI();
	~UI();

	// Init
	void SetWindow(sf::RenderWindow* new_window);

	// Objects
	void AddObject(UIObject* new_object);
	
	// Highlight
	void SetHighlight(Node* node);
	Node* GetHighlight();

	std::vector<UIObject*> objects;

private:
	sf::RenderWindow* window;

	// Objects
	UIObject* highlight;

	// Window Values
	float w_height;
	float w_width;
	float w_center_height;
	float w_center_width;
};

