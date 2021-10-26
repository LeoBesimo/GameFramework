#pragma once

#include "PhysicsBodies.h"

inline Manifold AABBvsAABB(Manifold m)
{
	AABBStruct abox = m.a.aabb;
	AABBStruct bbox = m.b.aabb;

	vec2 n = bbox.min - abox.min;
	m.collision = false;

	float a_extent = (abox.max.x - abox.min.x) / 2;
	float b_extent = (bbox.max.x - bbox.min.x) / 2;

	float x_overlap = a_extent + b_extent - abs(n.x);

	if (x_overlap > 0)
	{
		// Calculate half extents along x axis for each object
		float a_extent = (abox.max.y - abox.min.y) / 2;
		float b_extent = (bbox.max.y - bbox.min.y) / 2;

			// Calculate overlap on y axis
		float y_overlap = a_extent + b_extent - abs(n.y);

			// SAT test on y axis
			if (y_overlap > 0)
			{
				// Find out which axis is axis of least penetration
				if (x_overlap > y_overlap)
				{
					// Point towards B knowing that n points from A to B
					if (n.x < 0)
						m.normal = vec2(-1, 0);
					else
						m.normal = vec2(0, 0);
					
					m.penetration = x_overlap;
					m.collision = true;
					return m;
					
				}
				else
				{
					// Point toward B knowing that n points from A to B
					if (n.y < 0)
						m.normal = vec2(0, -1);
					else
						m.normal = vec2(0, 1);
					
					m.penetration = y_overlap;
					m.collision = true;
					return m;
				}
			}
	}

	return m;
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