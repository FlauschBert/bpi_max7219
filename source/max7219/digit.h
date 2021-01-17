#pragma once
#include <max7219/binary.h>

#include <unordered_map>
#include <string>

namespace {

using Map = std::unordered_map<char, uint8_t>;
static Map const sMap = {
	// numbers
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

	// operators
	{ '-', B00000001 },

	// literals
	{ 'r', B00000101 },

	// special symbols
	{ 'g', B01100011 }, // ° sign
	{ '>', B00100000 }, // up
	{ '<', B00010000 }, // down
};

}

namespace max7219 {

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

} // max7219

