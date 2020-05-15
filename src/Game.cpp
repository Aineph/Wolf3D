/*
 * Created by Nicolas Fez for Wolf3D.
 * Started on 2020-04-08.
 */

#include <iostream>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Position.hh"
#include "Level.hh"
#include "Player.hh"
#include "Display.hh"
#include "Game.hh"

/**
 * The game constructor.
 */
Game::Game()
{
    this->setDisplay(Display::getInstance());
    this->setCurrentPlayer(new Player());
    this->setCurrentLevel(new Level());
}

Game::Game(Game const &other)
{
    this->setDisplay(other.getDisplay());
    this->setCurrentPlayer(other.getCurrentPlayer());
    this->setCurrentLevel(other.getCurrentLevel());
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
 * The level equal operator.
 * @param other
 */
Game &Game::operator=(Game const &other)
{
    if (this != &other)
    {
        this->setDisplay(other.getDisplay());
        delete this->getCurrentPlayer();
        this->setCurrentPlayer(other.getCurrentPlayer());
        delete this->getCurrentLevel();
        this->setCurrentLevel(other.getCurrentLevel());
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

    playerPosition = this->getCurrentLevel()->loadLevelMap();
    this->getCurrentPlayer()->setPosition(playerPosition);
    return true;
}

/**
 * Runs the game.
 * @return
 */
bool Game::run()
{
    sf::Clock gameClock = this->getGameClock();

    this->getDisplay()->handleEvents(this->getCurrentPlayer(), this->getCurrentLevel());
    this->getDisplay()->render(this->getCurrentPlayer(), this->getCurrentLevel());
    std::cout << MICROSECONDS_PER_SECOND / gameClock.getElapsedTime().asMicroseconds() << " FPS" << std::endl;
    gameClock.restart();
    this->setGameClock(gameClock);
    return this->getDisplay()->isRunning();
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
 * The getter for the game clock.
 * @return
 */
sf::Clock const &Game::getGameClock() const
{
    return this->_gameClock;
}

/**
 * The setter for the game clock.
 * @param gameClock
 */
void Game::setGameClock(sf::Clock const &gameClock)
{
    this->_gameClock = gameClock;
}
