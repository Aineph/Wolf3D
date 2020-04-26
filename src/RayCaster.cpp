/*
 * Created by Nicolas Fez for Wolf3D.
 * Started on 2020-04-10.
 */

#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "IDrawable.hh"
#include "Position.hh"
#include "Level.hh"
#include "Player.hh"
#include "Display.hh"
#include "ARay.hh"
#include "HorizontalRay.hh"
#include "VerticalRay.hh"
#include "Minimap.hh"
#include "RayCaster.hh"

/**
 * The raycaster constructor.
 */
RayCaster::RayCaster::RayCaster()
{
    this->setMinimap(Minimap());
    this->setWindow(nullptr);
    this->setWindowSize(sf::Vector2u());
}

/**
 * The raycaster constructor.
 */
RayCaster::RayCaster::RayCaster(sf::RenderWindow *window, Level *level)
{
    sf::Vector2u const &windowDimensions = window->getSize();

    this->setMinimap(Minimap(level, windowDimensions));
    this->setWindow(window);
    this->setWindowSize(windowDimensions);
}

/**
 * The raycaster constructor.
 * @param other
 */
RayCaster::RayCaster::RayCaster(RayCaster const &other)
{
    this->setWindow(other.getWindow());
    this->setWindowSize(other.getWindowSize());
}

/**
 * The raycaster equal operator.
 * @param other
 */
RayCaster::RayCaster &RayCaster::RayCaster::operator=(RayCaster const &other)
{
    if (this != &other)
    {
        this->setWindow(other.getWindow());
        this->setWindowSize(other.getWindowSize());
    }
    return *this;
}

/**
 * Computes the view from the player's point of view.
 * @param playerPosition
 * @param levelMap
 */
void RayCaster::RayCaster::compute(Position const &playerPosition, Level *level,
                                   std::map<Level::BlockType, sf::Texture *> const &textures,
                                   Display::DisplayType displayType)
{
    sf::Vector2u const &windowDimensions = this->getWindowSize();
    Minimap minimap = this->getMinimap();
    ARay *currentRay;
    int windowRow = 0;
    int windowColumn = 0;

    while (windowRow < windowDimensions.y)
    {
        currentRay = new HorizontalRay(sf::Vector2u(0, windowRow), displayType);
        currentRay->initialize(playerPosition, windowDimensions);
        currentRay->cast(playerPosition, level, textures, windowDimensions);
        currentRay->render(this->getWindow());
        delete currentRay;
        windowRow += 1;
    }
    while (windowColumn < windowDimensions.x)
    {
        currentRay = new VerticalRay(sf::Vector2u(windowColumn, 0), displayType);
        currentRay->initialize(playerPosition, windowDimensions);
        currentRay->cast(playerPosition, level, textures, windowDimensions);
        currentRay->render(this->getWindow());
        delete currentRay;
        windowColumn += 1;
    }
    minimap.setPlayerPosition(playerPosition);
    this->setMinimap(minimap);
    this->getMinimap().render(this->getWindow());
}

/**
 * The getter for the minimap.
 * @return
 */
Minimap const &RayCaster::RayCaster::getMinimap() const
{
    return this->_minimap;
}

/**
 * The setter for the minimap.
 * @param minimap
 */
void RayCaster::RayCaster::setMinimap(Minimap const &minimap)
{
    this->_minimap = minimap;
}

/**
 * The getter for the window.
 * @return
 */
sf::RenderWindow *RayCaster::RayCaster::getWindow() const
{
    return this->_window;
}

/**
 * The setter for the window.
 * @param window
 */
void RayCaster::RayCaster::setWindow(sf::RenderWindow *window)
{
    this->_window = window;
}

/**
 * The getter for the window size.
 * @return
 */
sf::Vector2u const &RayCaster::RayCaster::getWindowSize() const
{
    return this->_windowSize;
}

/**
 * The setter for the window size.
 * @param windowSize
 */
void RayCaster::RayCaster::setWindowSize(sf::Vector2u const &windowSize)
{
    this->_windowSize = windowSize;
}
