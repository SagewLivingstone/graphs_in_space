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

sf::Vector3f RotateAroundOrigin(const sf::Vector3f & point, const sf::Vector3f & rotation)
{
	float x, y, z; // Original xyz coords
	x = point.x;
	y = point.y;
	z = point.z;
	float Rx, Ry, Rz; // Desired rotation
	Rx = rotation.x;
	Ry = rotation.y;
	Rz = rotation.z;
	float Nx, Ny, Nz; // New xyz coords from Y axis rotation
	float Mx, My, Mz; // New xyz coords from X axis rotation

	Nx = (x * cos(Rx)) + (z * sin(Rx)); // Calc Y axis rotation for desired x rotation
	Ny = y;
	Nz = (-x * sin(Rx)) + (z * cos(Rx));

	Mx = Nx;                            // Calc X axis rotation for desired y rotation
	My = (Ny * cos(Ry)) - (Nz * sin(Ry));
	Mz = (Ny * sin(Ry)) + (Nz * cos(Ry));

	return sf::Vector3f(Mx, My, Mz);
}

sf::Vector3f RotateAroundPoint(const sf::Vector3f & point, const sf::Vector3f & rotation, const sf::Vector3f & origin)
{
	sf::Vector3f normalized = point - origin;
	normalized = RotateAroundOrigin(normalized, rotation);
	normalized = normalized + origin;
	return normalized;
}

sf::Vector3f ScaleDifference(const sf::Vector3f & point, const sf::Vector3f & origin, float scale)
{
	sf::Vector3f normalized = point - origin;
	normalized = sf::Vector3f(normalized.x * scale, normalized.y * scale, normalized.z * scale);
	normalized = normalized + origin;
	return normalized;
}

float GetRandom(float low, float high)
{
	return low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(high - low)));
}

float GetDistance(sf::Vector2f a, sf::Vector2f b)
{
	return abs(sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)));
}

float GetDistance3(sf::Vector3f a, sf::Vector3f b)
{
	return abs(sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z)));
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