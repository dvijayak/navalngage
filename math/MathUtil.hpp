#ifndef MathUtil_hpp
#define MathUtil_hpp

#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class MathUtil
{
public:

	static constexpr float RADS_PER_DEG = M_PI/180.0;
	static constexpr float DEGS_PER_RAD = 180.0/M_PI;

	static float DegreesToRadians (float angle);
	static float RadiansToDegrees (float angle);
};

inline float MathUtil::DegreesToRadians (float angle)
{
	return angle * RADS_PER_DEG;
}

inline float MathUtil::RadiansToDegrees (float angle)
{
	return angle * DEGS_PER_RAD;
}

#endif