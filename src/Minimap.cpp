/*
 * Created by Nicolas Fez for Wolf3D.
 * Started on 2020-04-22.
 */

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "IDrawable.hh"
#include "Position.hh"
#include "Level.hh"
#include "Player.hh"
#include "Display.hh"
#include "Minimap.hh"

/**
 * The minimap constructor.
 */
Minimap::Minimap()
{
    this->setLevel(nullptr);
    this->setBlockSize(0);
    this->setMapPosition(sf::Vector2u());
    this->setMapDimensions(sf::Vector2u());
    this->setPlayerPosition(Position());
}

/**
 * The minimap constructor.
 * @param level
 * @param windowDimensions
 */
Minimap::Minimap(Level *level, sf::Vector2u const &windowDimensions)
{
    int minimapSize = std::min(static_cast<int>(windowDimensions.x * MINIMAP_DEFAULT_PROPORTION),
                               static_cast<int>(windowDimensions.y * MINIMAP_DEFAULT_PROPORTION));
    int levelSize = std::max(level->getLevelWidth(), level->getLevelHeight());
    int blockSize = minimapSize / levelSize;
    int mapWidth = level->getLevelWidth() * blockSize;
    int mapHeight = level->getLevelHeight() * blockSize;

    this->setLevel(level);
    this->setBlockSize(blockSize);
    this->setMapPosition(sf::Vector2u(windowDimensions.x - mapWidth, windowDimensions.y - mapHeight));
    this->setMapDimensions(sf::Vector2u(mapWidth, mapHeight));
    this->setPlayerPosition(Position());
}

/**
 * The minimap constructor.
 * @param other
 */
Minimap::Minimap(Minimap const &other)
{
    this->setLevel(other.getLevel());
    this->setBlockSize(other.getBlockSize());
    this->setMapPosition(other.getMapPosition());
    this->setMapDimensions(other.getMapDimensions());
    this->setPlayerPosition(other.getPlayerPosition());
}

/**
 * The minimap equal operator.
 * @param other
 * @return
 */
Minimap &Minimap::operator=(Minimap const &other)
{
    if (this != &other)
    {
        this->setLevel(other.getLevel());
        this->setBlockSize(other.getBlockSize());
        this->setMapPosition(other.getMapPosition());
        this->setMapDimensions(other.getMapDimensions());
        this->setPlayerPosition(other.getPlayerPosition());
    }
    return *this;
}

/**
 * Renders the minimap.
 * @param renderWindow
 */
void Minimap::render(sf::RenderWindow *renderWindow) const
{
    std::vector<std::vector<int>> const &currentLevelMap = this->getLevel()->getLevelMap();
    sf::RectangleShape wallShape(sf::Vector2f(this->getBlockSize(), this->getBlockSize()));
    sf::CircleShape playerShape(MINIMAP_DEFAULT_PLAYER_SIZE, MINIMAP_DEFAULT_PLAYER_SHAPE);
    Position const &playerPosition = this->getPlayerPosition();
    int positionX;
    int positionY;

    positionY = this->getMapPosition().y;
    for (auto &row : currentLevelMap)
    {
        positionX = this->getMapPosition().x;
        for (auto &column : row)
        {
            wallShape.setPosition(positionX, positionY);
            if (Level::isLevelWall(column))
                wallShape.setFillColor(sf::Color::Black);
            else
                wallShape.setFillColor(sf::Color::White);
            renderWindow->draw(wallShape);
            positionX += this->getBlockSize();
        }
        positionY += this->getBlockSize();
    }
    playerShape.setPosition(this->getMapPosition().x +
                            ((static_cast<double>(playerPosition.getPositionX()) / POSITION_UNIT_X) *
                             this->getBlockSize()), this->getMapPosition().y +
                                                    ((static_cast<double>(playerPosition.getPositionY()) /
                                                      POSITION_UNIT_Y) * this->getBlockSize()));
    playerShape.setOrigin(MINIMAP_DEFAULT_PLAYER_SIZE, MINIMAP_DEFAULT_PLAYER_SIZE);
    playerShape.rotate((std::atan2(playerPosition.getDirectionX(), -playerPosition.getDirectionY()) * 180) / M_PI);
    playerShape.setScale(1, 1.5);
    playerShape.setFillColor(sf::Color::Red);
    renderWindow->draw(playerShape);
}

/**
 * The getter for the level.
 * @return
 */
Level *Minimap::getLevel() const
{
    return this->_level;
}

/**
 * The setter for the level.
 * @param level
 */
void Minimap::setLevel(Level *level)
{
    this->_level = level;
}

/**
 * The getter for the block size.
 * @return
 */
int Minimap::getBlockSize() const
{
    return this->_blockSize;
}

/**
 * The setter for the block size.
 * @param blockSize
 */
void Minimap::setBlockSize(int blockSize)
{
    this->_blockSize = blockSize;
}

/**
 * The getter for the map position.
 * @return
 */
sf::Vector2u const &Minimap::getMapPosition() const
{
    return this->_mapPosition;
}

/**
 * The setter for the map position.
 * @param mapPosition
 */
void Minimap::setMapPosition(sf::Vector2u const &mapPosition)
{
    this->_mapPosition = mapPosition;
}

/**
 * The getter for the map dimensions.
 * @return
 */
sf::Vector2u const &Minimap::getMapDimensions() const
{
    return this->_mapDimensions;
}

/**
 * The setter for the map dimensions.
 * @param mapDimensions
 */
void Minimap::setMapDimensions(sf::Vector2u const &mapDimensions)
{
    this->_mapDimensions = mapDimensions;
}

/**
 * The getter for the player position.
 * @return
 */
Position const &Minimap::getPlayerPosition() const
{
    return this->_playerPosition;
}

/**
 * The setter for the player position.
 * @param playerPosition
 */
void Minimap::setPlayerPosition(Position const &playerPosition)
{
    this->_playerPosition = playerPosition;
}
