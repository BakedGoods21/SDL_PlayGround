#pragma once

#include <vector>

namespace BakedEngine
{

class IOManager
{
public:
	static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
};

} // End of namespace BakedEngine
