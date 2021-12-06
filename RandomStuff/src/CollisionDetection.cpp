#include "CollisionDetection.h"

namespace lge
{
	Manifold CircleVsAABB(Manifold m)
	{
		m.collision = false;

		CircleStruct a = m.a.circle;
		AABBStruct b = m.b.aabb;

		vec2 L = clampVec2(a.pos, b.min, b.max);
		vec2 ab = L - a.pos;
		float d2 = dotVec2(ab, ab);
		float r2 = a.radius * a.radius;
		if (d2 < r2)
		{
			if (d2 != 0)
			{
				float d = sqrt(d2);
				vec2 n = ab.normalize();
				m.collision = true;
				m.penetration = (a.radius - d);
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
				m.penetration = (a.radius + depth);
				m.normal = n;
			}
		}
		//if(m.collision) std::cout << "AABB pos: " << getPosition(&m.b) << " Circle Pos: " << getPosition(&m.a) << " AABB vel: " << m.b.velocity << " Circle vel: " << m.a.velocity << " Normal: " << m.normal << " \n";

		return m;
	}
	
	Manifold AABBVsAABB(Manifold m)
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
	}
	
	Manifold CircleVsCircle(Manifold m)
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
			m.penetration = (a.radius + b.radius) - d;
			m.normal = n / d;
			//std::cout << "Circle Normals: " << n << " Penetration: " << m.penetration << "\n";
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
}