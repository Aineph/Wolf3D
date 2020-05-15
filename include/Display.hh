/*
 * Created by Nicolas Fez for Wolf3D.
 * Started on 2020-04-08.
 */

#ifndef WOLF3D_DISPLAY_HH
#define WOLF3D_DISPLAY_HH

#define DISPLAY_DEFAULT_TITLE "Wolf3D"
#define DISPLAY_DEFAULT_WIDTH 800
#define DISPLAY_DEFAULT_HEIGHT 600
#define DISPLAY_DEFAULT_BPP 32

#define TEXTURE_BARREL "../resources/textures/barrel.png"
#define TEXTURE_BLUE_WALL "../resources/textures/bluestone.png"
#define TEXTURE_COLOR_WALL "../resources/textures/colorstone.png"
#define TEXTURE_EAGLE_WALL "../resources/textures/eagle.png"
#define TEXTURE_GREEN_LIGHT "../resources/textures/greenlight.png"
#define TEXTURE_GREY_WALL "../resources/textures/greystone.png"
#define TEXTURE_MOSSY_WALL "../resources/textures/mossy.png"
#define TEXTURE_PILLAR "../resources/textures/pillar.png"
#define TEXTURE_PURPLE_WALL "../resources/textures/purplestone.png"
#define TEXTURE_RED_WALL "../resources/textures/redbrick.png"
#define TEXTURE_WOODEN_WALL "../resources/textures/wood.png"


class Display
{
public:
    enum DisplayType
    {
        DISPLAY_VANILLA = false, DISPLAY_TEXTURED = true
    };

    virtual ~Display();

    Display(Display const &) = delete;

    static Display *getInstance();

    bool render(Player *, Level *);

    bool handleEvents(Player *, Level *);

    bool isRunning();

    sf::RenderWindow *getWindow() const;

    void setWindow(sf::RenderWindow *);

    std::string const &getWindowTitle() const;

    void setWindowTitle(std::string const &);

    DisplayType getDisplayType() const;

    void setDisplayType(DisplayType);

    std::map<sf::Keyboard::Key, bool> const &getKeyEvents() const;

    void setKeyEvents(std::map<sf::Keyboard::Key, bool> const &);

    std::map<Level::BlockType, sf::Texture *> const &getTextures() const;

    void setTextures(std::map<Level::BlockType, sf::Texture *> const &);

    sf::Clock const &getEventTimer() const;

    void setEventTimer(sf::Clock const &);

private:
    Display();

    bool loadTextures();

    bool fetchEvents();

    static Display *_instance;
    sf::RenderWindow *_window;
    std::string _windowTitle;
    DisplayType _displayType;
    std::map<sf::Keyboard::Key, bool> _keyEvents;
    std::map<Level::BlockType, sf::Texture *> _textures;
    sf::Clock _eventTimer;
};


#endif //WOLF3D_DISPLAY_HH
