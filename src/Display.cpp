/*
 * Created by Nicolas Fez for Wolf3D.
 * Started on 2020-04-08.
 */

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Position.hh"
#include "Level.hh"
#include "Player.hh"
#include "RayCaster.hh"
#include "Display.hh"

Display *Display::_instance = nullptr;

/**
 * The display constructor.
 */
Display::Display() : _window(), _windowTitle()
{
    this->setWindowTitle(DISPLAY_DEFAULT_TITLE);
    this->setWindow(
            new sf::RenderWindow(sf::VideoMode(DISPLAY_DEFAULT_WIDTH, DISPLAY_DEFAULT_HEIGHT), this->getWindowTitle()));
    this->getWindow()->setFramerateLimit(144);
    this->getWindow()->setVerticalSyncEnabled(true);
    this->setEvents(std::map<sf::Keyboard::Key, bool>());
    this->setEventTimer(sf::Clock());
}

/**
 * The display destructor.
 */
Display::~Display()
{
    delete this->getWindow();
}

/**
 * Creates a display instance.
 * @return
 */
Display *Display::getInstance()
{
    if (Display::_instance == nullptr)
        Display::_instance = new Display();
    return Display::_instance;
}

/**
 * Renders the level content on the screen.
 * @param player
 * @param level
 * @return
 */
bool Display::render(Player *player, Level *level)
{
    RayCaster rayCaster;
    Position rayPosition;
    sf::Vector2u windowDimensions = this->getWindow()->getSize();
    int cameraPosition = 0;
    int wallDistance = 0;
    int x = 0;

    this->getWindow()->clear(sf::Color::Black);
    while (x < windowDimensions.x)
    {
        cameraPosition = (((2 * x) * POSITION_UNIT_X) / windowDimensions.x) - POSITION_UNIT_X;
        rayPosition.setPositionX((player->getPosition().getPositionX() / POSITION_UNIT_X) * POSITION_UNIT_X);
        rayPosition.setPositionY((player->getPosition().getPositionY() / POSITION_UNIT_Y) * POSITION_UNIT_Y);
        rayPosition.setDirectionX(player->getPosition().getDirectionX() +
                                  ((player->getPosition().getPlaneX() * cameraPosition) / POSITION_UNIT_X));
        rayPosition.setDirectionY(player->getPosition().getDirectionY() +
                                  ((player->getPosition().getPlaneY() * cameraPosition) / POSITION_UNIT_Y));
        rayCaster.setRayPosition(rayPosition);
        wallDistance = rayCaster.render(player->getPosition(), level);
        this->renderColumn(x, windowDimensions.y, wallDistance);
        x += 1;
    }
    this->getWindow()->display();
    return true;
}

/**
 * Renders a column from the screen.
 * @param x
 * @param windowHeight
 * @param wallHeight
 */
void Display::renderColumn(int x, int windowHeight, int wallDistance)
{
    sf::RectangleShape sky;
    sf::RectangleShape wall;
    sf::RectangleShape floor;
    sf::Color wallColor;
    int wallSize = 0;
    float wallPosition;

    if (wallDistance == 0)
        wallSize = windowHeight;
    else
        wallSize = (windowHeight * POSITION_UNIT_Y) / wallDistance;
    wallPosition = (static_cast<float>(windowHeight) / 2) - (static_cast<float>(wallSize) / 2);
    sky = sf::RectangleShape(sf::Vector2f(1, wallPosition));
    sky.setFillColor(sf::Color(0, 0, 128));
    sky.setPosition(x, 0);
    wall = sf::RectangleShape(sf::Vector2f(1, wallSize));
    wallColor.r = (std::min(windowHeight, wallSize) * 255) / windowHeight;
    wallColor.g = (std::min(windowHeight, wallSize) * 255) / windowHeight;
    wallColor.b = (std::min(windowHeight, wallSize) * 255) / windowHeight;
    wall.setFillColor(wallColor);
    wall.setPosition(x, wallPosition);
    floor = sf::RectangleShape(sf::Vector2f(1, wallPosition));
    floor.setFillColor(sf::Color(0, 128, 0));
    floor.setPosition(x, wallPosition + wallSize);
    this->getWindow()->draw(sky);
    this->getWindow()->draw(wall);
    this->getWindow()->draw(floor);
}

/**
 * Handles the window events.
 * @param player
 * @param levelMap
 * @return
 */
bool Display::handleEvents(Player *player, Level *level)
{
    auto event = sf::Event();
    sf::Clock currentTimer = this->getEventTimer();

    while (this->getWindow()->pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed)
            this->_events[event.key.code] = true;
        else if (event.type == sf::Event::KeyReleased)
            this->_events[event.key.code] = false;
        else if (event.type == sf::Event::Closed)
            this->getWindow()->close();
    }
    if (currentTimer.getElapsedTime().asMicroseconds() >= 10000)
    {
        if (this->_events[sf::Keyboard::Z] || this->_events[sf::Keyboard::Up])
            player->moveForward(level);
        if (this->_events[sf::Keyboard::S] || this->_events[sf::Keyboard::Down])
            player->moveBackward(level);
        if (this->_events[sf::Keyboard::Q] || this->_events[sf::Keyboard::Left])
            player->rotateLeft();
        if (this->_events[sf::Keyboard::D] || this->_events[sf::Keyboard::Right])
            player->rotateRight();
        currentTimer.restart();
        this->setEventTimer(currentTimer);
    }
    if (this->_events[sf::Keyboard::Escape])
        this->getWindow()->close();
    return true;
}

/**
 * Checks if the display is still running.
 * @return
 */
bool Display::isRunning()
{
    return this->getWindow()->isOpen();
}

/**
 * The getter for the window.
 * @return
 */
sf::RenderWindow *Display::getWindow() const
{
    return this->_window;
}

/**
 * The setter for the window.
 * @param window
 */
void Display::setWindow(sf::RenderWindow *window)
{
    this->_window = window;
}

/**
 * The getter for the window title.
 * @return
 */
std::string const &Display::getWindowTitle() const
{
    return this->_windowTitle;
}

/**
 * The setter for the window title.
 * @param windowTitle
 */
void Display::setWindowTitle(std::string const &windowTitle)
{
    this->_windowTitle = windowTitle;
}

/**
 * The getter for the events.
 * @return
 */
std::map<sf::Keyboard::Key, bool> const &Display::getEvents() const
{
    return this->_events;
}

/**
 * The setter for the events.
 * @param events
 */
void Display::setEvents(const std::map<sf::Keyboard::Key, bool> &events)
{
    this->_events = events;
}

/**
 * The getter for the event timer.
 * @return
 */
sf::Clock const &Display::getEventTimer() const
{
    return this->_eventTimer;
}

/**
 * The setter for the event timer.
 * @param eventTimer
 */
void Display::setEventTimer(sf::Clock const &eventTimer)
{
    this->_eventTimer = eventTimer;
}