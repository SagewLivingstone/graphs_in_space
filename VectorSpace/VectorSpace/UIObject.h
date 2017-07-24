#pragma once
#include <SFML/Graphics.hpp>
#include "Node.h"

class UIObject
{
public:
	UIObject(bool zoom_scale=false);
	~UIObject();

	void Update();

	void SetImage(std::string path, bool center_pivot=false);
	void BindToNode(Node* node);

	Node* bound_node;
	sf::Sprite sprite;
	sf::Vector3f location;
	float size = 1;
	bool bDoesZoomScale = false; // Does scale with zoom
	bool bCenterPivot = false; // Should center pivot to image
	bool bVisible = true; // Should render
	bool bBindSize = false;
private:
	sf::Texture texture;
};

