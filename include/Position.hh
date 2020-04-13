/*
 * Created by Nicolas Fez for Wolf3D.
 * Started on 2020-04-08.
 */

#ifndef WOLF3D_POSITION_HH
#define WOLF3D_POSITION_HH

#define POSITION_UNIT_X 10000
#define POSITION_UNIT_Y 10000

#define POSITION_DEFAULT_X (0 + (POSITION_UNIT_X / 2))
#define POSITION_DEFAULT_Y (0 + (POSITION_UNIT_Y / 2))
#define POSITION_DEFAULT_DIRECTION_X 0
#define POSITION_DEFAULT_DIRECTION_Y 0
#define POSITION_DEFAULT_PLANE_X ((66 * POSITION_UNIT_X) / 100)
#define POSITION_DEFAULT_PLANE_Y ((66 * POSITION_UNIT_Y) / 100)

class Position
{
public:
    Position();

    Position(Position const &);

    Position &operator=(Position const &);

    friend std::ostream &operator<<(std::ostream &, Position const &);

    long getPositionX() const;

    void setPositionX(long);

    long getPositionY() const;

    void setPositionY(long);

    long getDirectionX() const;

    void setDirectionX(long);

    long getDirectionY() const;

    void setDirectionY(long);

    long getPlaneX() const;

    void setPlaneX(long);

    long getPlaneY() const;

    void setPlaneY(long);

private:
    long _positionX;
    long _positionY;
    long _directionX;
    long _directionY;
    long _planeX;
    long _planeY;
};


#endif //WOLF3D_POSITION_HH
