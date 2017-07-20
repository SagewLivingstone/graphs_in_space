#include "Helpers.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void PrintFullPath(char * partialPath)
{
	char full[_MAX_PATH];
	if (_fullpath(full, partialPath, _MAX_PATH) != NULL)
		printf("Working path is: %s\n", full);
	else
		printf("Invalid path\n");
}

float M::FClamp(float num, float min, float max)
{
	return fmax(fmin(num, max), min);
}