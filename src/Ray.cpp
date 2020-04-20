/*
 * Created by Nicolas Fez for Wolf3D.
 * Started on 2020-04-16.
 */

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Position.hh"
#include "Level.hh"
#include "Player.hh"
#include "Display.hh"
#include "Ray.hh"

/**
 * The ray constructor.
 */
Ray::Ray()
{
    this->setRayPosition(Position());
    this->setIncrementalPosition(Position());
    this->setHitAxis(Ray::RayHitAxis::AXIS_X);
    this->setHitBlockType(Level::BlockType::BLOCK_STANDARD_WALL);
    this->setHitPosition(0);
    this->setWallDistance(0);
    this->setWallSize(0);
    this->setWallStart(0);
    this->setWallEnd(0);
    this->setWallTexturePosition(0);
    this->setWallColor(sf::Color::White);
    this->setWallTexture(nullptr);
    this->setWallTextureDimensions(sf::Vector2u());
}

/**
 * The ray constructor.
 * @param playerPosition
 * @param rayPosition
 * @param level
 * @param windowHeight
 */
Ray::Ray(Position const &playerPosition, Position const &rayPosition, Level *level, int windowHeight)
{
    this->setRayPosition(rayPosition);
    this->setIncrementalPosition(Position());
    this->setHitAxis(Ray::RayHitAxis::AXIS_X);
    this->setHitBlockType(Level::BlockType::BLOCK_STANDARD_WALL);
    this->setHitPosition(0);
    this->setWallDistance(0);
    this->setWallSize(0);
    this->setWallStart(0);
    this->setWallEnd(0);
    this->setWallTexturePosition(0);
    this->setWallColor(sf::Color::White);
    this->setWallTexture(nullptr);
    this->setWallTextureDimensions(sf::Vector2u());
    this->initialize(playerPosition);
    this->cast(level);
    this->fetchDistances(playerPosition);
    this->preComputeWallDimensions(windowHeight);
}

/**
 * The ray constructor.
 * @param other
 */
Ray::Ray(Ray const &other)
{
    this->setRayPosition(other.getRayPosition());
    this->setIncrementalPosition(other.getIncrementalPosition());
    this->setHitAxis(other.getHitAxis());
    this->setHitBlockType(other.getHitBlockType());
    this->setHitPosition(other.getHitPosition());
    this->setWallDistance(other.getWallDistance());
    this->setWallSize(other.getWallSize());
    this->setWallStart(other.getWallStart());
    this->setWallEnd(other.getWallEnd());
    this->setWallTexturePosition(other.getWallTexturePosition());
    this->setWallColor(other.getWallColor());
    this->setWallTexture(other.getWallTexture());
    this->setWallTextureDimensions(other.getWallTextureDimensions());
}

/**
 * The ray equal operator.
 * @param other
 * @return
 */
Ray &Ray::operator=(Ray const &other)
{
    if (this != &other)
    {
        this->setRayPosition(other.getRayPosition());
        this->setIncrementalPosition(other.getIncrementalPosition());
        this->setHitAxis(other.getHitAxis());
        this->setHitBlockType(other.getHitBlockType());
        this->setHitPosition(other.getHitPosition());
        this->setWallDistance(other.getWallDistance());
        this->setWallSize(other.getWallSize());
        this->setWallStart(other.getWallStart());
        this->setWallEnd(other.getWallEnd());
        this->setWallTexturePosition(other.getWallTexturePosition());
        this->setWallColor(other.getWallColor());
        this->setWallTexture(other.getWallTexture());
        this->setWallTextureDimensions(other.getWallTextureDimensions());
    }
    return *this;
}

/**
 * Initializes the texture of the wall.
 * @param wallTexture
 * @param windowHeight
 */
void Ray::initializeTexture(sf::Texture *wallTexture)
{
    this->setWallTexture(wallTexture);
    this->setWallTextureDimensions(wallTexture->getSize());
    this->setWallTexturePosition((this->getHitPosition() * this->getWallTextureDimensions().x) / POSITION_UNIT_X);
    if ((this->getHitAxis() == AXIS_Y && this->getRayPosition().getDirectionX() > 0) ||
        (this->getHitAxis() == AXIS_X && this->getRayPosition().getDirectionY() < 0))
        this->setWallTexturePosition(this->getWallTextureDimensions().x - this->getWallTexturePosition() - 1);
}

/**
 * Fills the screen content with the current ray.
 * @param screenContent
 * @param windowColumn
 * @param windowDimensions
 */
void Ray::fillScreen(sf::RenderWindow *window, int windowColumn, sf::Vector2u const &windowDimensions,
                     Display::DisplayType displayType)
{
    sf::RectangleShape sky(sf::Vector2f(1, this->getWallStart()));
    sf::RectangleShape wall(sf::Vector2f(1, this->getWallSize()));
    sf::RectangleShape floor(sf::Vector2f(1, this->getWallStart()));

    sky.setPosition(windowColumn, 0);
    wall.setPosition(windowColumn, this->getWallStart());
    floor.setPosition(windowColumn, this->getWallEnd());
    sky.setFillColor(sf::Color::Blue);
    if (displayType == Display::DisplayType::DISPLAY_VANILLA)
        wall.setFillColor(this->getWallColor());
    else
    {
        wall.setTexture(this->getWallTexture());
        wall.setTextureRect(sf::IntRect(this->getWallTexturePosition(), 0, 1, this->getWallTextureDimensions().y));
    }
    floor.setFillColor(sf::Color::Green);
    window->draw(sky);
    window->draw(wall);
    window->draw(floor);
}

/**
 * Initializes the ray variables.
 * @param playerPosition
 */
void Ray::initialize(Position const &playerPosition)
{
    Position incrementalPosition = this->getIncrementalPosition();
    Position const &rayPosition = this->getRayPosition();

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
    incrementalPosition.setPlaneX(((rayPosition.getDirectionX() < 0) ? (-POSITION_UNIT_X) : (POSITION_UNIT_X)));
    incrementalPosition.setPlaneY(((rayPosition.getDirectionY() < 0) ? (-POSITION_UNIT_Y) : (POSITION_UNIT_Y)));
    this->setIncrementalPosition(incrementalPosition);
}

/**
 * Casts a ray.
 * @param level
 */
void Ray::cast(Level *level)
{
    Position incrementalPosition = this->getIncrementalPosition();
    Position rayPosition = this->getRayPosition();
    bool wallEncountered = false;
    int positionX = 0;
    int positionY = 0;

    while (!wallEncountered)
    {
        if (rayPosition.getDirectionX() != 0 && (rayPosition.getDirectionY() == 0 ||
                                                 incrementalPosition.getPositionX() <
                                                 incrementalPosition.getPositionY()))
        {
            incrementalPosition.setPositionX(incrementalPosition.getPositionX() + incrementalPosition.getDirectionX());
            rayPosition.setPositionX(rayPosition.getPositionX() + incrementalPosition.getPlaneX());
            this->setHitAxis(RayHitAxis::AXIS_Y);
        }
        else
        {
            incrementalPosition.setPositionY(incrementalPosition.getPositionY() + incrementalPosition.getDirectionY());
            rayPosition.setPositionY(rayPosition.getPositionY() + incrementalPosition.getPlaneY());
            this->setHitAxis(RayHitAxis::AXIS_X);
        }
        positionX = rayPosition.getPositionX() / POSITION_UNIT_X;
        positionY = rayPosition.getPositionY() / POSITION_UNIT_Y;
        if (positionX >= level->getLevelWidth() || positionX < 0 || positionY >= level->getLevelHeight() ||
            positionY < 0 || Level::isLevelWall(level->getLevelMap()[positionY][positionX]))
        {
            this->setHitBlockType(static_cast<Level::BlockType >(level->getLevelMap()[positionY][positionX]));
            wallEncountered = true;
        }
    }
    this->setIncrementalPosition(incrementalPosition);
    this->setRayPosition(rayPosition);
}

/**
 * Fetch the distances between the player and the wall.
 * @param playerPosition
 */
void Ray::fetchDistances(Position const &playerPosition)
{
    Position const &incrementalPosition = this->getIncrementalPosition();
    Position const &rayPosition = this->getRayPosition();
    int hitPositionTemp = 0;

    if (this->getHitAxis() == AXIS_Y)
    {
        if (rayPosition.getDirectionX() == 0)
            this->setWallDistance(std::abs(rayPosition.getPositionX() - playerPosition.getPositionX()));
        else
            this->setWallDistance(((rayPosition.getPositionX() - playerPosition.getPositionX() +
                                    ((POSITION_UNIT_X - incrementalPosition.getPlaneX()) / 2)) * POSITION_UNIT_X) /
                                  rayPosition.getDirectionX());
        hitPositionTemp = playerPosition.getPositionY() +
                          (this->getWallDistance() * rayPosition.getDirectionY()) / POSITION_UNIT_X;
        this->setHitPosition(hitPositionTemp - ((hitPositionTemp / POSITION_UNIT_X) * POSITION_UNIT_X));
    }
    else
    {
        if (rayPosition.getDirectionY() == 0)
            this->setWallDistance(std::abs(rayPosition.getPositionY() - playerPosition.getPositionY()));
        else
            this->setWallDistance(((rayPosition.getPositionY() - playerPosition.getPositionY() +
                                    ((POSITION_UNIT_Y - incrementalPosition.getPlaneY()) / 2)) * POSITION_UNIT_Y) /
                                  rayPosition.getDirectionY());
        hitPositionTemp = playerPosition.getPositionX() +
                          (this->getWallDistance() * rayPosition.getDirectionX()) / POSITION_UNIT_Y;
        this->setHitPosition(hitPositionTemp - ((hitPositionTemp / POSITION_UNIT_Y) * POSITION_UNIT_Y));
    }
}

/**
 * Pre-computes the wall dimensions for the render window.
 * @param windowHeight
 */
void Ray::preComputeWallDimensions(int windowHeight)
{
    int wallPosition = 0;
    sf::Color wallColor;

    if (!this->getWallDistance())
        this->setWallSize(windowHeight);
    else
        this->setWallSize((windowHeight * POSITION_UNIT_Y) / this->getWallDistance());
    wallPosition = (windowHeight / 2) - (this->getWallSize() / 2);
    wallColor.r = (std::min(windowHeight, this->getWallSize()) * 255) / windowHeight;
    wallColor.g = (std::min(windowHeight, this->getWallSize()) * 255) / windowHeight;
    wallColor.b = (std::min(windowHeight, this->getWallSize()) * 255) / windowHeight;
    this->setWallStart(wallPosition);
    this->setWallEnd(windowHeight - wallPosition);
    this->setWallColor(wallColor);
}

/**
 * The getter for the ray position.
 * @return
 */
Position const &Ray::getRayPosition() const
{
    return this->_rayPosition;
}

/**
 * The setter for the ray position.
 * @param rayPosition
 */
void Ray::setRayPosition(const Position &rayPosition)
{
    this->_rayPosition = rayPosition;
}

/**
 * The getter for the incremental position.
 * @return
 */
Position const &Ray::getIncrementalPosition() const
{
    return this->_incrementalPosition;
}

/**
 * The setter for the incremental position.
 * @param incrementalPosition
 */
void Ray::setIncrementalPosition(Position const &incrementalPosition)
{
    this->_incrementalPosition = incrementalPosition;
}

/**
 * The getter for the hit axis.
 * @return
 */
Ray::RayHitAxis Ray::getHitAxis() const
{
    return this->_hitAxis;
}

/**
 * The setter for the hit axis.
 * @param hitAxis
 */
void Ray::setHitAxis(Ray::RayHitAxis hitAxis)
{
    this->_hitAxis = hitAxis;
}

/**
 * The getter for the hit block type.
 * @return
 */
Level::BlockType Ray::getHitBlockType() const
{
    return this->_hitBlockType;
}

/**
 * The setter for the hit block type.
 * @param hitBlockType
 */
void Ray::setHitBlockType(Level::BlockType hitBlockType)
{
    this->_hitBlockType = hitBlockType;
}

/**
 * The getter for the hit position.
 * @return
 */
int Ray::getHitPosition() const
{
    return this->_hitPosition;
}

/**
 * The setter for the hit position.
 * @param wallColumn
 */
void Ray::setHitPosition(int hitPosition)
{
    this->_hitPosition = hitPosition;
}

/**
 * The getter for the wall distance.
 * @return
 */
long Ray::getWallDistance() const
{
    return this->_wallDistance;
}

/**
 * The setter for the wall distance.
 * @param wallDistance
 */
void Ray::setWallDistance(long wallDistance)
{
    this->_wallDistance = wallDistance;
}

/**
 * The getter for the wall size.
 * @return
 */
int Ray::getWallSize() const
{
    return this->_wallSize;
}

/**
 * The setter for the wall size.
 * @param wallSize
 */
void Ray::setWallSize(int wallSize)
{
    this->_wallSize = wallSize;
}

/**
 * The getter for the wall start.
 * @return
 */
int Ray::getWallStart() const
{
    return this->_wallStart;
}

/**
 * The setter for the wall start.
 * @param wallStart
 */
void Ray::setWallStart(int wallStart)
{
    this->_wallStart = wallStart;
}

/**
 * The getter for the wall end.
 * @return
 */
int Ray::getWallEnd() const
{
    return this->_wallEnd;
}

/**
 * The setter for the wall end.
 * @param wallEnd
 */
void Ray::setWallEnd(int wallEnd)
{
    this->_wallEnd = wallEnd;
}

/**
 * The getter for the wall texture position.
 * @return
 */
int Ray::getWallTexturePosition() const
{
    return this->_wallTexturePosition;
}

/**
 * The setter for the wall texture position.
 * @param wallTexturePosition
 */
void Ray::setWallTexturePosition(int wallTexturePosition)
{
    this->_wallTexturePosition = wallTexturePosition;
}

/**
 * The getter for the wall color.
 * @return
 */
sf::Color const &Ray::getWallColor() const
{
    return this->_wallColor;
}

/**
 * The setter for the wall color.
 * @param wallColor
 */
void Ray::setWallColor(sf::Color const &wallColor)
{
    this->_wallColor = wallColor;
}

/**
 * The getter for the wall texture.
 * @return
 */
sf::Texture *Ray::getWallTexture() const
{
    return this->_wallTexture;
}

/**
 * The setter for the wall texture.
 * @param wallTexture
 */
void Ray::setWallTexture(sf::Texture *wallTexture)
{
    this->_wallTexture = wallTexture;
}

/**
 * The getter for the wall texture dimensions.
 * @return
 */
sf::Vector2u const &Ray::getWallTextureDimensions() const
{
    return this->_wallTextureDimensions;
}

/**
 * The setter for the wall texture dimensions.
 * @param wallTextureDimensions
 */
void Ray::setWallTextureDimensions(sf::Vector2u const &wallTextureDimensions)
{
    this->_wallTextureDimensions = wallTextureDimensions;
}
