/*
 * Created by Nicolas Fez for Wolf3D.
 * Started on 2020-04-08.
 */

#ifndef WOLF3D_GAME_HH
#define WOLF3D_GAME_HH

#define MICROSECONDS_PER_SECOND 1000000

class Game
{
public:
    Game();

    Game(Game const &);

    virtual ~Game();

    Game &operator=(Game const &);

    friend std::ostream &operator<<(std::ostream &, Game const &);

    bool start();

    bool run();

    Display *getDisplay() const;

    void setDisplay(Display *display);

    Player *getCurrentPlayer() const;

    void setCurrentPlayer(Player *);

    Level *getCurrentLevel() const;

    void setCurrentLevel(Level *);

    sf::Clock const &getGameClock() const;

    void setGameClock(sf::Clock const &);

private:
    Display *_display;
    Player *_currentPlayer;
    Level *_currentLevel;
    sf::Clock _gameClock;
};


#endif //WOLF3D_GAME_HH
