#pragma once
#include "binary.h"

#include <unordered_map>

namespace {

using Map = std::unordered_map<char, uint8_t>;
static Map const sMap = {
	{ '0', B01111110 },
	{ '1', B00110000 },
	{ '2', B01101101 },
	{ '3', B01111001 },
	{ '4', B00110011 },
	{ '5', B01011011 },
	{ '6', B01011111 },
	{ '7', B01110000 },
	{ '8', B01111111 },
	{ '9', B01111011 },
	{ '-', B00000001 },

	{ 'r', B00000101 },
	{ '°', B01100011 },
	{ '`', B00100000 }, // up
	{ '´', B00010000 }, // down
};

}

namespace ledcontrol {

inline uint8_t toDigit (char const c, bool dot = false)
{
	try
	{
		return sMap.at (c) | (dot ? B10000000 : B00000000);
	}
	catch (...)
	{
		return 0;
	}
}

} // ledcontrol

