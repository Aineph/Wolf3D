/*
 * Created by Nicolas Fez for Wolf3D.
 * Started on 2020-04-24.
 */

#include <map>
#include <SFML/Graphics.hpp>
#include "IDrawable.hh"
#include "Position.hh"
#include "Level.hh"
#include "Player.hh"
#include "Display.hh"
#include "ARay.hh"
#include "VerticalRay.hh"

/**
 * The vertical ray constructor.
 */
RayCaster::VerticalRay::VerticalRay() : RayCaster::ARay()
{
    this->setRayPosition(Position());
    this->setIncrementalPosition(Position());
}

/**
 * The vertical ray constructor.
 * @param rayCoordinates
 * @param rayDisplayType
 */
RayCaster::VerticalRay::VerticalRay(sf::Vector2u const &rayCoordinates, Display::DisplayType rayDisplayType) : ARay(
        rayCoordinates, rayDisplayType)
{
    this->setRayPosition(Position());
    this->setIncrementalPosition(Position());
}

/**
 * The vertical ray constructor.
 * @param other
 */
RayCaster::VerticalRay::VerticalRay(RayCaster::VerticalRay const &other) : RayCaster::ARay(other)
{
    this->setRayPosition(other.getRayPosition());
    this->setIncrementalPosition(other.getIncrementalPosition());
}

/**
 * The vertical ray equal operator.
 * @param other
 * @return
 */
RayCaster::VerticalRay &RayCaster::VerticalRay::operator=(RayCaster::VerticalRay const &other)
{
    if (this != &other)
    {
        ARay::operator=(other);
        this->setRayPosition(other.getRayPosition());
        this->setIncrementalPosition(other.getIncrementalPosition());
    }
    return *this;
}

/**
 * Initializes the vertical ray.
 * @param playerPosition
 * @param windowDimensions
 */
void RayCaster::VerticalRay::initialize(Position const &playerPosition, sf::Vector2u const &windowDimensions)
{
    sf::Vector2i const *rayCoordinates = this->getRayCoordinates();
    Position rayPosition = Position();
    Position incrementalPosition = Position();
    sf::Vector2i incrementalSteps = sf::Vector2i();
    int cameraPosition = 0;

    if (RAY_VERTEX_NUMBER > 0)
        cameraPosition = (((2 * rayCoordinates[RAY_VERTEX_NUMBER - 1].x) * POSITION_UNIT_X) / windowDimensions.x) -
                         POSITION_UNIT_X;
    rayPosition.setPositionX((playerPosition.getPositionX() / POSITION_UNIT_X) * POSITION_UNIT_X);
    rayPosition.setPositionY((playerPosition.getPositionY() / POSITION_UNIT_Y) * POSITION_UNIT_Y);
    rayPosition.setDirectionX(
            static_cast<long>(playerPosition.getDirectionX() + (playerPosition.getPlaneX() * cameraPosition)));
    rayPosition.setDirectionY(
            static_cast<long>(playerPosition.getDirectionY() + (playerPosition.getPlaneY() * cameraPosition)));
    if (rayPosition.getDirectionX() == 0)
        incrementalPosition.setDirectionX(0);
    else
        incrementalPosition.setDirectionX(std::abs((POSITION_UNIT_X * POSITION_UNIT_X) / rayPosition.getDirectionX()));
    if (rayPosition.getDirectionX() < 0)
        incrementalPosition.setPositionX(
                ((playerPosition.getPositionX() - rayPosition.getPositionX()) * incrementalPosition.getDirectionX()) /
                POSITION_UNIT_X);
    else
        incrementalPosition.setPositionX(
                ((rayPosition.getPositionX() + POSITION_UNIT_X - playerPosition.getPositionX()) *
                 incrementalPosition.getDirectionX()) / POSITION_UNIT_X);
    if (rayPosition.getDirectionY() == 0)
        incrementalPosition.setDirectionY(0);
    else
        incrementalPosition.setDirectionY(std::abs((POSITION_UNIT_Y * POSITION_UNIT_Y) / rayPosition.getDirectionY()));
    if (rayPosition.getDirectionY() <= 0)
        incrementalPosition.setPositionY(
                ((playerPosition.getPositionY() - rayPosition.getPositionY()) * incrementalPosition.getDirectionY()) /
                POSITION_UNIT_Y);
    else
        incrementalPosition.setPositionY(
                ((rayPosition.getPositionY() + POSITION_UNIT_Y - playerPosition.getPositionY()) *
                 incrementalPosition.getDirectionY()) / POSITION_UNIT_Y);
    incrementalSteps.x = ((rayPosition.getDirectionX() < 0) ? (-POSITION_UNIT_X) : (POSITION_UNIT_X));
    incrementalSteps.y = ((rayPosition.getDirectionY() < 0) ? (-POSITION_UNIT_Y) : (POSITION_UNIT_Y));
    this->setRayPosition(rayPosition);
    this->setIncrementalPosition(incrementalPosition);
    this->setIncrementalSteps(incrementalSteps);
}

/**
 * Casts the vertical ray.
 * @param playerPosition
 * @param level
 * @param levelTextures
 * @param windowDimensions
 */
void RayCaster::VerticalRay::cast(Position const &playerPosition, Level *level,
                                  std::map<Level::BlockType, sf::Texture *> const &levelTextures,
                                  sf::Vector2u const &windowDimensions)
{
    Position incrementalPosition = this->getIncrementalPosition();
    Position rayPosition = this->getRayPosition();
    bool wallEncountered = false;
    int hitAxis = 0;
    int positionX = 0;
    int positionY = 0;

    while (!wallEncountered)
    {
        if (rayPosition.getDirectionX() != 0 && (rayPosition.getDirectionY() == 0 ||
                                                 incrementalPosition.getPositionX() <
                                                 incrementalPosition.getPositionY()))
        {
            incrementalPosition.setPositionX(incrementalPosition.getPositionX() + incrementalPosition.getDirectionX());
            rayPosition.setPositionX(rayPosition.getPositionX() + this->getIncrementalSteps().x);
            hitAxis = 0;
        }
        else
        {
            incrementalPosition.setPositionY(incrementalPosition.getPositionY() + incrementalPosition.getDirectionY());
            rayPosition.setPositionY(rayPosition.getPositionY() + this->getIncrementalSteps().y);
            hitAxis = 1;
        }
        positionX = rayPosition.getPositionX() / POSITION_UNIT_X;
        positionY = rayPosition.getPositionY() / POSITION_UNIT_Y;
        if (positionX >= level->getLevelWidth() || positionX < 0 || positionY >= level->getLevelHeight() ||
            positionY < 0)
            return this->setRayTexture(nullptr);
        if (Level::isLevelWall(level->getLevelMap()[positionY][positionX]))
        {
            this->setRayTexture(
                    levelTextures.at(static_cast<Level::BlockType>(level->getLevelMap()[positionY][positionX])));
            wallEncountered = true;
        }
    }
    this->setIncrementalPosition(incrementalPosition);
    this->setRayPosition(rayPosition);
    this->fillCoordinates(hitAxis, playerPosition, windowDimensions);
}

/**
 * Fills the vertical ray coordinates.
 * @param hitAxis
 * @param playerPosition
 * @param windowDimensions
 */
void RayCaster::VerticalRay::fillCoordinates(int hitAxis, Position const &playerPosition,
                                             sf::Vector2u const &windowDimensions)
{
    Position const &rayPosition = this->getRayPosition();
    sf::Color rayColor = this->getRayColor();
    unsigned int wallSize = 0;
    int coordinateIndex = 0;
    int hitPosition = 0;

    if (hitAxis == 0)
    {
        if (rayPosition.getDirectionX() == 0)
            this->setRayDistance(std::abs(rayPosition.getPositionX() - playerPosition.getPositionX()));
        else
            this->setRayDistance(((rayPosition.getPositionX() - playerPosition.getPositionX() +
                                   ((POSITION_UNIT_X - this->getIncrementalSteps().x) / 2)) * POSITION_UNIT_X) /
                                 rayPosition.getDirectionX());
        hitPosition = playerPosition.getPositionY() +
                      (this->getRayDistance() * rayPosition.getDirectionY()) / POSITION_UNIT_X;
        hitPosition = hitPosition - ((hitPosition / POSITION_UNIT_X) * POSITION_UNIT_X);
    }
    else
    {
        if (rayPosition.getDirectionY() == 0)
            this->setRayDistance(std::abs(rayPosition.getPositionY() - playerPosition.getPositionY()));
        else
            this->setRayDistance(((rayPosition.getPositionY() - playerPosition.getPositionY() +
                                   ((POSITION_UNIT_Y - this->getIncrementalSteps().y) / 2)) * POSITION_UNIT_Y) /
                                 rayPosition.getDirectionY());
        hitPosition = playerPosition.getPositionX() +
                      (this->getRayDistance() * rayPosition.getDirectionX()) / POSITION_UNIT_Y;
        hitPosition = hitPosition - ((hitPosition / POSITION_UNIT_Y) * POSITION_UNIT_Y);
    }
    hitPosition = (hitPosition * this->getRayTexture()->getSize().x) / POSITION_UNIT_X;
    if (this->getRayDistance() == 0)
        wallSize = windowDimensions.y;
    else
        wallSize = (windowDimensions.y * POSITION_UNIT_Y) / this->getRayDistance();
    if ((hitAxis == 0 && this->getRayPosition().getDirectionX() > 0) ||
        (hitAxis == 1 && this->getRayPosition().getDirectionY() < 0))
        hitPosition = this->getRayTexture()->getSize().x - hitPosition - 1;
    while (coordinateIndex < RAY_VERTEX_NUMBER)
    {
        this->getRayCoordinates()[coordinateIndex].y =
                (((windowDimensions.y / 2) + playerPosition.getPitch()) - (wallSize / 2)) +
                (coordinateIndex * (wallSize / (RAY_VERTEX_NUMBER - 1)));
        this->getRayTextureCoordinates()[coordinateIndex].x = hitPosition;
        this->getRayTextureCoordinates()[coordinateIndex].y =
                coordinateIndex * (this->getRayTexture()->getSize().y / (RAY_VERTEX_NUMBER - 1));
        coordinateIndex += 1;
    }
    rayColor.r = (255 * std::min(windowDimensions.y, wallSize)) / windowDimensions.y;
    rayColor.g = (255 * std::min(windowDimensions.y, wallSize)) / windowDimensions.y;
    rayColor.b = (255 * std::min(windowDimensions.y, wallSize)) / windowDimensions.y;
    this->setRayColor(rayColor);
}

/**
 * The getter for the ray position.
 * @return
 */
Position const &RayCaster::VerticalRay::getRayPosition() const
{
    return this->_rayPosition;
}

/**
 * The setter for the ray position.
 * @param rayPosition
 */
void RayCaster::VerticalRay::setRayPosition(Position const &rayPosition)
{
    this->_rayPosition = rayPosition;
}

/**
 * The getter for the incremental position.
 * @return
 */
Position const &RayCaster::VerticalRay::getIncrementalPosition() const
{
    return this->_incrementalPosition;
}

/**
 * The setter for the incremental position.
 * @param incrementalPosition
 */
void RayCaster::VerticalRay::setIncrementalPosition(Position const &incrementalPosition)
{
    this->_incrementalPosition = incrementalPosition;
}
