#include "UI.h"

const std::string HIGHLIGHT_IMAGE = "images\\node_highlight.png";

UI::UI()
{
	highlight = new UIObject(true); // Object for node highlight
	highlight->SetImage(HIGHLIGHT_IMAGE, true);
	highlight->bDoesZoomScale = true;
	highlight->bBindSize = true;
	AddObject(highlight);

	printf("UI: initialized\n");
}


UI::~UI()
{
	for (auto* a : objects) delete a;
}

void UI::SetWindow(sf::RenderWindow* new_window)
{
	window = new_window;

	// Set window specifications
	sf::Vector2u window_size = window->getSize();
	w_height = (float)window_size.y;
	w_width = (float)window_size.x;
	w_center_height = w_height / 2;
	w_center_width = w_width / 2;
}

void UI::AddObject(UIObject * new_object)
{
	if (!new_object) return;

	objects.push_back(new_object);
}

void UI::SetHighlight(Node * node)
{
	highlight->BindToNode(node);
	highlight->bVisible = node; // Only set visible if we have a node to highlight
}

Node * UI::GetHighlight()
{
	return highlight->bound_node;
}
