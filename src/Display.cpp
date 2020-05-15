/*
 * Created by Nicolas Fez for Wolf3D.
 * Started on 2020-04-08.
 */

#include <map>
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
#include "Engine.hh"

Display *Display::_instance = nullptr;

/**
 * The display constructor.
 */
Display::Display()
{
    this->setWindowTitle(DISPLAY_DEFAULT_TITLE);
    this->setWindow(
            new sf::RenderWindow(sf::VideoMode(DISPLAY_DEFAULT_WIDTH, DISPLAY_DEFAULT_HEIGHT, DISPLAY_DEFAULT_BPP),
                                 this->getWindowTitle(), sf::Style::None));
    this->getWindow()->setFramerateLimit(60);
    this->getWindow()->setVerticalSyncEnabled(true);
    this->getWindow()->setMouseCursorVisible(false);
  //  sf::Mouse::setPosition(sf::Vector2i(DISPLAY_DEFAULT_WIDTH / 2, DISPLAY_DEFAULT_HEIGHT / 2), *this->getWindow());
    this->setDisplayType(DisplayType::DISPLAY_TEXTURED);
    this->setKeyEvents(std::map<sf::Keyboard::Key, bool>());
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

    textures[Level::BLOCK_BARREL] = new sf::Texture();
    if (!textures[Level::BLOCK_BARREL]->loadFromFile(TEXTURE_BARREL))
    {
        delete textures[Level::BLOCK_BARREL];
        return false;
    }
    textures[Level::BLOCK_BLUE_WALL] = new sf::Texture();
    if (!textures[Level::BLOCK_BLUE_WALL]->loadFromFile(TEXTURE_BLUE_WALL))
    {
        delete textures[Level::BLOCK_BLUE_WALL];
        return false;
    }
    textures[Level::BLOCK_COLOR_WALL] = new sf::Texture();
    if (!textures[Level::BLOCK_COLOR_WALL]->loadFromFile(TEXTURE_COLOR_WALL))
    {
        delete textures[Level::BLOCK_COLOR_WALL];
        return false;
    }
    textures[Level::BLOCK_EAGLE_WALL] = new sf::Texture();
    if (!textures[Level::BLOCK_EAGLE_WALL]->loadFromFile(TEXTURE_EAGLE_WALL))
    {
        delete textures[Level::BLOCK_EAGLE_WALL];
        return false;
    }
    textures[Level::BLOCK_GREEN_LIGHT] = new sf::Texture();
    if (!textures[Level::BLOCK_GREEN_LIGHT]->loadFromFile(TEXTURE_GREEN_LIGHT))
    {
        delete textures[Level::BLOCK_GREEN_LIGHT];
        return false;
    }
    textures[Level::BLOCK_GREY_WALL] = new sf::Texture();
    if (!textures[Level::BLOCK_GREY_WALL]->loadFromFile(TEXTURE_GREY_WALL))
    {
        delete textures[Level::BLOCK_GREY_WALL];
        return false;
    }
    textures[Level::BLOCK_MOSSY_WALL] = new sf::Texture();
    if (!textures[Level::BLOCK_MOSSY_WALL]->loadFromFile(TEXTURE_MOSSY_WALL))
    {
        delete textures[Level::BLOCK_MOSSY_WALL];
        return false;
    }
    textures[Level::BLOCK_PILLAR] = new sf::Texture();
    if (!textures[Level::BLOCK_PILLAR]->loadFromFile(TEXTURE_PILLAR))
    {
        delete textures[Level::BLOCK_PILLAR];
        return false;
    }
    textures[Level::BLOCK_PURPLE_WALL] = new sf::Texture();
    if (!textures[Level::BLOCK_PURPLE_WALL]->loadFromFile(TEXTURE_PURPLE_WALL))
    {
        delete textures[Level::BLOCK_PURPLE_WALL];
        return false;
    }
    textures[Level::BLOCK_RED_WALL] = new sf::Texture();
    if (!textures[Level::BLOCK_RED_WALL]->loadFromFile(TEXTURE_RED_WALL))
    {
        delete textures[Level::BLOCK_RED_WALL];
        return false;
    }
    textures[Level::BLOCK_WOODEN_WALL] = new sf::Texture();
    if (!textures[Level::BLOCK_WOODEN_WALL]->loadFromFile(TEXTURE_WOODEN_WALL))
    {
        delete textures[Level::BLOCK_WOODEN_WALL];
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
    RayCaster::Engine rayCaster = RayCaster::Engine(this->getWindow(), level);

    this->getWindow()->clear(sf::Color::Black);
    rayCaster.raycast(player->getPosition(), level, this->getTextures(), this->getDisplayType());
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
    sf::Vector2u const &windowDimensions = this->getWindow()->getSize();
//    sf::Vector2i const &currentMouseLocation = sf::Mouse::getPosition(*this->getWindow());
    sf::Clock currentTimer = this->getEventTimer();

    this->fetchEvents();
    if (currentTimer.getElapsedTime().asMicroseconds() >= 10000)
    {
        if (this->_keyEvents[sf::Keyboard::Z])
            player->moveForward(level);
        if (this->_keyEvents[sf::Keyboard::S])
            player->moveBackward(level);
        if (this->_keyEvents[sf::Keyboard::Q])
            player->moveLeft(level);
        if (this->_keyEvents[sf::Keyboard::D])
            player->moveRight(level);
        if (/*currentMouseLocation.x < windowDimensions.x / 4 || */this->_keyEvents[sf::Keyboard::Left])
            player->rotateLeft();
        else if (/*urrentMouseLocation.x > 3 * windowDimensions.x / 4 || */this->_keyEvents[sf::Keyboard::Right])
            player->rotateRight();
        if (/*currentMouseLocation.y < windowDimensions.y / 4  || */this->_keyEvents[sf::Keyboard::Up])
            player->rotateUp(this->getWindow()->getSize());
        else if (/*currentMouseLocation.y > 3 * windowDimensions.y / 4 || */this->_keyEvents[sf::Keyboard::Down])
            player->rotateDown(this->getWindow()->getSize());
        //sf::Mouse::setPosition(sf::Vector2i(windowDimensions.x / 2, windowDimensions.y / 2), *this->getWindow());
        currentTimer.restart();
        this->setEventTimer(currentTimer);
    }
    return true;
}

/**
 * Fetches the event from the window.
 * @return
 */
bool Display::fetchEvents()
{
    auto event = sf::Event();

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
                this->_keyEvents[event.key.code] = true;
        }
        else if (event.type == sf::Event::KeyReleased)
            this->_keyEvents[event.key.code] = false;
        else if (event.type == sf::Event::Closed)
            this->getWindow()->close();
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
std::map<sf::Keyboard::Key, bool> const &Display::getKeyEvents() const
{
    return this->_keyEvents;
}

/**
 * The setter for the events.
 * @param events
 */
void Display::setKeyEvents(const std::map<sf::Keyboard::Key, bool> &events)
{
    this->_keyEvents = events;
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
