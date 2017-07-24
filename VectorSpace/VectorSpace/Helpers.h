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
sf::Vector3f RotateAroundOrigin(const sf::Vector3f& point, const sf::Vector3f& rotation);
sf::Vector3f RotateAroundPoint(const sf::Vector3f& point, const sf::Vector3f& rotation, const sf::Vector3f& origin);
sf::Vector3f ScaleDifference(const sf::Vector3f& point, const sf::Vector3f& origin, float scale);
float GetRandom(float low, float high);
float GetDistance(sf::Vector2f a, sf::Vector2f b);
float GetDistance3(sf::Vector3f a, sf::Vector3f b);
float GetAngle(sf::Vector2f a, sf::Vector2f b);
