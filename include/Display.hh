/*
 * Created by Nicolas Fez for Wolf3D.
 * Started on 2020-04-08.
 */

#ifndef WOLF3D_DISPLAY_HH
#define WOLF3D_DISPLAY_HH

#define DISPLAY_DEFAULT_TITLE "Wolf3D"
#define DISPLAY_DEFAULT_WIDTH 1280
#define DISPLAY_DEFAULT_HEIGHT 720

class Display
{
public:
    virtual ~Display();

    Display(Display const &) = delete;

    static Display *getInstance();

    bool render(Player *, Level *);

    void renderColumn(int, int, int);

    bool handleEvents(Player *, Level *);

    bool isRunning();

    sf::RenderWindow *getWindow() const;

    void setWindow(sf::RenderWindow *);

    std::string const &getWindowTitle() const;

    void setWindowTitle(std::string const &);

    std::map<sf::Keyboard::Key, bool> const &getEvents() const;

    void setEvents(std::map<sf::Keyboard::Key, bool> const &);

    sf::Clock const &getEventTimer() const;

    void setEventTimer(sf::Clock const &);

private:
    static Display *_instance;
    sf::RenderWindow *_window;
    std::string _windowTitle;
    std::map<sf::Keyboard::Key, bool> _events;
    sf::Clock _eventTimer;

    Display();
};


#endif //WOLF3D_DISPLAY_HH
