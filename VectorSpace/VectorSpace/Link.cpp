#include "Link.h"
#include "Helpers.h"

Link::Link(Node * s, Node * e) : a(s), b(e)
{
	UpdateMidpoint();
	thickness = 6;
	max_distance = 1500;
}

void Link::Tick(float & delta)
{
	UpdateMidpoint();

/*
	float actual_distance = GetDistance3(a->location, b->location);
	velocity = (max_distance - actual_distance) / max_distance;
	distance += velocity * 2500 * delta;

	float scale_factor = distance / GetDistance3(a->location, b->location);
	a->location = ScaleDifference(a->location, midpoint, scale_factor);
	b->location = ScaleDifference(b->location, midpoint, scale_factor);*/
}

void Link::UpdateMidpoint()
{
	midpoint = CalcMidpoint(a->location, b->location);
}
