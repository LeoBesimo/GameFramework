#pragma once

namespace lge
{
	struct Material
	{
		double density;
		double restitution;

		Material(double density = 0, double restitution = 0) :
			density(density), restitution(restitution)
		{}
	};

	const Material STONE = { 0.6,0.2 };
	const Material WOOD = { 0.3,0.2 };
	const Material METAL = { 1.2,0.05 };
	const Material BOUNCYBALL = { 0.3,0.8 };
	const Material SUPERBALL = { 0.3,0.95 };
	const Material PILLOW = { 0.1,0.2 };
	const Material STATIC = { 0,0.4 };
	const Material PERFECT = { 1,1 };
}