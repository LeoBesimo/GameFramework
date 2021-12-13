#pragma once

#include "Components.h"
#include "Utilities.h"
#include "PhysicsBodies.h"

namespace lge
{
	const double GRAVITY = 60.0;

	vec2 getPosition(PhysicsBody* body);
	void setPosition(PhysicsBody* body, vec2 position);
	vec2 forceForDesiredVelocity(const PhysicsBody &body, vec2 desiredVelocity, double deltaTime, double timeSteps);
	void applyForce(PhysicsBody* body, vec2 force);
	void applyGravity(PhysicsBody* body, double deltaTime, double timeSteps);
	bool updatePhysicsBody(PhysicsBody* body, double deltaTime, double timeSteps);
	void constrainPhysicsBody(PhysicsBody* body, vec2 min, vec2 max);
	void bounceInArea(PhysicsBody* body, vec2 min, vec2 max);
}