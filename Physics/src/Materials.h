#pragma once

namespace lge
{
	struct Material
	{
		double density = 0;
		double restitution = 0;
		double staticFriction = 0;
		double dynamicFriction = 0;

		Material(double density = 0, double restitution = 0, double staticFriction = 0, double dynamicFriction = 0) :
			density(density), restitution(restitution), staticFriction(staticFriction), dynamicFriction(dynamicFriction)
		{}
	};

	const Material STONE = Material(0.6, 0.2, 1, 1);// { 0.6, 0.2 };
	const Material WOOD = Material(0.3, 0.2, 1, 1);
	const Material METAL = Material(1.2, 0.05, 1, 1);
	const Material BOUNCYBALL = Material(0.3, 0.8, 1, 1);
	const Material SUPERBALL = Material(0.3, 0.95, 1, 1);
	const Material PILLOW = Material(0.1, 0.2, 1, 1);
	const Material STATIC = Material(0, 0.4, 1, 1);
	const Material PERFECT = Material(1, 1, 0, 1);
}