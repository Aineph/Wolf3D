/*
 * Created by Nicolas Fez for Wolf3D.
 * Started on 2020-04-08.
 */

#include <iostream>
#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <exception>
#include "Position.hh"
#include "Level.hh"
#include "Player.hh"
#include "Display.hh"
#include "Game.hh"

/**
 * The main function.
 * @return
 */
int main()
{
    bool isRunning = true;

    try
    {
        Game *game = new Game();

        if (!game->start())
            return 1;
        while (isRunning)
        {
            isRunning = game->run();
        }
    } catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
