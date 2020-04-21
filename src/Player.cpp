/*
 * Created by Nicolas Fez for Wolf3D.
 * Started on 2020-04-08.
 */

#include <iostream>
#include <vector>
#include <cmath>
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
    newPositionX = currentPosition.getPositionX() + (currentPosition.getDirectionX() / 20);
    newPositionY = currentPosition.getPositionY() + (currentPosition.getDirectionY() / 20);
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
    newPositionX = currentPosition.getPositionX() - (currentPosition.getDirectionX() / 20);
    newPositionY = currentPosition.getPositionY() - (currentPosition.getDirectionY() / 20);
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
    long rotationCos = static_cast<long>(std::cos(-(M_PI / 48)) * POSITION_UNIT_X * POSITION_UNIT_Y);
    long rotationSin = static_cast<long>(std::sin(-(M_PI / 48)) * POSITION_UNIT_X * POSITION_UNIT_Y);
    Position currentPosition = this->getPosition();

    currentPosition.setDirectionX(
            ((currentPosition.getDirectionX() * rotationCos) - (currentPosition.getDirectionY() * rotationSin)) /
            (POSITION_UNIT_X * POSITION_UNIT_Y));
    currentPosition.setDirectionY(
            ((this->getPosition().getDirectionX() * rotationSin) + (currentPosition.getDirectionY() * rotationCos)) /
            (POSITION_UNIT_X * POSITION_UNIT_Y));
    currentPosition.setPlaneX(
            ((currentPosition.getPlaneX() * rotationCos) - (currentPosition.getPlaneY() * rotationSin)) /
            (POSITION_UNIT_X * POSITION_UNIT_Y));
    currentPosition.setPlaneY(
            ((this->getPosition().getPlaneX() * rotationSin) + (currentPosition.getPlaneY() * rotationCos)) /
            (POSITION_UNIT_X * POSITION_UNIT_Y));
    Player::fixAngles(currentPosition);
    this->setPosition(currentPosition);
    return true;
}

/**
 * Rotates the player to the right.
 * @return
 */
bool Player::rotateRight()
{
    long rotationCos = static_cast<long>(std::cos(M_PI / 48) * POSITION_UNIT_X * POSITION_UNIT_Y);
    long rotationSin = static_cast<long>(std::sin(M_PI / 48) * POSITION_UNIT_X * POSITION_UNIT_Y);
    Position currentPosition = this->getPosition();

    currentPosition.setDirectionX(
            ((currentPosition.getDirectionX() * rotationCos) - (currentPosition.getDirectionY() * rotationSin)) /
            (POSITION_UNIT_X * POSITION_UNIT_Y));
    currentPosition.setDirectionY(
            ((this->getPosition().getDirectionX() * rotationSin) + (currentPosition.getDirectionY() * rotationCos)) /
            (POSITION_UNIT_X * POSITION_UNIT_Y));
    currentPosition.setPlaneX(
            ((currentPosition.getPlaneX() * rotationCos) - (currentPosition.getPlaneY() * rotationSin)) /
            (POSITION_UNIT_X * POSITION_UNIT_Y));
    currentPosition.setPlaneY(
            ((this->getPosition().getPlaneX() * rotationSin) + (currentPosition.getPlaneY() * rotationCos)) /
            (POSITION_UNIT_X * POSITION_UNIT_Y));
    Player::fixAngles(currentPosition);
    this->setPosition(currentPosition);
    return true;
}

void Player::fixAngles(Position &playerPosition)
{
    if (playerPosition.getDirectionX() == 0)
    {
        if (playerPosition.getDirectionY() < 0)
        {
            playerPosition.setDirectionY(-POSITION_UNIT_Y);
            playerPosition.setPlaneX(POSITION_DEFAULT_PLANE_X);
        }
        else if (playerPosition.getDirectionY() > 0)
        {
            playerPosition.setDirectionY(POSITION_UNIT_Y);
            playerPosition.setPlaneX(-POSITION_DEFAULT_PLANE_X);
        }
        playerPosition.setPlaneY(0);
    }
    if (playerPosition.getDirectionY() == 0)
    {
        if (playerPosition.getDirectionX() < 0)
        {
            playerPosition.setDirectionX(-POSITION_UNIT_X);
            playerPosition.setPlaneY(-POSITION_DEFAULT_PLANE_Y);
        }
        else if (playerPosition.getDirectionY() > 0)
        {
            playerPosition.setDirectionX(POSITION_UNIT_X);
            playerPosition.setPlaneY(POSITION_DEFAULT_PLANE_Y);
        }
        playerPosition.setPlaneX(0);
    }
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
