/*
 * Created by Nicolas Fez for Wolf3D.
 * Started on 2020-04-08.
 */

#include <iostream>
#include <string>
#include <vector>
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
 * The game constructor.
 */
Game::Game() : _currentPlayer(), _currentLevel()
{
    this->setCurrentPlayer(new Player());
    this->setCurrentLevel(new Level());
    this->setDisplay(Display::getInstance());
}

/**
 * The game destructor.
 */
Game::~Game()
{
    delete this->getCurrentPlayer();
    delete this->getCurrentLevel();
}

/**
 * The level constructor.
 * @param other
 */
Game &Game::operator=(Game const &other)
{
    if (this != &other)
    {
        this->setCurrentPlayer(other.getCurrentPlayer());
        this->setCurrentLevel(other.getCurrentLevel());
        this->setDisplay(other.getDisplay());
    }
    return *this;
}

/**
 * The game left shift operator.
 * @param os
 * @param game
 * @return
 */
std::ostream &operator<<(std::ostream &os, Game const &game)
{
    os << "********** GAME STATE **********" << std::endl;
    os << *game.getCurrentLevel() << std::endl;
    os << *game.getCurrentPlayer() << std::endl;
    os << "********************************" << std::endl;
    return os;
}

/**
 * Initializes the objects inside the game.
 * @return
 */
bool Game::start()
{
    Position playerPosition;

    try
    {
        playerPosition = this->getCurrentLevel()->loadLevelMap();
        this->getCurrentPlayer()->setPosition(playerPosition);
    } catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return false;
    }
    return true;
}

/**
 * Runs the game.
 * @return
 */
bool Game::run()
{
    this->getDisplay()->handleEvents(this->getCurrentPlayer(), this->getCurrentLevel());
    this->getDisplay()->render(this->getCurrentPlayer(), this->getCurrentLevel());
    return this->getDisplay()->isRunning();
}

/**
 * The getter for the current player.
 * @return
 */
Player *Game::getCurrentPlayer() const
{
    return this->_currentPlayer;
}

/**
 * The setter for the current level.
 * @param currentPlayer
 */
void Game::setCurrentPlayer(Player *currentPlayer)
{
    this->_currentPlayer = currentPlayer;
}

/**
 * The getter for the current level.
 * @return
 */
Level *Game::getCurrentLevel() const
{
    return this->_currentLevel;
}

/**
 * The setter for the current level.
 * @param currentLevel
 */
void Game::setCurrentLevel(Level *currentLevel)
{
    this->_currentLevel = currentLevel;
}

/**
 * The getter for the display.
 * @return
 */
Display *Game::getDisplay() const
{
    return this->_display;
}

/**
 * The setter for the display.
 * @param display
 */
void Game::setDisplay(Display *display)
{
    this->_display = display;
}
