#include "UIObject.h"



UIObject::UIObject(bool zoom_scale) : bDoesZoomScale(zoom_scale)
{
}


UIObject::~UIObject()
{
}

void UIObject::Update()
{
}

void UIObject::SetImage(std::string path, bool center_pivot)
{
	texture.loadFromFile(path);
	texture.setSmooth(true);

	sprite.setTexture(texture);

	if (center_pivot) // Center pivot to texture
	{
		sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	}
}

void UIObject::BindToNode(Node * node)
{
	bound_node = node;
}
