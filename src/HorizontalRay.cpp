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
#include "HorizontalRay.hh"

/**
 * The horizontal ray constructor.
 */
RayCaster::HorizontalRay::HorizontalRay() : ARay()
{
    this->setFirstRayPosition(Position());
    this->setLastRayPosition(Position());
}

/**
 * The horizontal ray constructor.
 * @param rayCoordinates
 * @param rayDisplayType
 */
RayCaster::HorizontalRay::HorizontalRay(sf::Vector2u const &rayCoordinates, Display::DisplayType rayDisplayType) : ARay(
        rayCoordinates, rayDisplayType)
{
    this->setFirstRayPosition(Position());
    this->setLastRayPosition(Position());
}

/**
 * The horizontal ray constructor.
 * @param other
 */
RayCaster::HorizontalRay::HorizontalRay(const RayCaster::HorizontalRay &other) : ARay(other)
{
    this->setFirstRayPosition(other.getFirstRayPosition());
    this->setLastRayPosition(other.getLastRayPosition());
}

/**
 * The horizontal ray equal operator.
 * @param other
 * @return
 */
RayCaster::HorizontalRay &RayCaster::HorizontalRay::operator=(const RayCaster::HorizontalRay &other)
{
    if (this != &other)
    {
        ARay::operator=(other);
        this->setFirstRayPosition(other.getFirstRayPosition());
        this->setLastRayPosition(other.getLastRayPosition());

    }
    return *this;
}

/**
 * Initializes the horizontal ray.
 * @param playerPosition
 * @param windowDimensions
 */
void RayCaster::HorizontalRay::initialize(Position const &playerPosition, sf::Vector2u const &windowDimensions)
{
    Position firstRayPosition = this->getFirstRayPosition();
    Position lastRayPosition = this->getLastRayPosition();

    firstRayPosition.setDirectionX(
            (playerPosition.getDirectionX() - static_cast<long>(playerPosition.getPlaneX() * POSITION_UNIT_X)));
    firstRayPosition.setDirectionY(
            (playerPosition.getDirectionY() - static_cast<long>(playerPosition.getPlaneY() * POSITION_UNIT_Y)));
    lastRayPosition.setDirectionX(
            (playerPosition.getDirectionX() + static_cast<long>(playerPosition.getPlaneX() * POSITION_UNIT_X)));
    lastRayPosition.setDirectionY(
            (playerPosition.getDirectionY() + static_cast<long>(playerPosition.getPlaneY() * POSITION_UNIT_Y)));
    this->setFirstRayPosition(firstRayPosition);
    this->setLastRayPosition(lastRayPosition);
}

/**
 * Casts the horizontal ray.
 * @param playerPosition
 * @param level
 * @param levelTextures
 * @param windowDimensions
 */
void RayCaster::HorizontalRay::cast(Position const &playerPosition, Level *level,
                                    std::map<Level::BlockType, sf::Texture *> const &levelTextures,
                                    sf::Vector2u const &windowDimensions)
{
    Position firstRayPosition = this->getFirstRayPosition();
    Position lastRayPosition = this->getLastRayPosition();
    sf::Vector2i incrementalSteps = this->getIncrementalSteps();
    sf::Color rayColor = this->getRayColor();
    char rayBrightness = 0;
    int coordinateIndex = 0;

    rayBrightness = (std::abs(static_cast<int>((windowDimensions.y / 2) + playerPosition.getPitch()) -
                              this->getRayCoordinates()[RAY_VERTEX_NUMBER - 1].y) * 255) / (windowDimensions.y * 2);
    this->setRayDistance(0);
    if (RAY_VERTEX_NUMBER > 0)
    {
        if (this->getRayCoordinates()[RAY_VERTEX_NUMBER - 1].y -
            ((windowDimensions.y / 2) + playerPosition.getPitch()) != 0)
            this->setRayDistance(((static_cast<int>(windowDimensions.y) / 2) * POSITION_UNIT_X) /
                                 (this->getRayCoordinates()[RAY_VERTEX_NUMBER - 1].y -
                                  ((static_cast<int>(windowDimensions.y) / 2) + playerPosition.getPitch())));
        if (this->getRayDistance() >= 0)
        {
            this->setRayTexture(levelTextures.at(Level::BlockType::BLOCK_WOODEN_WALL));
            if (this->getRayDisplayType() == Display::DisplayType::DISPLAY_VANILLA)
                rayColor.g = rayBrightness;
        }
        else
        {
            this->setRayDistance(-this->getRayDistance());
            this->setRayTexture(levelTextures.at(Level::BlockType::BLOCK_BLUE_WALL));
            if (this->getRayDisplayType() == Display::DisplayType::DISPLAY_VANILLA)
                rayColor.b = rayBrightness;
        }
        if (this->getRayDisplayType() == Display::DisplayType::DISPLAY_TEXTURED)
        {
            rayColor.r = rayBrightness;
            rayColor.g = rayBrightness;
            rayColor.b = rayBrightness;
        }
        this->getRayTexture()->setRepeated(true);
    }
    firstRayPosition.setPositionX(((playerPosition.getPositionX() * POSITION_UNIT_X) +
                                   (this->getRayDistance() * firstRayPosition.getDirectionX())) / POSITION_UNIT_X);
    firstRayPosition.setPositionY(((playerPosition.getPositionY() * POSITION_UNIT_Y) +
                                   (this->getRayDistance() * firstRayPosition.getDirectionY())) / POSITION_UNIT_Y);
    incrementalSteps.x =
            (this->getRayDistance() * (lastRayPosition.getDirectionX() - firstRayPosition.getDirectionX())) /
            POSITION_UNIT_X;
    incrementalSteps.y =
            (this->getRayDistance() * (lastRayPosition.getDirectionY() - firstRayPosition.getDirectionY())) /
            POSITION_UNIT_Y;
    while (coordinateIndex < RAY_VERTEX_NUMBER)
    {
        this->getRayCoordinates()[coordinateIndex].x = coordinateIndex * (windowDimensions.x / (RAY_VERTEX_NUMBER - 1));
        this->getRayTextureCoordinates()[coordinateIndex].x = this->getRayTexture()->getSize().x *
                                                              (((static_cast<double>(firstRayPosition.getPositionX()) /
                                                                 POSITION_UNIT_X) - static_cast<int>(
                                                                        static_cast<double>(firstRayPosition.getPositionX()) /
                                                                        POSITION_UNIT_X)) + (coordinateIndex *
                                                                                             ((static_cast<double>(incrementalSteps.x) /
                                                                                               POSITION_UNIT_X) /
                                                                                              (RAY_VERTEX_NUMBER -
                                                                                               1))));
        this->getRayTextureCoordinates()[coordinateIndex].y = this->getRayTexture()->getSize().y *
                                                              (((static_cast<double>(firstRayPosition.getPositionY()) /
                                                                 POSITION_UNIT_Y) - static_cast<int>(
                                                                        static_cast<double>(firstRayPosition.getPositionY()) /
                                                                        POSITION_UNIT_Y)) + (coordinateIndex *
                                                                                             ((static_cast<double>(incrementalSteps.y) /
                                                                                               POSITION_UNIT_Y) /
                                                                                              (RAY_VERTEX_NUMBER -
                                                                                               1))));
        coordinateIndex += 1;
    }
    this->setFirstRayPosition(firstRayPosition);
    this->setIncrementalSteps(incrementalSteps);
    this->setRayColor(rayColor);
}

/**
 * The getter for the first ray position.
 * @return
 */
Position const &RayCaster::HorizontalRay::getFirstRayPosition() const
{
    return this->_firstRayPosition;
}

/**
 * The setter for the first ray position.
 * @param firstRayPosition
 */
void RayCaster::HorizontalRay::setFirstRayPosition(Position const &firstRayPosition)
{
    this->_firstRayPosition = firstRayPosition;
}

/**
 * The getter for the last ray position.
 * @return
 */
Position const &RayCaster::HorizontalRay::getLastRayPosition() const
{
    return this->_lastRayPosition;
}

/**
 * The setter for the last ray position.
 * @param lastRayPosition
 */
void RayCaster::HorizontalRay::setLastRayPosition(Position const &lastRayPosition)
{
    this->_lastRayPosition = lastRayPosition;
}
