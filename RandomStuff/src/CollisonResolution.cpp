#include "CollisionResolution.h"

namespace lge
{
	void ResolveCollision(Manifold m, PhysicsBody* a, PhysicsBody* b)
	{
		vec2 rv = b->velocity - a->velocity;

		float velAlongNormal = dotVec2(rv, m.normal);

		if (velAlongNormal > 0) return;

		float e = fminf(a->material.restitution, b->material.restitution);

		float j = -(1 + e) * velAlongNormal;
		j /= a->massData.invMass + b->massData.invMass;

		vec2 impulse = m.normal * j;

		a->velocity -= impulse * a->massData.invMass * a->movable;
		b->velocity += impulse * b->massData.invMass * b->movable;
	}

	void ResolveCollisionStatic(Manifold m, PhysicsBody* a, PhysicsBody* b)
	{
		if (a->collidedWithImmovable || !a->movable) b->collidedWithImmovable = true;
		if (b->collidedWithImmovable || !b->movable) a->collidedWithImmovable = true;

		vec2 aPos = getPosition(a);
		vec2 bPos = getPosition(b);
		aPos -= m.normal * (m.penetration / 2) * (a->movable || !a->collidedWithImmovable);
		bPos += m.normal * (m.penetration / 2) * (b->movable || !a->collidedWithImmovable);
		setPosition(a, aPos);
		setPosition(b, bPos);
	}

	void PositionalCorrection(Manifold m, PhysicsBody* a, PhysicsBody* b)
	{
		const float percent = 1.1;
		const float slop = 0.01;
		vec2 correction = m.normal * (max(m.penetration - slop, 0.0f) / (a->massData.invMass + b->massData.invMass)) * percent;
		vec2 pos1 = getPosition(a);
		vec2 pos2 = getPosition(b);

		pos1 -= correction * a->massData.invMass * a->movable;
		pos2 += correction * b->massData.invMass * b->movable;

		setPosition(a, pos1);
		setPosition(b, pos2);
	}

	Manifold Collide(PhysicsBody* a, PhysicsBody* b)
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
				m = AABBVsAABB(m);
				return m;
			}
			case BodyType::Circle:
			{
				Manifold m;
				m.a = *b;
				m.b = *a;
				m = CircleVsAABB(m);
				//positionalCorrection(m, a, b);
				ResolveCollisionStatic(m, b, a);
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
				m = CircleVsAABB(m);
				//positionalCorrection(m, a, b);
				ResolveCollisionStatic(m, a, b);
				return m;
			}
			case BodyType::Circle:
			{
				Manifold m;
				m.a = *a;
				m.b = *b;
				m = CircleVsCircle(m);
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
}