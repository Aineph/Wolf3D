/*
 * Created by Nicolas Fez for Wolf3D.
 * Started on 2020-04-08.
 */

#ifndef WOLF3D_DISPLAY_HH
#define WOLF3D_DISPLAY_HH

#define DISPLAY_DEFAULT_TITLE "Wolf3D"
#define DISPLAY_DEFAULT_WIDTH 800
#define DISPLAY_DEFAULT_HEIGHT 600

#define DISPLAY_DEFAULT_MAP_RATIO 4
#define DISPLAY_DEFAULT_PLAYER_SIZE 10
#define DISPLAY_TRIANGLE_SHAPE 3

#define TEXTURE_STANDARD_WALL "../resources/textures/redbrick.png"
#define TEXTURE_EAGLE_WALL "../resources/textures/eagle.png"
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

    bool loadTextures();

    bool render(Player *, Level *);

    void renderMap(Player *, Level *);

    bool handleEvents(Player *, Level *);

    bool isRunning();

    sf::RenderWindow *getWindow() const;

    void setWindow(sf::RenderWindow *);

    std::string const &getWindowTitle() const;

    void setWindowTitle(std::string const &);

    DisplayType getDisplayType() const;

    void setDisplayType(DisplayType);

    std::map<sf::Keyboard::Key, bool> const &getEvents() const;

    void setEvents(std::map<sf::Keyboard::Key, bool> const &);

    std::map<Level::BlockType, sf::Texture *> const &getTextures() const;

    void setTextures(std::map<Level::BlockType, sf::Texture *> const &);

    sf::Clock const &getEventTimer() const;

    void setEventTimer(sf::Clock const &);

private:
    static Display *_instance;
    sf::RenderWindow *_window;
    std::string _windowTitle;
    DisplayType _displayType;
    std::map<sf::Keyboard::Key, bool> _events;
    std::map<Level::BlockType, sf::Texture *> _textures;
    sf::Clock _eventTimer;

    Display();
};


#endif //WOLF3D_DISPLAY_HH
