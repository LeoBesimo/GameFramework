#pragma once

namespace lge
{
	class Engine
	{

	public:
		Engine();
		~Engine();


		void create(int width, int height);
		void run();
		void destroy();
	};
}