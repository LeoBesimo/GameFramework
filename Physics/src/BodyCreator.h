#pragma once

#include "Components.h"
#include "Utilities.h"
#include "lgeMath.h"
#include "PhysicsBodies.h"

namespace lge
{
	bool CreateCircle(PhysicsBody* body, vec2 pos, double radius, vec2 vel, Material material);
	bool CreateAABB(PhysicsBody* body, vec2 pos, vec2 dim, vec2 vel, Material material);
	bool CreatePolygon(PhysicsBody* body, vec2 pos, float radius, unsigned int numberPoints, vec2 vel, Material material);
}