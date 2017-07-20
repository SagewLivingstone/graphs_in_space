#pragma once

const float ONE_DEG = 0.0174533f;

// For debugging : get working directory
void PrintFullPath(char *);

namespace M
{
	float FClamp(float num, float min, float max);
}