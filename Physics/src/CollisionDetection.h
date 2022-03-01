#pragma once

#include "Components.h"
#include "Utilities.h"
#include "lgeMath.h"

#include "PhysicsBodies.h"
#include "Physics.h"

namespace lge
{
	Manifold CircleVsAABB(Manifold m);
	Manifold AABBVsAABB(Manifold m);
	Manifold CircleVsCircle(Manifold m);
}