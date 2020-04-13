/*
 * Created by Nicolas Fez for Wolf3D.
 * Started on 2020-04-10.
 */

#include <iostream>
#include <vector>
#include <SFML/System.hpp>
#include "Position.hh"
#include "Level.hh"
#include "RayCaster.hh"

/**
 * The raycaster constructor.
 */
RayCaster::RayCaster()
{
    this->setRayPosition(Position());
    this->setDeltaDistance(sf::Vector2i());
    this->setSideDistance(sf::Vector2i());
    this->setSteps(sf::Vector2i());
    this->setHitDirection(0);
    this->setPreviousWallDistance(0);
}

/**
 * The raycaster constructor.
 * @param other
 */
RayCaster::RayCaster(RayCaster const &other)
{
    this->setRayPosition(other.getRayPosition());
    this->setDeltaDistance(other.getDeltaDistance());
    this->setSideDistance(other.getSideDistance());
    this->setSteps(other.getSteps());
    this->setHitDirection(other.getHitDirection());
    this->setPreviousWallDistance(other.getPreviousWallDistance());
}

/**
 * Renders the view from the player's point of view.
 * @param playerPosition
 * @param levelMap
 */
int RayCaster::render(Position const &playerPosition, Level *level)
{
    int wallDistance;

    this->initializeVectors(playerPosition);
    this->computeDistances(playerPosition);
    this->cast(level);
    if (!this->getHitDirection())
    {
        if (this->getRayPosition().getDirectionX() == 0)
            wallDistance = this->getPreviousWallDistance();
        else
            wallDistance = ((this->getRayPosition().getPositionX() - playerPosition.getPositionX() +
                             ((POSITION_UNIT_X - this->getSteps().x) / 2)) * POSITION_UNIT_X) /
                           this->getRayPosition().getDirectionX();
    }
    else
    {
        if (this->getRayPosition().getDirectionY() == 0)
            wallDistance = this->getPreviousWallDistance();
        else
            wallDistance = ((this->getRayPosition().getPositionY() - playerPosition.getPositionY() +
                             ((POSITION_UNIT_Y - this->getSteps().y) / 2)) * POSITION_UNIT_Y) /
                           this->getRayPosition().getDirectionY();
    }
    this->setPreviousWallDistance(wallDistance);
    return wallDistance;
}

/**
 * Initializes the raycasting vectors.
 * @param playerPosition
 * @return
 */
void RayCaster::initializeVectors(Position const &playerPosition)
{
    if (this->getRayPosition().getDirectionX() == 0)
        this->_deltaDistance.x = 0;
    else
        this->_deltaDistance.x = std::abs((POSITION_UNIT_X * POSITION_UNIT_X) / this->getRayPosition().getDirectionX());
    if (this->getRayPosition().getDirectionY() == 0)
        this->_deltaDistance.y = 0;
    else
        this->_deltaDistance.y = std::abs((POSITION_UNIT_Y * POSITION_UNIT_Y) / this->getRayPosition().getDirectionY());
}

/**
 * Computes the raycasting distances.
 * @param playerPosition
 */
void RayCaster::computeDistances(Position const &playerPosition)
{
    if (this->getRayPosition().getDirectionX() < 0)
    {
        this->_steps.x = -POSITION_UNIT_X;
        this->_sideDistance.x =
                ((playerPosition.getPositionX() - this->getRayPosition().getPositionX()) * this->_deltaDistance.x) /
                POSITION_UNIT_X;
    }
    else
    {
        this->_steps.x = POSITION_UNIT_X;
        this->_sideDistance.x =
                ((this->getRayPosition().getPositionX() + POSITION_UNIT_X - playerPosition.getPositionX()) *
                 this->_deltaDistance.x) / POSITION_UNIT_X;
    }
    if (this->getRayPosition().getDirectionY() < 0)
    {
        this->_steps.y = -POSITION_UNIT_Y;
        this->_sideDistance.y =
                ((playerPosition.getPositionY() - this->getRayPosition().getPositionY()) * this->_deltaDistance.y) /
                POSITION_UNIT_Y;
    }
    else
    {
        this->_steps.y = POSITION_UNIT_Y;
        this->_sideDistance.y =
                ((this->getRayPosition().getPositionY() + POSITION_UNIT_Y - playerPosition.getPositionY()) *
                 this->_deltaDistance.y) / POSITION_UNIT_Y;
    }
}

/**
 * Casts a ray until it hits a wall.
 * @param levelMap
 */
void RayCaster::cast(Level *level)
{
    bool wallEncountered = false;
    long positionX = 0;
    long positionY = 0;

    while (!wallEncountered)
    {
        if (this->_sideDistance.x < this->_sideDistance.y)
        {
            this->_sideDistance.x += this->_deltaDistance.x;
            this->_rayPosition.setPositionX(this->getRayPosition().getPositionX() + this->getSteps().x);
            this->setHitDirection(0);
        }
        else
        {
            this->_sideDistance.y += this->_deltaDistance.y;
            this->_rayPosition.setPositionY(this->getRayPosition().getPositionY() + this->getSteps().y);
            this->setHitDirection(1);
        }
        positionX = this->getRayPosition().getPositionX() / POSITION_UNIT_X;
        positionY = this->getRayPosition().getPositionY() / POSITION_UNIT_Y;
        if (positionX >= level->getLevelWidth() || positionX < 0 || positionY >= level->getLevelHeight() ||
            positionY < 0 || level->getLevelMap()[positionY][positionX] == Level::BLOCK_STANDARD_WALL)
            wallEncountered = true;
    }
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
 * The getter for the delta distance.
 * @return
 */
sf::Vector2i const &RayCaster::getDeltaDistance() const
{
    return this->_deltaDistance;
}

/**
 * The setter for the delta distance.
 * @param deltaDistance
 */
void RayCaster::setDeltaDistance(sf::Vector2i const &deltaDistance)
{
    this->_deltaDistance = deltaDistance;
}

/**
 * The getter for the side distance.
 * @return
 */
sf::Vector2i const &RayCaster::getSideDistance() const
{
    return this->_sideDistance;
}

/**
 * The setter for the side distance.
 * @param sideDistance
 */
void RayCaster::setSideDistance(sf::Vector2i const &sideDistance)
{
    this->_sideDistance = sideDistance;
}

/**
 * The getter for the steps.
 * @return
 */
sf::Vector2i const &RayCaster::getSteps() const
{
    return this->_steps;
}

/**
 * The setter for the steps.
 * @param steps
 */
void RayCaster::setSteps(sf::Vector2i const &steps)
{
    this->_steps = steps;
}

/**
 * The getter for the hit direction.
 * @return
 */
int RayCaster::getHitDirection() const
{
    return this->_hitDirection;
}

/**
 * The setter for the hit direction.
 * @param hitDirection
 */
void RayCaster::setHitDirection(int hitDirection)
{
    this->_hitDirection = hitDirection;
}

/**
 * The getter for the previous wall height.
 * @return
 */
int RayCaster::getPreviousWallDistance() const
{
    return this->_previousWallDistance;
}

/**
 * The setter for the previous wall height.
 */
void RayCaster::setPreviousWallDistance(int wallDistance)
{
    this->_previousWallDistance = wallDistance;
}
