#pragma once

// C++ Includes
#include <array>

namespace BakedEngine
{

constexpr int DEGREES_OF_PERCISION = 360;
extern std::array<float, DEGREES_OF_PERCISION> bakedSin;
extern std::array<float, DEGREES_OF_PERCISION> bakedCos;
extern std::array<float, DEGREES_OF_PERCISION> bakedTan;

extern void initializeBakedTrig();

} // End of namespace BakedEngine
