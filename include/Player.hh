/*
 * Created by Nicolas Fez for Wolf3D.
 * Started on 2020-04-08.
 */

#ifndef WOLF3D_PLAYER_HH
#define WOLF3D_PLAYER_HH

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

    void fixAngles(Position &);

    Position const &getPosition() const;

    void setPosition(Position const &);

private:
    Position _position;
};


#endif //WOLF3D_PLAYER_HH
