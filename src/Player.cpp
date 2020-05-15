/*
 * Created by Nicolas Fez for Wolf3D.
 * Started on 2020-04-08.
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/System.hpp>
#include "Position.hh"
#include "Level.hh"
#include "Player.hh"

/**
 * The player constructor.
 */
Player::Player()
{
    this->setPosition(Position());
}

/**
 * The player constructor.
 * @param other
 */
Player::Player(Player const &other)
{
    this->setPosition(other.getPosition());
}

/**
 * The player equal operator.
 * @param other
 * @return
 */
Player &Player::operator=(Player const &other)
{
    if (this != &other)
        this->setPosition(other.getPosition());
    return *this;
}

/**
 * The player left shift operator.
 * @param os
 * @param player
 * @return
 */
std::ostream &operator<<(std::ostream &os, Player const &player)
{
    os << std::endl << "----------------------------------------" << std::endl;
    os << "This is the state of the current player." << std::endl;
    os << player.getPosition() << std::endl;
    os << "----------------------------------------" << std::endl;
    return os;
}

/**
 * Moves the player forward.
 * @param level
 * @return
 */
bool Player::moveForward(Level *level)
{
    Position currentPosition = this->getPosition();
    long newPositionX = 0;
    long newPositionY = 0;
    long currentPositionX = 0;
    long currentPositionY = 0;
    long positionX = 0;
    long positionY = 0;

    currentPositionX = currentPosition.getPositionX() / POSITION_UNIT_X;
    currentPositionY = currentPosition.getPositionY() / POSITION_UNIT_Y;
    newPositionX = static_cast<long>(currentPosition.getPositionX() +
                                     (currentPosition.getDirectionX() * PLAYER_DEFAULT_SPEED));
    newPositionY = static_cast<long>(currentPosition.getPositionY() +
                                     (currentPosition.getDirectionY() * PLAYER_DEFAULT_SPEED));
    positionX = newPositionX / POSITION_UNIT_X;
    positionY = newPositionY / POSITION_UNIT_Y;
    if (positionX < level->getLevelWidth() && positionX >= 0 && positionY < level->getLevelHeight() && positionY >= 0 &&
        !Level::isLevelWall(level->getLevelMap()[positionY][positionX]))
    {
        currentPosition.setPositionX(newPositionX);
        currentPosition.setPositionY(newPositionY);
    }
    else if (currentPositionX < level->getLevelWidth() && currentPositionX >= 0 &&
             positionY < level->getLevelHeight() && positionY >= 0 &&
             !Level::isLevelWall(level->getLevelMap()[positionY][currentPositionX]))
        currentPosition.setPositionY(newPositionY);
    else if (positionX < level->getLevelWidth() && positionX >= 0 && currentPositionY < level->getLevelHeight() &&
             currentPositionY >= 0 && !Level::isLevelWall(level->getLevelMap()[currentPositionY][positionX]))
        currentPosition.setPositionX(newPositionX);
    this->setPosition(currentPosition);
    return true;
}

/**
 * Moves the player backward.
 * @param level
 * @return
 */
bool Player::moveBackward(Level *level)
{
    Position currentPosition = this->getPosition();
    long newPositionX = 0;
    long newPositionY = 0;
    long currentPositionX = 0;
    long currentPositionY = 0;
    long positionX = 0;
    long positionY = 0;

    currentPositionX = currentPosition.getPositionX() / POSITION_UNIT_X;
    currentPositionY = currentPosition.getPositionY() / POSITION_UNIT_Y;
    newPositionX = static_cast<long>(currentPosition.getPositionX() -
                                     (currentPosition.getDirectionX() * PLAYER_DEFAULT_SPEED));
    newPositionY = static_cast<long>(currentPosition.getPositionY() -
                                     (currentPosition.getDirectionY() * PLAYER_DEFAULT_SPEED));
    positionX = newPositionX / POSITION_UNIT_X;
    positionY = newPositionY / POSITION_UNIT_Y;
    if (positionX < level->getLevelWidth() && positionX >= 0 && positionY < level->getLevelHeight() && positionY >= 0 &&
        !Level::isLevelWall(level->getLevelMap()[positionY][positionX]))
    {
        currentPosition.setPositionX(newPositionX);
        currentPosition.setPositionY(newPositionY);
    }
    else if (currentPositionX < level->getLevelWidth() && currentPositionX >= 0 &&
             positionY < level->getLevelHeight() && positionY >= 0 &&
             !Level::isLevelWall(level->getLevelMap()[positionY][currentPositionX]))
        currentPosition.setPositionY(newPositionY);
    else if (positionX < level->getLevelWidth() && positionX >= 0 && currentPositionY < level->getLevelHeight() &&
             currentPositionY >= 0 && !Level::isLevelWall(level->getLevelMap()[currentPositionY][positionX]))
        currentPosition.setPositionX(newPositionX);
    this->setPosition(currentPosition);
    return true;
}

/**
 * Rotates the player to the left.
 * @return
 */
bool Player::rotateLeft()
{
    double rotationCos = std::cos(-PLAYER_DEFAULT_ROTATION);
    double rotationSin = std::sin(-PLAYER_DEFAULT_ROTATION);
    Position currentPosition = this->getPosition();
    double directionAngle = 0;

    currentPosition.setDirectionX(static_cast<long>((currentPosition.getDirectionX() * rotationCos) -
                                                    (currentPosition.getDirectionY() * rotationSin)));
    currentPosition.setDirectionY(static_cast<long>((this->getPosition().getDirectionX() * rotationSin) +
                                                    (currentPosition.getDirectionY() * rotationCos)));
    currentPosition.setPlaneX(
            (currentPosition.getPlaneX() * rotationCos) - (currentPosition.getPlaneY() * rotationSin));
    currentPosition.setPlaneY(
            (this->getPosition().getPlaneX() * rotationSin) + (currentPosition.getPlaneY() * rotationCos));
    directionAngle = std::round(
            (std::atan2(currentPosition.getDirectionY(), currentPosition.getDirectionX()) * 180) / M_PI);
    currentPosition.setDirectionX(static_cast<long>(cos((directionAngle * M_PI) / 180) * POSITION_UNIT_X));
    currentPosition.setDirectionY(static_cast<long>(sin((directionAngle * M_PI) / 180) * POSITION_UNIT_X));
    this->setPosition(currentPosition);
    return true;
}

/**
 * Rotates the player to the right.
 * @return
 */
bool Player::rotateRight()
{
    Position currentPosition = this->getPosition();
    double rotationCos = std::cos(PLAYER_DEFAULT_ROTATION);
    double rotationSin = std::sin(PLAYER_DEFAULT_ROTATION);
    double directionAngle = 0;

    currentPosition.setDirectionX(static_cast<long>((currentPosition.getDirectionX() * rotationCos) -
                                                    (currentPosition.getDirectionY() * rotationSin)));
    currentPosition.setDirectionY(static_cast<long>((this->getPosition().getDirectionX() * rotationSin) +
                                                    (currentPosition.getDirectionY() * rotationCos)));
    currentPosition.setPlaneX(
            (currentPosition.getPlaneX() * rotationCos) - (currentPosition.getPlaneY() * rotationSin));
    currentPosition.setPlaneY(
            (this->getPosition().getPlaneX() * rotationSin) + (currentPosition.getPlaneY() * rotationCos));
    directionAngle = std::round(
            (std::atan2(currentPosition.getDirectionY(), currentPosition.getDirectionX()) * 180) / M_PI);
    currentPosition.setDirectionX(static_cast<long>(cos((directionAngle * M_PI) / 180) * POSITION_UNIT_X));
    currentPosition.setDirectionY(static_cast<long>(sin((directionAngle * M_PI) / 180) * POSITION_UNIT_X));
    this->setPosition(currentPosition);
    return true;
}

/**
 * Rotates the player to the top.
 * @return
 */
bool Player::rotateUp(sf::Vector2u const &windowDimensions)
{
    Position currentPosition = this->getPosition();

    currentPosition.setPitch(currentPosition.getPitch() + (windowDimensions.y / 10));
    if (currentPosition.getPitch() < static_cast<int>(windowDimensions.y))
        this->setPosition(currentPosition);
    return true;
}

/**
 * Rotates the player to the bottom.
 * @return
 */
bool Player::rotateDown(sf::Vector2u const &windowDimensions)
{
    Position currentPosition = this->getPosition();

    currentPosition.setPitch(currentPosition.getPitch() - (windowDimensions.y / 10));
    if (currentPosition.getPitch() > -static_cast<int>(windowDimensions.y))
        this->setPosition(currentPosition);
    return true;
}

/**
 * Moves the player to the left.
 * @param level
 * @return
 */
bool Player::moveLeft(Level *level)
{
    Position currentPosition = this->getPosition();
    long newPositionX = 0;
    long newPositionY = 0;
    long currentPositionX = 0;
    long currentPositionY = 0;
    long positionX = 0;
    long positionY = 0;

    currentPositionX = currentPosition.getPositionX() / POSITION_UNIT_X;
    currentPositionY = currentPosition.getPositionY() / POSITION_UNIT_Y;
    newPositionX = static_cast<long>(currentPosition.getPositionX() +
                                     (currentPosition.getDirectionY() * PLAYER_DEFAULT_SPEED));
    newPositionY = static_cast<long>(currentPosition.getPositionY() -
                                     (currentPosition.getDirectionX() * PLAYER_DEFAULT_SPEED));
    positionX = newPositionX / POSITION_UNIT_X;
    positionY = newPositionY / POSITION_UNIT_Y;
    if (positionX < level->getLevelWidth() && positionX >= 0 && positionY < level->getLevelHeight() && positionY >= 0 &&
        !Level::isLevelWall(level->getLevelMap()[positionY][positionX]))
    {
        currentPosition.setPositionX(newPositionX);
        currentPosition.setPositionY(newPositionY);
    }
    else if (currentPositionX < level->getLevelWidth() && currentPositionX >= 0 &&
             positionY < level->getLevelHeight() && positionY >= 0 &&
             !Level::isLevelWall(level->getLevelMap()[positionY][currentPositionX]))
        currentPosition.setPositionY(newPositionY);
    else if (positionX < level->getLevelWidth() && positionX >= 0 && currentPositionY < level->getLevelHeight() &&
             currentPositionY >= 0 && !Level::isLevelWall(level->getLevelMap()[currentPositionY][positionX]))
        currentPosition.setPositionX(newPositionX);
    this->setPosition(currentPosition);
    return true;
}

/**
 * Moves the player to the right.
 * @param level
 * @return
 */
bool Player::moveRight(Level *level)
{
    Position currentPosition = this->getPosition();
    long newPositionX = 0;
    long newPositionY = 0;
    long currentPositionX = 0;
    long currentPositionY = 0;
    long positionX = 0;
    long positionY = 0;

    currentPositionX = currentPosition.getPositionX() / POSITION_UNIT_X;
    currentPositionY = currentPosition.getPositionY() / POSITION_UNIT_Y;
    newPositionX = static_cast<long>(currentPosition.getPositionX() -
                                     (currentPosition.getDirectionY() * PLAYER_DEFAULT_SPEED));
    newPositionY = static_cast<long>(currentPosition.getPositionY() +
                                     (currentPosition.getDirectionX() * PLAYER_DEFAULT_SPEED));
    positionX = newPositionX / POSITION_UNIT_X;
    positionY = newPositionY / POSITION_UNIT_Y;
    if (positionX < level->getLevelWidth() && positionX >= 0 && positionY < level->getLevelHeight() && positionY >= 0 &&
        !Level::isLevelWall(level->getLevelMap()[positionY][positionX]))
    {
        currentPosition.setPositionX(newPositionX);
        currentPosition.setPositionY(newPositionY);
    }
    else if (currentPositionX < level->getLevelWidth() && currentPositionX >= 0 &&
             positionY < level->getLevelHeight() && positionY >= 0 &&
             !Level::isLevelWall(level->getLevelMap()[positionY][currentPositionX]))
        currentPosition.setPositionY(newPositionY);
    else if (positionX < level->getLevelWidth() && positionX >= 0 && currentPositionY < level->getLevelHeight() &&
             currentPositionY >= 0 && !Level::isLevelWall(level->getLevelMap()[currentPositionY][positionX]))
        currentPosition.setPositionX(newPositionX);
    this->setPosition(currentPosition);
    return true;
}

/**
 * The getter for the position.
 * @return
 */
Position const &Player::getPosition() const
{
    return this->_position;
}

/**
 * The setter for the position.
 * @param positionX
 */
void Player::setPosition(Position const &position)
{
    this->_position = position;
}
