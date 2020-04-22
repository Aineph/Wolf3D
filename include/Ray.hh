/*
 * Created by Nicolas Fez for Wolf3D.
 * Started on 2020-04-16.
 */

#ifndef WOLF3D_RAY_HH
#define WOLF3D_RAY_HH

class Ray
{
public:
    enum RayHitAxis
    {
        AXIS_X = 0, AXIS_Y = 1
    };

    Ray();

    Ray(Position const &, Position const &, Level *, int);

    Ray(Ray const &);

    virtual ~Ray() = default;

    Ray &operator=(Ray const &);

    void initializeTexture(sf::Texture *);

    void fillScreen(sf::RenderWindow *, int, sf::Vector2u const &, Display::DisplayType);

    void initialize(Position const &);

    void cast(Level *);

    void fetchDistances(Position const &);

    void preComputeWallDimensions(int);

    Position const &getRayPosition() const;

    void setRayPosition(Position const &);

    Position const &getIncrementalPosition() const;

    void setIncrementalPosition(Position const &);

    sf::Vector2i const &getIncrementalSteps() const;

    void setIncrementalSteps(sf::Vector2i const &);

    RayHitAxis getHitAxis() const;

    void setHitAxis(RayHitAxis);

    Level::BlockType getHitBlockType() const;

    void setHitBlockType(Level::BlockType);

    int getHitPosition() const;

    void setHitPosition(int);

    long getWallDistance() const;

    void setWallDistance(long);

    int getWallSize() const;

    void setWallSize(int);

    int getWallStart() const;

    void setWallStart(int);

    int getWallEnd() const;

    void setWallEnd(int);

    int getWallTexturePosition() const;

    void setWallTexturePosition(int);

    sf::Color const &getWallColor() const;

    void setWallColor(sf::Color const &);

    sf::Texture *getWallTexture() const;

    void setWallTexture(sf::Texture *);

    sf::Vector2u const &getWallTextureDimensions() const;

    void setWallTextureDimensions(sf::Vector2u const &);

private:
    Position _rayPosition;
    Position _incrementalPosition;
    sf::Vector2i _incrementalSteps;
    RayHitAxis _hitAxis;
    Level::BlockType _hitBlockType;
    int _hitPosition;
    long _wallDistance;
    int _wallSize;
    int _wallStart;
    int _wallEnd;
    int _wallTexturePosition;
    sf::Color _wallColor;
    sf::Texture *_wallTexture;
    sf::Vector2u _wallTextureDimensions;
};

#endif //WOLF3D_RAY_HH
