#include "Helpers.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <chrono>

void PrintFullPath(char * partialPath)
{
	char full[_MAX_PATH];
	if (_fullpath(full, partialPath, _MAX_PATH) != NULL)
		printf("Working path is: %s\n", full);
	else
		printf("Invalid path\n");
}

sf::Vector3f CalcMidpoint(sf::Vector3f & a, sf::Vector3f & b)
{
	sf::Vector3f end;
	end.x = (a.x + b.x) / 2;
	end.y = (a.y + b.y) / 2;
	end.z = (a.z + b.z) / 2;
	//std::cout << "Y: " << a.y << std::endl;
	return end;
}

float GetDistance(sf::Vector2f a, sf::Vector2f b)
{
	return abs(sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)));
}

float GetAngle(sf::Vector2f a, sf::Vector2f b)
{
	float width = a.x - b.x;
	float height = b.y - a.y;

	float angle = atan(width / height);

	return angle * (180.0f / 3.14159f);
}

float M::FClamp(float num, float min, float max)
{
	return fmax(fmin(num, max), min);
}