#pragma once

#include "PhysicsBodies.h"

inline bool AABBvsAABB(AABBStruct a, AABBStruct b) 
{
	if (a.max.x < b.min.x or a.min.x > b.max.x) return false;
	if (a.max.y < b.min.y or a.min.y > b.max.y) return false;
	return true;
}

inline Manifold CirclevsCircle(Manifold m)
{
	CircleStruct a = m.a.circle;
	CircleStruct b = m.b.circle;

	vec2 n = b.pos - a.pos;

	float r = a.radius + b.radius;
	r *= r;

	if (n.lenSqr() > r) {
		m.collision = false;
		return m;
	}

	float d = n.len();

	if (d != 0)
	{
		m.collision = true;
		m.penetration = r - d;
		m.normal = n / d;
		return m;
	}
	else
	{
		m.collision = true;
		m.penetration = a.radius;
		m.normal = vec2(1, 0);
		return m;
	}
}

void ResolveCollision(Manifold m, PhysicsBody *a, PhysicsBody *b) 
{
	vec2 rv = b->velocity - a->velocity;

	float velAlongNormal = dotProduct(rv, m.normal);

	if (velAlongNormal > 0) return;

	float e = fminf(a->restitution, b->restitution);

	float j = -(1 + e) * velAlongNormal;
	j /= 1 / a->mass + 1 / b->mass;

	vec2 impulse = m.normal * j;

	a->velocity -= impulse * (1 / a->mass);
	b->velocity += impulse * (1 / b->mass);
}