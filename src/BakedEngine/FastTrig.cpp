// C++ Includes
#include <cmath>

// BakedEngine Libraries
#include "BakedEngine/FastTrig.h"

namespace BakedEngine
{

std::array<float, DEGREES_OF_PERCISION> bakedSin;
std::array<float, DEGREES_OF_PERCISION> bakedCos;
std::array<float, DEGREES_OF_PERCISION> bakedTan;

void initializeBakedTrig()
{
	for (int i = 0; i < DEGREES_OF_PERCISION; i++)
	{
		bakedCos[i] = (float)std::cos((double)i);
		bakedSin[i] = (float)std::sin((double)i);
		bakedTan[i] = (float)std::tan((double)i);
	}
}

} // End of namespace BakedEngine
