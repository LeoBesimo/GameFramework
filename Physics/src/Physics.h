#pragma once

#include "components.h"
#include "PhysicsBodies.h"

namespace lge
{
	const double GRAVITY = 20.0;

	vec2 getPosition(PhysicsBody* body);
	void setPosition(PhysicsBody* body, vec2 position);
	void applyGravity(PhysicsBody* body, double deltaTime, double timeSteps);
	bool updatePhysicsBody(PhysicsBody* body, double deltaTime, double timeSteps);
	void constrainPhysicsBody(PhysicsBody* body, vec2 min, vec2 max);
	void bounceInArea(PhysicsBody* body, vec2 min, vec2 max);
}