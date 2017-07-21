#pragma once

#include <SFML/Graphics.hpp>

const float ONE_DEG = 0.0174533f;

// For debugging : get working directory
void PrintFullPath(char *);

namespace M
{
	float FClamp(float num, float min, float max);
}

sf::Vector3f CalcMidpoint(sf::Vector3f& a, sf::Vector3f& b);
float GetDistance(sf::Vector2f a, sf::Vector2f b);
float GetAngle(sf::Vector2f a, sf::Vector2f b);