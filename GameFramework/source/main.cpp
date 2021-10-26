#include <SFML/Graphics.hpp>

#include "Game/Game.h"

#include <iostream>

int main()
{
//std::cout << "test" << "\n";

    create(1000 ,800);
    run();
    destroy();

    return 0;
}