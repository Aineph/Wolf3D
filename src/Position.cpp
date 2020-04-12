/*
 * Created by Nicolas Fez for Wolf3D.
 * Started on 2020-04-08.
 */

#include <iostream>
#include "Position.hh"

/**
 * The position constructor.
 */
Position::Position()
{
    this->setPositionX(POSITION_DEFAULT_X);
    this->setPositionY(POSITION_DEFAULT_Y);
    this->setDirectionX(POSITION_DEFAULT_DIRECTION_X);
    this->setDirectionY(POSITION_DEFAULT_DIRECTION_Y);
    this->setPlaneX(POSITION_DEFAULT_PLANE_X);
    this->setPlaneY(POSITION_DEFAULT_PLANE_Y);
}

/**
 * The position constructor.
 * @param other
 */
Position::Position(Position const &other)
{
    this->setPositionX(other.getPositionX());
    this->setPositionY(other.getPositionY());
    this->setDirectionX(other.getDirectionX());
    this->setDirectionY(other.getDirectionY());
    this->setPlaneX(other.getPlaneX());
    this->setPlaneY(other.getPlaneY());
}

/**
 * The position equal operator.
 * @param other
 * @return
 */
Position &Position::operator=(Position const &other)
{
    if (this != &other)
    {
        this->setPositionX(other.getPositionX());
        this->setPositionY(other.getPositionY());
        this->setDirectionX(other.getDirectionX());
        this->setDirectionY(other.getDirectionY());
        this->setPlaneX(other.getPlaneX());
        this->setPlaneY(other.getPlaneY());
    }
    return *this;
}

/**
 * The position left shift operator.
 * @param os
 * @param position
 * @return
 */
std::ostream &operator<<(std::ostream &os, Position const &position)
{
    os << std::endl << "------------------------------" << std::endl;
    os << "This is the object's position." << std::endl;
    os << "Position X: " << position.getPositionX() << std::endl;
    os << "Position Y: " << position.getPositionY() << std::endl;
    os << "Direction X: " << position.getDirectionX() << std::endl;
    os << "Direction Y: " << position.getDirectionY() << std::endl;
    os << "Plane X: " << position.getPlaneX() << std::endl;
    os << "Plane Y: " << position.getPlaneY() << std::endl;
    os << "------------------------------" << std::endl;
    return os;
}

/**
 * The getter for the position x.
 * @return
 */
long Position::getPositionX() const
{
    return this->_positionX;
}

/**
 * The setter for the position x.
 * @return
 */
void Position::setPositionX(long positionX)
{
    this->_positionX = positionX;
}

/**
 * The getter for the position y.
 * @return
 */
long Position::getPositionY() const
{
    return this->_positionY;
}

/**
 * The setter for the position y.
 * @return
 */
void Position::setPositionY(long positionY)
{
    this->_positionY = positionY;
}

/**
 * The getter for the direction x.
 * @return
 */
long Position::getDirectionX() const
{
    return this->_directionX;
}

/**
 * The setter for the direction x.
 * @return
 */
void Position::setDirectionX(long directionX)
{
    this->_directionX = directionX;
}

/**
 * The getter for the direction y.
 * @return
 */
long Position::getDirectionY() const
{
    return this->_directionY;
}

/**
 * The setter for the direction y.
 * @return
 */
void Position::setDirectionY(long directionY)
{
    this->_directionY = directionY;
}

/**
 * The getter for the plane x.
 * @return
 */
long Position::getPlaneX() const
{
    return this->_planeX;
}

/**
 * The setter for the plane x.
 * @return
 */
void Position::setPlaneX(long planeX)
{
    this->_planeX = planeX;
}

/**
 * The getter for the plane y.
 * @return
 */
long Position::getPlaneY() const
{
    return this->_planeY;
}

/**
 * The setter for the plane y.
 * @return
 */
void Position::setPlaneY(long planeY)
{
    this->_planeY = planeY;
}
