#ifndef Color_hpp
#define Color_hpp

#include <SDL2/SDL.h>

#include <string>
#include <sstream>
#include <iomanip>

class Color
{
public:
	static constexpr Uint32 Black			= 0x00000000;
	static constexpr Uint32 White			= 0xFFFFFF00;
	static constexpr Uint32 Red 			= 0xFF000000;
	static constexpr Uint32 Green 		= 0x00FF0000;
	static constexpr Uint32 Blue 			= 0x0000FF00;
	static constexpr Uint32 Purple		= 0xFF00FF00;
	static constexpr Uint32 Yellow 		= 0xFFFF0000;
	static constexpr Uint32 Orange 		= 0xFFA50000;
	static constexpr Uint32 Cyan 			= 0x00FFFF00;
	static constexpr Uint32 Pink 			= 0xFF00FF00;

	inline static Uint32 Mix (Uint8 r=0, Uint8 g=0, Uint8 b=0)
	{
		return ( (r & 0xFF) << 24 ) + ( (g & 0xFF) << 16 ) + ( (b & 0xFF) << 8) + 0xFF;
	}

	// Converts a color value to an HTML hex string
	inline static std::string str (Uint32 color)
	{
		std::stringstream ss;
		ss << "#";
		ss << std::hex << std::setfill('0') << std::setw(2);
		ss << (color >> 24);
		ss << std::hex << std::setfill('0') << std::setw(2);
		ss << ((color >> 16) & 0x00FF);
		ss << std::hex << std::setfill('0') << std::setw(2);
		ss << ((color >> 8) & 0x0000FF);
		return ss.str();
	}
};

#endif