/*
 * Created by Nicolas Fez for Wolf3D.
 * Started on 2020-04-23.
 */

#include <map>
#include <vector>
#include <SFML/Graphics.hpp>
#include "IDrawable.hh"
#include "Position.hh"
#include "Level.hh"
#include "Player.hh"
#include "Display.hh"
#include "ARay.hh"

/**
 * The ray constructor.
 */
RayCaster::ARay::ARay()
{
    this->setRayDistance(0);
    this->setRayCoordinates(new sf::Vector2i[RAY_VERTEX_NUMBER]);
    this->setRayTextureCoordinates(new sf::Vector2f[RAY_VERTEX_NUMBER]);
    this->setIncrementalSteps(sf::Vector2i());
    this->setRayDisplayType(Display::DisplayType::DISPLAY_VANILLA);
    this->setRayColor(sf::Color::Black);
    this->setRayTexture(nullptr);
}

/**
 * The ray constructor.
 * @param rayCoordinates
 * @param rayDisplayType
 */
RayCaster::ARay::ARay(sf::Vector2u const &rayCoordinates, Display::DisplayType rayDisplayType)
{
    int coordinateIndex = 0;

    this->setRayDistance(0);
    this->setRayCoordinates(new sf::Vector2i[RAY_VERTEX_NUMBER]);
    this->setRayTextureCoordinates(new sf::Vector2f[RAY_VERTEX_NUMBER]);
    this->setIncrementalSteps(sf::Vector2i());
    this->setRayDisplayType(rayDisplayType);
    this->setRayColor(sf::Color::Black);
    this->setRayTexture(nullptr);
    while (coordinateIndex < RAY_VERTEX_NUMBER)
    {
        this->getRayCoordinates()[coordinateIndex].x = rayCoordinates.x;
        this->getRayCoordinates()[coordinateIndex].y = rayCoordinates.y;
        coordinateIndex += 1;
    }
}

/**
 * The ray contructor.
 * @param other
 */
RayCaster::ARay::ARay(RayCaster::ARay const &other)
{
    this->setRayDistance(other.getRayDistance());
    this->setRayCoordinates(other.getRayCoordinates());
    this->setRayTextureCoordinates(other.getRayTextureCoordinates());
    this->setIncrementalSteps(other.getIncrementalSteps());
    this->setRayDisplayType(other.getRayDisplayType());
    this->setRayColor(other.getRayColor());
    this->setRayTexture(other.getRayTexture());
}

/**
 * The ray destructor.
 */
RayCaster::ARay::~ARay()
{
    delete this->getRayCoordinates();
    delete this->getRayTextureCoordinates();
}

/**
 * The ray equal operator.
 * @param other
 * @return
 */
RayCaster::ARay &RayCaster::ARay::operator=(RayCaster::ARay const &other)
{
    int coordinateIndex = 0;

    if (this != &other)
    {
        this->setRayDistance(other.getRayDistance());
        while (coordinateIndex < RAY_VERTEX_NUMBER)
        {
            this->getRayCoordinates()[coordinateIndex].x = other.getRayCoordinates()[coordinateIndex].x;
            this->getRayCoordinates()[coordinateIndex].y = other.getRayCoordinates()[coordinateIndex].y;
            this->getRayTextureCoordinates()[coordinateIndex].x = other.getRayTextureCoordinates()[coordinateIndex].x;
            this->getRayTextureCoordinates()[coordinateIndex].y = other.getRayTextureCoordinates()[coordinateIndex].y;
            coordinateIndex += 1;
        }
        this->setIncrementalSteps(other.getIncrementalSteps());
        this->setRayDisplayType(other.getRayDisplayType());
        this->setRayColor(other.getRayColor());
        this->setRayTexture(other.getRayTexture());
    }
    return *this;
}

/**
 * Renders the ray.
 * @param renderWindow
 */
void RayCaster::ARay::render(sf::RenderWindow *renderWindow) const
{
    sf::VertexArray verticalRayShape(sf::LineStrip, RAY_VERTEX_NUMBER);
    sf::Vector2i const *rayCoordinates = this->getRayCoordinates();
    sf::Color const &rayColor = this->getRayColor();
    sf::Vector2f const *rayTextureCoordinates = this->getRayTextureCoordinates();
    int vertexIndex = 0;

    while (vertexIndex < RAY_VERTEX_NUMBER)
    {
        verticalRayShape[vertexIndex].position.x = rayCoordinates[vertexIndex].x;
        verticalRayShape[vertexIndex].position.y = rayCoordinates[vertexIndex].y;
        verticalRayShape[vertexIndex].color = rayColor;
        verticalRayShape[vertexIndex].texCoords.x = rayTextureCoordinates[vertexIndex].x;
        verticalRayShape[vertexIndex].texCoords.y = rayTextureCoordinates[vertexIndex].y;
        vertexIndex += 1;
    }
    if (verticalRayShape[0].position.x == verticalRayShape[RAY_VERTEX_NUMBER - 1].position.x)
        verticalRayShape[RAY_VERTEX_NUMBER - 1].position.x += 1;
    if (verticalRayShape[0].position.y == verticalRayShape[RAY_VERTEX_NUMBER - 1].position.y)
        verticalRayShape[RAY_VERTEX_NUMBER - 1].position.y += 1;
    if (this->getRayTexture() == nullptr || this->getRayDisplayType() == Display::DisplayType::DISPLAY_VANILLA)
        renderWindow->draw(verticalRayShape);
    else
        renderWindow->draw(verticalRayShape, this->getRayTexture());
}

/**
 * The getter for the ray distance.
 * @return
 */
long RayCaster::ARay::getRayDistance() const
{
    return this->_rayDistance;
}

/**
 * The setter for the ray distance.
 * @param rayDistance
 */
void RayCaster::ARay::setRayDistance(long rayDistance)
{
    this->_rayDistance = rayDistance;
}

/**
 * The getter for the ray coordinates.
 * @return
 */
sf::Vector2i *RayCaster::ARay::getRayCoordinates() const
{
    return this->_rayCoordinates;
}

/**
 * The setter for the ray coordinates.
 * @param rayCoordinates
 */
void RayCaster::ARay::setRayCoordinates(sf::Vector2i *rayCoordinates)
{
    this->_rayCoordinates = rayCoordinates;
}

/**
 * The getter for the ray texture coordinates.
 * @return
 */
sf::Vector2f *RayCaster::ARay::getRayTextureCoordinates() const
{
    return this->_rayTextureCoordinates;
}

/**
 * The setter for the ray texture coordinates.
 * @param rayTextureCoordinates
 */
void RayCaster::ARay::setRayTextureCoordinates(sf::Vector2f *rayTextureCoordinates)
{
    this->_rayTextureCoordinates = rayTextureCoordinates;
}

/**
 * The getter for the incremental steps.
 * @return
 */
sf::Vector2i const &RayCaster::ARay::getIncrementalSteps() const
{
    return this->_incrementalSteps;
}

/**
 * The setter for the incremental steps.
 * @param incrementalSteps
 */
void RayCaster::ARay::setIncrementalSteps(sf::Vector2i const &incrementalSteps)
{
    this->_incrementalSteps = incrementalSteps;
}

/**
 * The getter for the ray display type.
 * @return
 */
Display::DisplayType RayCaster::ARay::getRayDisplayType() const
{
    return this->_rayDisplayType;
}

/**
 * The setter for the ray display type.
 * @param rayDisplayType
 */
void RayCaster::ARay::setRayDisplayType(Display::DisplayType rayDisplayType)
{
    this->_rayDisplayType = rayDisplayType;
}

/**
 * The getter for the ray color.
 * @return
 */
sf::Color const &RayCaster::ARay::getRayColor() const
{
    return this->_rayColor;
}

/**
 * The setter for the ray color.
 * @param rayColor
 */
void RayCaster::ARay::setRayColor(const sf::Color &rayColor)
{
    this->_rayColor = rayColor;
}

/**
 * The getter for the ray texture.
 * @return
 */
sf::Texture *RayCaster::ARay::getRayTexture() const
{
    return this->_rayTexture;
}

/**
 * The setter for the ray texture.
 * @param rayTexture
 */
void RayCaster::ARay::setRayTexture(sf::Texture *rayTexture)
{
    this->_rayTexture = rayTexture;
}
