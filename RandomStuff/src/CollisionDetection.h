#pragma once

#include "components.h"

#include "PhysicsBodies.h"
#include "Physics.h"

namespace lge
{
	Manifold CircleVsAABB(Manifold m);
	Manifold AABBVsAABB(Manifold m);
	Manifold CircleVsCircle(Manifold m);
}