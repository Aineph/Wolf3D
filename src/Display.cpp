/*
 * Created by Nicolas Fez for Wolf3D.
 * Started on 2020-04-08.
 */

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cmath>
#include <exception>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "IDrawable.hh"
#include "Position.hh"
#include "Level.hh"
#include "Player.hh"
#include "Display.hh"
#include "Minimap.hh"
#include "RayCaster.hh"

Display *Display::_instance = nullptr;

/**
 * The display constructor.
 */
Display::Display()
{
    this->setWindowTitle(DISPLAY_DEFAULT_TITLE);
    this->setWindow(
            new sf::RenderWindow(sf::VideoMode(DISPLAY_DEFAULT_WIDTH, DISPLAY_DEFAULT_HEIGHT), this->getWindowTitle(),
                                 sf::Style::None));
    this->getWindow()->setFramerateLimit(60);
    this->getWindow()->setVerticalSyncEnabled(true);
    this->setDisplayType(DisplayType::DISPLAY_TEXTURED);
    this->setEvents(std::map<sf::Keyboard::Key, bool>());
    this->setTextures(std::map<Level::BlockType, sf::Texture *>());
    this->setEventTimer(sf::Clock());
    if (!this->loadTextures())
        throw std::exception();
}

/**
 * The display destructor.
 */
Display::~Display()
{
    delete this->getWindow();
    for (auto &texture : this->getTextures())
        delete texture.second;
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
 * Loads the wall textures.
 * @return
 */
bool Display::loadTextures()
{
    std::map<Level::BlockType, sf::Texture *> textures = this->getTextures();

    textures[Level::BLOCK_STANDARD_WALL] = new sf::Texture();
    if (!textures[Level::BLOCK_STANDARD_WALL]->loadFromFile(TEXTURE_STANDARD_WALL))
    {
        delete textures[Level::BLOCK_STANDARD_WALL];
        return false;
    }
    textures[Level::BLOCK_EAGLE_WALL] = new sf::Texture();
    if (!textures[Level::BLOCK_EAGLE_WALL]->loadFromFile(TEXTURE_EAGLE_WALL))
    {
        delete textures[Level::BLOCK_EAGLE_WALL];
        return false;
    }
    textures[Level::BLOCK_WOODEN_WALL] = new sf::Texture();
    if (!textures[Level::BLOCK_WOODEN_WALL]->loadFromFile(TEXTURE_WOODEN_WALL))
    {
        delete textures[Level::BLOCK_WOODEN_WALL];
        return false;
    }
    textures[Level::BLOCK_BLUE_WALL] = new sf::Texture();
    if (!textures[Level::BLOCK_BLUE_WALL]->loadFromFile(TEXTURE_BLUE_WALL))
    {
        delete textures[Level::BLOCK_BLUE_WALL];
        return false;
    }
    this->setTextures(textures);
    return true;
}

/**
 * Renders the level content on the screen.
 * @param player
 * @param level
 */
bool Display::render(Player *player, Level *level)
{
    RayCaster::RayCaster rayCaster = RayCaster::RayCaster(this->getWindow(), level);

    this->getWindow()->clear(sf::Color::Black);
    rayCaster.compute(player->getPosition(), level, this->getTextures(), this->getDisplayType());
    this->getWindow()->display();
    return true;
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
        {
            if (event.key.code == sf::Keyboard::T)
            {
                if (this->getDisplayType() == Display::DisplayType::DISPLAY_TEXTURED)
                    this->setDisplayType(Display::DisplayType::DISPLAY_VANILLA);
                else
                    this->setDisplayType(Display::DisplayType::DISPLAY_TEXTURED);
            }
            else if (event.key.code == sf::Keyboard::Escape)
                this->getWindow()->close();
            else
                this->_events[event.key.code] = true;
        }
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
        if (this->_events[sf::Keyboard::A])
            player->moveLeft(level);
        if (this->_events[sf::Keyboard::E])
            player->moveRight(level);
        currentTimer.restart();
        this->setEventTimer(currentTimer);
    }
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
 * The getter for the display type.
 * @return
 */
Display::DisplayType Display::getDisplayType() const
{
    return this->_displayType;
}

/**
 * The setter for the display type.
 * @param displayType
 */
void Display::setDisplayType(Display::DisplayType displayType)
{
    this->_displayType = displayType;
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
 * The getter for the textures.
 * @return
 */
std::map<Level::BlockType, sf::Texture *> const &Display::getTextures() const
{
    return this->_textures;
}

/**
 * The setter for the textures.
 * @param textures
 */
void Display::setTextures(std::map<Level::BlockType, sf::Texture *> const &textures)
{
    this->_textures = textures;
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
