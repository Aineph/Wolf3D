/*
 * Created by Nicolas Fez for Wolf3D.
 * Started on 2020-04-10.
 */

#ifndef WOLF3D_RAYCASTER_HH
#define WOLF3D_RAYCASTER_HH

class RayCaster
{
public:
    RayCaster(sf::RenderWindow *);

    RayCaster(RayCaster const &);

    virtual ~RayCaster() = default;

    void compute(Position const &, Level *, std::map<Level::BlockType, sf::Texture *> const &, Display::DisplayType);

    void initialize(int, Position const &);

    Position const &getRayPosition() const;

    void setRayPosition(Position const &);

    sf::RenderWindow *getWindow() const;

    void setWindow(sf::RenderWindow *);

    sf::Vector2u const &getWindowSize() const;

    void setWindowSize(sf::Vector2u const &);

private:
    Position _rayPosition;
    sf::RenderWindow *_window;
    sf::Vector2u _windowSize;
};

#endif //WOLF3D_RAYCASTER_HH
