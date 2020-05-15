/*
 * Created by Nicolas Fez for Wolf3D.
 * Started on 2020-04-08.
 */

#ifndef WOLF3D_PLAYER_HH
#define WOLF3D_PLAYER_HH

#define PLAYER_DEFAULT_SPEED .05
#define PLAYER_DEFAULT_ROTATION M_PI / 30

class Player
{
public:
    Player();

    Player(Player const &);

    virtual ~Player() = default;

    Player &operator=(Player const &);

    friend std::ostream &operator<<(std::ostream &, Player const &);

    bool moveForward(Level *);

    bool moveBackward(Level *);

    bool rotateLeft();

    bool rotateRight();

    bool rotateUp(sf::Vector2u const &);

    bool rotateDown(sf::Vector2u const &);

    bool moveLeft(Level *);

    bool moveRight(Level *);

    Position const &getPosition() const;

    void setPosition(Position const &);

private:
    Position _position;
};


#endif //WOLF3D_PLAYER_HH
