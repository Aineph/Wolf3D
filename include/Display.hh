/*
 * Created by Nicolas Fez for Wolf3D.
 * Started on 2020-04-08.
 */

#ifndef WOLF3D_DISPLAY_HH
#define WOLF3D_DISPLAY_HH

#define DISPLAY_DEFAULT_TITLE "Wolf3D"
#define DISPLAY_DEFAULT_WIDTH 1920
#define DISPLAY_DEFAULT_HEIGHT 1080

class Display
{
public:
    virtual ~Display();

    Display(Display const &) = delete;

    static Display *getInstance();

    bool render(Player *, Level *, bool = false);

    void renderColumn(int, int, int);

    bool handleEvents(Player *);

    bool isRunning();

    sf::RenderWindow *getWindow() const;

    void setWindow(sf::RenderWindow *);

    std::string const &getWindowTitle() const;

    void setWindowTitle(std::string const &);

private:
    static Display *_instance;
    sf::RenderWindow *_window;
    std::string _windowTitle;

    Display();
};


#endif //WOLF3D_DISPLAY_HH
