/*
 * Created by Nicolas Fez for Wolf3D.
 * Started on 2020-04-08.
 */

#include <string>
#include <fstream>
#include <vector>
#include <exception>
#include "Position.hh"
#include "Level.hh"

/**
 * The level constructor.
 */
Level::Level()
{
    this->setLevelName(LEVEL_DEFAULT_NAME);
    this->setLevelFile(LEVEL_DEFAULT_FILE);
    this->setLevelWidth(0);
    this->setLevelHeight(0);
    this->setLevelMap(std::vector<std::vector<int>>());
}

/**
 * The level constructor.
 * @param other
 */
Level::Level(Level const &other)
{
    this->setLevelName(other.getLevelName());
    this->setLevelFile(other.getLevelFile());
    this->setLevelWidth(other.getLevelWidth());
    this->setLevelHeight(other.getLevelHeight());
    this->setLevelMap(other.getLevelMap());
}

/**
 * The level left shift operator.
 * @param other
 * @return
 */
Level &Level::operator=(Level const &other)
{
    if (this != &other)
    {
        this->setLevelName(other.getLevelName());
        this->setLevelFile(other.getLevelFile());
        this->setLevelMap(other.getLevelMap());
    }
    return *this;
}

/**
 * The level left shift operator.
 * @param os
 * @param level
 * @return
 */
std::ostream &operator<<(std::ostream &os, Level const &level)
{
    os << std::endl << "---------------------------------------" << std::endl;
    os << "This is the state of the current level." << std::endl;
    os << "Level Name: " << level.getLevelName() << std::endl;
    os << "Level File: " << level.getLevelFile() << std::endl;
    os << "Level Width: " << level.getLevelWidth() << std::endl;
    os << "Level Height: " << level.getLevelHeight() << std::endl;
    for (auto &row : level.getLevelMap())
    {
        for (auto &column : row)
        {
            os << column;
        }
        os << std::endl;
    }
    os << "---------------------------------------" << std::endl;
    return os;
}

/**
 * Loads the content of the current level.
 * @return
 */
Position Level::loadLevelMap()
{
    std::ifstream levelFileStream;
    std::string levelFileLine;
    Position startPosition;
    int currentColumn;
    int currentRow;

    levelFileStream.open(this->getLevelFile());
    if (!levelFileStream.is_open())
        throw std::exception();
    currentRow = 0;
    while (std::getline(levelFileStream, levelFileLine))
    {
        std::vector<int> levelMapLine;
        currentColumn = 0;
        for (auto &character : levelFileLine)
        {
            if (character == BlockType::BLOCK_START_UP || character == BlockType::BLOCK_START_RIGHT ||
                character == BlockType::BLOCK_START_DOWN || character == BlockType::BLOCK_START_LEFT)
            {
                startPosition.setPositionX((currentColumn * POSITION_UNIT_X) + (POSITION_UNIT_X / 2));
                startPosition.setPositionY((currentRow * POSITION_UNIT_Y) + (POSITION_UNIT_Y / 2));
                if (character == BLOCK_START_UP)
                {
                    startPosition.setDirectionX(0);
                    startPosition.setDirectionY(-POSITION_UNIT_Y);
                    startPosition.setPlaneY(0);
                }
                else if (character == BLOCK_START_RIGHT)
                {
                    startPosition.setDirectionX(POSITION_UNIT_X);
                    startPosition.setDirectionY(0);
                    startPosition.setPlaneX(0);
                }
                else if (character == BLOCK_START_DOWN)
                {
                    startPosition.setDirectionX(0);
                    startPosition.setDirectionY(POSITION_UNIT_Y);
                    startPosition.setPlaneX(-startPosition.getPlaneX());
                    startPosition.setPlaneY(0);
                }
                else
                {
                    startPosition.setDirectionX(-POSITION_UNIT_X);
                    startPosition.setDirectionY(0);
                    startPosition.setPlaneX(0);
                    startPosition.setPlaneY(-startPosition.getPlaneY());
                }
            }
            levelMapLine.push_back(character);
            currentColumn += 1;
        }
        this->_levelMap.push_back(levelMapLine);
        currentRow += 1;
    }
    this->setLevelWidth(currentColumn);
    this->setLevelHeight(currentRow);
    return startPosition;
}

/**
 * The getter for the level name.
 * @return
 */
std::string const &Level::getLevelName() const
{
    return this->_levelName;
}

/**
 * The setter for the level name.
 * @param levelName
 */
void Level::setLevelName(std::string const &levelName)
{
    this->_levelName = levelName;
}

/**
 * The getter for the level file.
 * @return
 */
std::string const &Level::getLevelFile() const
{
    return this->_levelFile;
}

/**
 * The setter for the level file.
 * @param levelFile
 */
void Level::setLevelFile(std::string const &levelFile)
{
    this->_levelFile = levelFile;
}

/**
 * The getter for the level width.
 * @return
 */
int Level::getLevelWidth() const
{
    return this->_levelWidth;
}

/**
 * The setter for the level width.
 * @param levelWidth
 */
void Level::setLevelWidth(int levelWidth)
{
    this->_levelWidth = levelWidth;
}

/**
 * The getter for the level height.
 * @return
 */
int Level::getLevelHeight() const
{
    return this->_levelHeight;
}

/**
 * The setter for the level height.
 * @param levelHeight
 */
void Level::setLevelHeight(int levelHeight)
{
    this->_levelHeight = levelHeight;
}

/**
 * The getter for the level map.
 * @return
 */
std::vector<std::vector<int>> const &Level::getLevelMap() const
{
    return this->_levelMap;
}

/**
 * The setter for the level map.
 * @param levelMap
 */
void Level::setLevelMap(std::vector<std::vector<int>> const &levelMap)
{
    this->_levelMap = levelMap;
}
