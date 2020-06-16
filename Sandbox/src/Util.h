#pragma once

#include <random>

static float RandomFloat(float maximo = 1)
{
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX / maximo);
}