#include "Utilities.h"
#include <math.h>

namespace lge
{
	double PythagoreanSolve(double a, double b)
	{
		return sqrt(a * a + b * b);
	}

	float fastInvSqrt(float n)
	{

		const float threehalfs = 1.5F;
		float y = n;

		long i = *(long*)&y;

		i = 0x5f3759df - (i >> 1);
		y = *(float*)&i;

		y = y * (threehalfs - ((n * 0.5F) * y * y));
		y = y * (threehalfs - ((n * 0.5F) * y * y));

		return y;
	}

	int hash(int state)
	{
		state ^= 2747636419u;
		state *= 2654435769u;
		state ^= state >> 16;
		state *= 2654435769u;
		state ^= state >> 16;
		state *= 2654435769u;
		return state;
	}

	double randomDouble(double min, double max)
	{
		return (min)+((double)rand() / RAND_MAX) * (max - min);  // can change random2D().lenSqr() with rand() / RAND_MAX
	}

	vec2 random2D()
	{
		return vec2(randomDouble(-1, 1), randomDouble(-1, 1)).normalize();//vec2(hash(rand()), hash(rand())).normalize();
	}

	vec2 signRandom2D()
	{
		vec2 r = random2D();
		r.x = r.x < 0 ? r.x * -1 : r.x;
		r.y = r.y < 0 ? r.y * -1 : r.y;
		r.normalize();
		return r;
	}

	vec3 random3D()
	{
		return vec3(hash(rand()), hash(rand()), hash(rand())).normalize();
	}

	vec4 random4D()
	{
		return vec4(hash(rand()), hash(rand()), hash(rand()), hash(rand())).normalize();
	}

	double min(double a, double b)
	{
		return a < b ? a : b;
	}

	double max(double a, double b)
	{
		return a > b ? a : b;
	}

	double clamp(double a, double low, double hi)
	{
		return max(low, min(a, hi));
	}

	vec2 minVec2(vec2 a, vec2 b)
	{
		return vec2(min(a.x, b.x), min(a.y, b.y));
	}

	vec2 maxVec2(vec2 a, vec2 b)
	{
		return vec2(max(a.x, b.x), max(a.y, b.y));
	}

	vec2 clampVec2(vec2 a, vec2 min, vec2 max)
	{
		return maxVec2(min, minVec2(a, max));
	}

	vec2 absVec2(vec2 a)
	{
		return vec2(a.x < 0 ? -a.x : a.x, a.y < 0 ? -a.y : a.y);
	}

	double map(double val, double oldMin, double oldMax, double newMin, double newMax)
	{
		return newMin + (newMax - newMin) * ((val - oldMin) / (oldMax - oldMin));
	}

	double constrain(double val, double min, double max)
	{
		return val < min ? min : val > max ? max : val;
	}

	vec2 constrainVec2(vec2 vec, vec2 min, vec2 max)
	{
		vec.x = constrain(vec.x, min.x, max.x);
		vec.y = constrain(vec.y, min.y, max.y);
		return vec;
	}

	double dotVec2(vec2 a, vec2 b)
	{
		return a.x * b.x + a.y * b.y;
	}
}