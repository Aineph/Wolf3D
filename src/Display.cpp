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
#include "Position.hh"
#include "RayCaster.hh"
#include "Level.hh"
#include "Player.hh"
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
    this->getWindow()->setFramerateLimit(60);
    this->setEvents(std::map<sf::Keyboard::Key, bool>());
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
    int wallHeight = 0;
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
        wallHeight = rayCaster.render(player->getPosition(), level->getLevelMap());
        this->renderColumn(x, windowDimensions.y, wallHeight);
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
void Display::renderColumn(int x, int windowHeight, int wallHeight)
{
    sf::RectangleShape line;
    int wallSize = 0;

    if (wallHeight == 0)
        wallSize = windowHeight;
    else
        wallSize = (windowHeight * POSITION_UNIT_Y) / wallHeight;
    line = sf::RectangleShape(sf::Vector2f(1, wallSize));
    line.setPosition(x, (static_cast<float>(windowHeight) / 2) - (static_cast<float>(wallSize) / 2));
    this->getWindow()->draw(line);
}

/**
 * Handles the window events.
 * @param player
 * @param levelMap
 * @return
 */
bool Display::handleEvents(Player *player, std::vector<std::vector<int>> const &levelMap)
{
    auto event = sf::Event();

    while (this->getWindow()->pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed)
            this->_events[event.key.code] = true;
        else if (event.type == sf::Event::KeyReleased)
            this->_events[event.key.code] = false;
        else if (event.type == sf::Event::Closed)
            this->getWindow()->close();
    }
    if (this->_events[sf::Keyboard::Z] || this->_events[sf::Keyboard::Up])
        player->moveForward(levelMap);
    if (this->_events[sf::Keyboard::S] || this->_events[sf::Keyboard::Down])
        player->moveBackward(levelMap);
    if (this->_events[sf::Keyboard::Q] || this->_events[sf::Keyboard::Left])
        player->rotateLeft();
    if (this->_events[sf::Keyboard::D] || this->_events[sf::Keyboard::Right])
        player->rotateRight();
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