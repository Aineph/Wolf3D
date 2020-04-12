/*
 * Created by Nicolas Fez for Wolf3D.
 * Started on 2020-04-10.
 */

#ifndef WOLF3D_RAYCASTER_HH
#define WOLF3D_RAYCASTER_HH

class RayCaster
{
public:
    RayCaster();

    RayCaster(RayCaster const &);

    virtual ~RayCaster() = default;

    int render(Position const &, std::vector<std::vector<int>> const &, bool);

    void initializeVectors(Position const &);

    void computeDistances(Position const &);

    void cast(std::vector<std::vector<int>> const &, bool);

    Position const &getRayPosition() const;

    void setRayPosition(Position const &);

    sf::Vector2i const &getDeltaDistance() const;

    void setDeltaDistance(sf::Vector2i const &);

    sf::Vector2i const &getSideDistance() const;

    void setSideDistance(sf::Vector2i const &);

    sf::Vector2i const &getSteps() const;

    void setSteps(sf::Vector2i const &);

    int getHitDirection() const;

    void setHitDirection(int);

    int getPreviousWallDistance() const;

    void setPreviousWallDistance(int);

private:
    Position _rayPosition;
    sf::Vector2i _deltaDistance;
    sf::Vector2i _sideDistance;
    sf::Vector2i _steps;
    int _previousWallDistance;
    int _hitDirection;
};


#endif //WOLF3D_RAYCASTER_HH
