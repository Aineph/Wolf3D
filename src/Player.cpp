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
 * The player left shift operator.
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
        level->getLevelMap()[positionY][positionX] != Level::BLOCK_STANDARD_WALL)
    {
        currentPosition.setPositionX(newPositionX);
        currentPosition.setPositionY(newPositionY);
    }
    else if (currentPositionX < level->getLevelWidth() && currentPositionX >= 0 &&
             positionY < level->getLevelHeight() && positionY >= 0 &&
             level->getLevelMap()[positionY][currentPositionX] != Level::BLOCK_STANDARD_WALL)
        currentPosition.setPositionY(newPositionY);
    else if (positionX < level->getLevelWidth() && positionX >= 0 && currentPositionY < level->getLevelHeight() &&
             currentPositionY >= 0 && level->getLevelMap()[currentPositionY][positionX] != Level::BLOCK_STANDARD_WALL)
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
        level->getLevelMap()[positionY][positionX] != Level::BLOCK_STANDARD_WALL)
    {
        currentPosition.setPositionX(newPositionX);
        currentPosition.setPositionY(newPositionY);
    }
    else if (currentPositionX < level->getLevelWidth() && currentPositionX >= 0 &&
             positionY < level->getLevelHeight() && positionY >= 0 &&
             level->getLevelMap()[positionY][currentPositionX] != Level::BLOCK_STANDARD_WALL)
        currentPosition.setPositionY(newPositionY);
    else if (positionX < level->getLevelWidth() && positionX >= 0 && currentPositionY < level->getLevelHeight() &&
             currentPositionY >= 0 && level->getLevelMap()[currentPositionY][positionX] != Level::BLOCK_STANDARD_WALL)
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
    Position currentPosition = this->getPosition();

    currentPosition.setDirectionX(static_cast<long>(currentPosition.getDirectionX() * std::cos(-(M_PI / 48)) -
                                                    currentPosition.getDirectionY() * std::sin(-(M_PI / 48))));
    currentPosition.setDirectionY(static_cast<long>(this->getPosition().getDirectionX() * std::sin(-(M_PI / 48)) +
                                                    currentPosition.getDirectionY() * std::cos(-(M_PI / 48))));
    currentPosition.setPlaneX(static_cast<long>(currentPosition.getPlaneX() * std::cos(-(M_PI / 48)) -
                                                currentPosition.getPlaneY() * std::sin(-(M_PI / 48))));
    currentPosition.setPlaneY(static_cast<long>(this->getPosition().getPlaneX() * std::sin(-(M_PI / 48)) +
                                                currentPosition.getPlaneY() * std::cos(-(M_PI / 48))));
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

    currentPosition.setDirectionX(static_cast<long>(currentPosition.getDirectionX() * std::cos(M_PI / 48) -
                                                    currentPosition.getDirectionY() * std::sin(M_PI / 48)));
    currentPosition.setDirectionY(static_cast<long>(this->getPosition().getDirectionX() * std::sin(M_PI / 48) +
                                                    currentPosition.getDirectionY() * std::cos(M_PI / 48)));
    currentPosition.setPlaneX(static_cast<long>(currentPosition.getPlaneX() * std::cos(M_PI / 48) -
                                                currentPosition.getPlaneY() * std::sin(M_PI / 48)));
    currentPosition.setPlaneY(static_cast<long>(this->getPosition().getPlaneX() * std::sin(M_PI / 48) +
                                                currentPosition.getPlaneY() * std::cos(M_PI / 48)));
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
