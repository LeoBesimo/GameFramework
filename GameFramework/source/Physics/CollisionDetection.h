#pragma once

#include "PhysicsBodies.h"

inline Manifold CirclevsAABB(Manifold m)
{
	m.collision = false;

	CircleStruct a = m.a.circle;
	AABBStruct b = m.b.aabb;

	vec2 L = clampVec2(a.pos, b.min, b.max);
	vec2 ab = L - a.pos;
	float d2 = dotVec2(ab,ab);
	float r2 = a.radius * a.radius;
	if (d2 < r2)
	{
		if (d2 != 0)
		{
			float d = sqrtf(d2);
			vec2 n = ab.normalize();
			m.collision = true;
			m.penetration = a.radius - d;
			m.normal = n;
		}

		else
		{
			vec2 mid = (b.min + b.max) * 0.5;
			vec2 e = (b.max - b.min) * 0.5;
			vec2 d = a.pos - mid;
			vec2 abs_d = absVec2(d);

			float x_overlap = e.x - abs_d.x;
			float y_overlap = e.y - abs_d.y;

			float depth;
			vec2 n;

			if (x_overlap < y_overlap)
			{
				depth = x_overlap;
				n = vec2(1.0, 0);
				n = n * (d.x < 0 ? 1.0 : -1.0);
			}
			else
			{
				depth = y_overlap;
				n = vec2(0, 1.0);
				n = n * (d.y < 0 ? 1.0 : -1.0);
			}

			m.collision = true;
			m.penetration = a.radius + depth;
			m.normal = n;
		}
	}

	return m;
}

inline Manifold AABBvsAABB(Manifold m)
{
	AABBStruct abox = m.a.aabb;
	AABBStruct bbox = m.b.aabb;

	vec2 n = bbox.min - abox.min;
	m.collision = false;

	vec2 mid_a = (abox.min + abox.max) * 0.5;
	vec2 mid_b = (bbox.min + bbox.max) * 0.5;

	vec2 eA = absVec2((abox.max - abox.min) * 0.5);
	vec2 eB = absVec2((bbox.max - bbox.min) * 0.5);

	vec2 d = mid_b - mid_a;

	float dx = eA.x + eB.x - abs(d.x);
	if (dx < 0) return m;
	float dy = eA.y + eB.y - abs(d.y);
	if (dy < 0) return m;

	m.collision = true;

	if (dx < dy)
	{
		m.penetration = dx;
		if (d.x < 0)
			m.normal = vec2(-1.0, 0);
		else
			m.normal = vec2(1.0, 0);
	}
	else
	{
		m.penetration = dy;
		if (d.y < 0)
			m.normal = vec2(0, -1.0);
		else
			m.normal = vec2(0, 1.0);
	}

	return m;

	/*float a_extent = (abox.max.x - abox.min.x) / 2;
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
						m.normal = vec2(1, 0);
					
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
	}*/

	//return m;
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

	float velAlongNormal = dotVec2(rv, m.normal);

	if (velAlongNormal > 0) return;

	float e = fminf(a->restitution, b->restitution);

	float j = -(1 + e) * velAlongNormal;
	j /= 1 / a->mass + 1 / b->mass;

	vec2 impulse = m.normal * j;

	a->velocity -= impulse * (1 / a->mass);
	b->velocity += impulse * (1 / b->mass);
}

void positionalCorrection(Manifold m,PhysicsBody* a, PhysicsBody* b)
{
	const float precent = 0.2;
	const float slop = 0.01;
	vec2 correction = max(m.penetration - slop, 0.0f) / (1 / a->mass + 1 / b->mass);
}

inline Manifold collide(PhysicsBody* a, PhysicsBody* b)
{
	switch (a->type)
	{
	case BodyType::AABB:
		switch (b->type)
		{
		case BodyType::AABB:
		{
			Manifold m;
			m.a = *a;
			m.b = *b;
			m = AABBvsAABB(m);
			return m;
		}
		case BodyType::Circle:
		{
			Manifold m;
			m.a = *b;
			m.b = *a;
			m = CirclevsAABB(m);
			return m;
		}
		case BodyType::Polygon:
			break;
		case BodyType::Null:
			break;
		}
		break;

	case BodyType::Circle:
		switch (b->type)
		{
		case BodyType::AABB:
		{
			Manifold m;
			m.a = *a;
			m.b = *b;
			m = CirclevsAABB(m);
			return m;
		}
		case BodyType::Circle:
		{
			Manifold m;
			m.a = *a;
			m.b = *b;
			m = CirclevsCircle(m);
			return m;
		}
		case BodyType::Polygon:
			break;
		case BodyType::Null:
			break;
		}
		break;

	case BodyType::Polygon:
		switch (b->type)
		{
		case BodyType::AABB:
			break;
		case BodyType::Circle:
			break;
		case BodyType::Polygon:
			break;
		case BodyType::Null:
			break;
		}
		break;

	case BodyType::Null:
		switch (b->type)
		{
		case BodyType::AABB:
			break;
		case BodyType::Circle:
			break;
		case BodyType::Polygon:
			break;
		case BodyType::Null:
			break;
		}
		break;
	}
	Manifold m;
	m.collision = false;
	return m;
}