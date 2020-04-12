/*
 * Created by Nicolas Fez for Wolf3D.
 * Started on 2020-04-08.
 */

#include <iostream>
#include <cmath>
#include "Position.hh"
#include "Player.hh"

/**
 * The player constructor.
 */
Player::Player()
{
    this->setPosition(Position());
    this->setPlayerHeight(PLAYER_DEFAULT_HEIGHT);
    this->setPlayerViewField(PLAYER_DEFAULT_VIEWFIELD);
}

/**
 * The player constructor.
 * @param other
 */
Player::Player(Player const &other)
{
    this->setPosition(other.getPosition());
    this->setPlayerHeight(other.getPlayerHeight());
    this->setPlayerViewField(other.getPlayerViewField());
}

Player &Player::operator=(Player const &other)
{
    if (this != &other)
    {
        this->setPosition(other.getPosition());
        this->setPlayerHeight(other.getPlayerHeight());
        this->setPlayerViewField(other.getPlayerViewField());
    }
    return *this;
}

std::ostream &operator<<(std::ostream &os, Player const &player)
{
    os << std::endl << "----------------------------------------" << std::endl;
    os << "This is the state of the current player." << std::endl;
    os << player.getPosition() << std::endl;
    os << "Player Height: " << player.getPlayerHeight() << std::endl;
    os << "Player View Field: " << player.getPlayerViewField() << std::endl;
    os << "----------------------------------------" << std::endl;
    return os;
}

/**
 * Moves the player forward.
 * @return
 */
bool Player::moveForward()
{
    Position currentPosition = this->getPosition();

    currentPosition.setPositionX(currentPosition.getPositionX() + (currentPosition.getDirectionX() / 10));
    currentPosition.setPositionY(currentPosition.getPositionY() + (currentPosition.getDirectionY() / 10));
    this->setPosition(currentPosition);
    return true;
}

/**
 * Moves the player backward.
 * @return
 */
bool Player::moveBackward()
{
    Position currentPosition = this->getPosition();

    currentPosition.setPositionX(currentPosition.getPositionX() - (currentPosition.getDirectionX() / 10));
    currentPosition.setPositionY(currentPosition.getPositionY() - (currentPosition.getDirectionY() / 10));
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

    currentPosition.setDirectionX((currentPosition.getDirectionX() * std::cos(-(M_PI / 24)) -
                                   currentPosition.getDirectionY() * std::sin(-(M_PI / 24))));
    currentPosition.setDirectionY((this->getPosition().getDirectionX() * std::sin(-(M_PI / 24)) +
                                   currentPosition.getDirectionY() * std::cos(-(M_PI / 24))));
    currentPosition.setPlaneX((currentPosition.getPlaneX() * std::cos(-(M_PI / 24)) -
                               currentPosition.getPlaneY() * std::sin(-(M_PI / 24))));
    currentPosition.setPlaneY((this->getPosition().getPlaneX() * std::sin(-(M_PI / 24)) +
                               currentPosition.getPlaneY() * std::cos(-(M_PI / 24))));
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

    currentPosition.setDirectionX((currentPosition.getDirectionX() * std::cos(M_PI / 24) -
                                   currentPosition.getDirectionY() * std::sin(M_PI / 24)));
    currentPosition.setDirectionY((this->getPosition().getDirectionX() * std::sin(M_PI / 24) +
                                   currentPosition.getDirectionY() * std::cos(M_PI / 24)));
    currentPosition.setPlaneX(
            (currentPosition.getPlaneX() * std::cos(M_PI / 24) - currentPosition.getPlaneY() * std::sin(M_PI / 24)));
    currentPosition.setPlaneY(
            (this->getPosition().getPlaneX() * std::sin(M_PI / 24) + currentPosition.getPlaneY() * std::cos(M_PI / 24)));
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

/**
 * The getter for the player height.
 * @return
 */
int Player::getPlayerHeight() const
{
    return this->_playerHeight;
}

/**
 * The setter for the player height.
 * @param height
 */
void Player::setPlayerHeight(int height)
{
    this->_playerHeight = height;
}

/**
 * The getter for the player view field.
 * @return
 */
int Player::getPlayerViewField() const
{
    return this->_playerViewField;
}

/**
 * The setter for the player view field.
 * @param viewField
 */
void Player::setPlayerViewField(int viewField)
{
    this->_playerViewField = viewField;
}
