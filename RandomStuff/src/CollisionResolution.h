#pragma once

#include "PhysicsBodies.h"
#include "Physics.h"
#include "CollisionDetection.h"

namespace lge
{
	void ResolveCollision(Manifold m, PhysicsBody* a, PhysicsBody* b);
	void ResolveCollisionStatic(Manifold m, PhysicsBody* a, PhysicsBody* b);

	void PositionalCorrection(Manifold m, PhysicsBody* a, PhysicsBody* b);

	Manifold Collide(PhysicsBody* a, PhysicsBody* b);
}