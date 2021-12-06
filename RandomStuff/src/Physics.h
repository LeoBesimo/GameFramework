#pragma once

#include "components.h"
#include "PhysicsBodies.h"

namespace lge
{
	const double GRAVITY = 20.0;

	inline vec2 getPosition(PhysicsBody* body);
	inline void setPosition(PhysicsBody* body, vec2 position);
	inline void applyGravity(PhysicsBody* body, double deltaTime, double timeSteps);
	inline bool updatePhysicsBody(PhysicsBody* body, double deltaTime, double timeSteps);
	inline void constrainPhysicsBody(PhysicsBody* body, vec2 min, vec2 max);
	inline void bounceInArea(PhysicsBody* body, vec2 min, vec2 max);
}