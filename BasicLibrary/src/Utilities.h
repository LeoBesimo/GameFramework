#pragma once
#include "Components.h"

namespace lge
{
	double PythagoreanSolve(double a, double b);
	float fastInvSqrt(float n);
	int hash(int state);
	double randomDouble(double min, double man);
	vec2 random2D();
	vec2 signRandom2D();
	vec3 random3D();
	vec4 random4D();
	double min(double a, double b);
	double max(double a, double b);
	double clamp(double a, double low, double hi);
	vec2 minVec2(vec2 a, vec2 b);
	vec2 maxVec2(vec2 a, vec2 b);
	vec2 clampVec2(vec2 a, vec2 min, vec2 max);
	vec2 absVec2(vec2 a);
	double map(double val, double oldMin, double oldMax, double newMin, double newMax);
	double constrain(double val, double min, double max);
	vec2 constrainVec2(vec2 a, vec2 min, vec2 max);
	double dotVec2(vec2 a, vec2 b);
}

