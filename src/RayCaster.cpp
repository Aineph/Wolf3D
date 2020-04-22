/*
 * Created by Nicolas Fez for Wolf3D.
 * Started on 2020-04-10.
 */

#include <iostream>
#include <vector>
#include <map>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Position.hh"
#include "Level.hh"
#include "Player.hh"
#include "Display.hh"
#include "Ray.hh"
#include "RayCaster.hh"

/**
 * The raycaster constructor.
 */
RayCaster::RayCaster()
{
    this->setRayPosition(Position());
    this->setWindow(nullptr);
    this->setWindowSize(sf::Vector2u());
}

/**
 * The raycaster constructor.
 */
RayCaster::RayCaster(sf::RenderWindow *window)
{
    this->setRayPosition(Position());
    this->setWindow(window);
    this->setWindowSize(window->getSize());
}

/**
 * The raycaster constructor.
 * @param other
 */
RayCaster::RayCaster(RayCaster const &other)
{
    this->setRayPosition(other.getRayPosition());
    this->setWindow(other.getWindow());
    this->setWindowSize(other.getWindowSize());
}

/**
 * The raycaster equal operator.
 * @param other
 */
RayCaster &RayCaster::operator=(RayCaster const &other)
{
    if (this != &other)
    {
        this->setRayPosition(other.getRayPosition());
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
void RayCaster::compute(Position const &playerPosition, Level *level,
                        std::map<Level::BlockType, sf::Texture *> const &textures, Display::DisplayType displayType)
{
    sf::Vector2u const &windowDimensions = this->getWindowSize();
    sf::RectangleShape floor;
    sf::Texture *floorTexture;
    int windowRow = 0;
    int windowColumn = 0;
    Ray currentRay;

    floorTexture = textures.at(Level::BlockType::BLOCK_WOODEN_WALL);
    while (windowRow < windowDimensions.y)
    {
//        floor = sf::RectangleShape(sf::Vector2f(windowDimensions.x, 1));
        //       floor.setPosition(0, windowRow);
        //      floor.setFillColor(sf::Color::Yellow);
        //    floor.setTexture(floorTexture);
        //  floor.setTextureRect(sf::IntRect(0, windowRow % 64, 1, 64));
        // this->getWindow()->draw(floor);
        windowRow += 1;
    }
    while (windowColumn < windowDimensions.x)
    {
        this->initialize(windowColumn, playerPosition);
        currentRay = Ray(playerPosition, this->getRayPosition(), level, windowDimensions.y);
        currentRay.initializeTexture(textures.at(currentRay.getHitBlockType()));
        currentRay.fillScreen(this->getWindow(), windowColumn, windowDimensions, displayType);
        windowColumn += 1;
    }
}

/**
 * Initializes the raycasting vectors.
 * @param playerPosition
 * @return
 */
void RayCaster::initialize(int windowColumn, Position const &playerPosition)
{
    Position rayPosition = this->getRayPosition();
    int cameraPosition = 0;

    cameraPosition = (((2 * windowColumn) * POSITION_UNIT_X) / this->getWindowSize().x) - POSITION_UNIT_X;
    rayPosition.setPositionX((playerPosition.getPositionX() / POSITION_UNIT_X) * POSITION_UNIT_X);
    rayPosition.setPositionY((playerPosition.getPositionY() / POSITION_UNIT_Y) * POSITION_UNIT_Y);
    rayPosition.setDirectionX(
            static_cast<long>(playerPosition.getDirectionX() + (playerPosition.getPlaneX() * cameraPosition)));
    rayPosition.setDirectionY(
            static_cast<long>(playerPosition.getDirectionY() + (playerPosition.getPlaneY() * cameraPosition)));
    this->setRayPosition(rayPosition);
}

/**
 * The getter for the ray position.
 * @return
 */
Position const &RayCaster::getRayPosition() const
{
    return this->_rayPosition;
}

/**
 * The setter for the ray position.
 * @param rayPosition
 */
void RayCaster::setRayPosition(Position const &rayPosition)
{
    this->_rayPosition = rayPosition;
}

/**
 * The getter for the window.
 * @return
 */
sf::RenderWindow *RayCaster::getWindow() const
{
    return this->_window;
}

/**
 * The setter for the window.
 * @param window
 */
void RayCaster::setWindow(sf::RenderWindow *window)
{
    this->_window = window;
}

/**
 * The getter for the window size.
 * @return
 */
sf::Vector2u const &RayCaster::getWindowSize() const
{
    return this->_windowSize;
}

/**
 * The setter for the window size.
 * @param windowSize
 */
void RayCaster::setWindowSize(sf::Vector2u const &windowSize)
{
    this->_windowSize = windowSize;
}
