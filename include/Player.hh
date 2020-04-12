/*
 * Created by Nicolas Fez for Wolf3D.
 * Started on 2020-04-08.
 */

#ifndef WOLF3D_PLAYER_HH
#define WOLF3D_PLAYER_HH

#define PLAYER_DEFAULT_HEIGHT (172 * POSITION_UNIT_HEIGHT)
#define PLAYER_DEFAULT_VIEWFIELD (60 * ((POSITION_UNIT_X + POSITION_UNIT_Y) / 2))

class Player
{
public:
    Player();

    Player(Player const &);

    virtual ~Player() = default;

    Player &operator=(Player const &);

    friend std::ostream &operator<<(std::ostream &, Player const &);

    bool moveForward(std::vector<std::vector<int>> const &);

    bool moveBackward(std::vector<std::vector<int>> const &);

    bool rotateLeft();

    bool rotateRight();

    Position const &getPosition() const;

    void setPosition(Position const &);

    int getPlayerHeight() const;

    void setPlayerHeight(int);

    int getPlayerViewField() const;

    void setPlayerViewField(int);

private:
    Position _position;

    int _playerHeight;

    int _playerViewField;
};


#endif //WOLF3D_PLAYER_HH
