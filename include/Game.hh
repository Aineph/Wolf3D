/*
 * Created by Nicolas Fez for Wolf3D.
 * Started on 2020-04-08.
 */

#ifndef WOLF3D_GAME_HH
#define WOLF3D_GAME_HH


class Game
{
public:
    Game();

    virtual ~Game();

    Game &operator=(Game const &);

    friend std::ostream &operator<<(std::ostream &, Game const &);

    bool start();

    bool run();

    Player *getCurrentPlayer() const;

    void setCurrentPlayer(Player *);

    Level *getCurrentLevel() const;

    void setCurrentLevel(Level *);

    Display *getDisplay() const;

    void setDisplay(Display *display);

private:
    Display *_display;
    Player *_currentPlayer;
    Level *_currentLevel;
};


#endif //WOLF3D_GAME_HH
