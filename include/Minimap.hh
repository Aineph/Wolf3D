/*
 * Created by Nicolas Fez for Wolf3D.
 * Started on 2020-04-22.
 */

#ifndef WOLF3D_MINIMAP_HH
#define WOLF3D_MINIMAP_HH

#define MINIMAP_DEFAULT_PROPORTION .3
#define MINIMAP_DEFAULT_PLAYER_SIZE 10
#define MINIMAP_DEFAULT_PLAYER_SHAPE 3

class Minimap : public IDrawable
{
public:
    Minimap();

    Minimap(Level *, sf::Vector2u const &);

    Minimap(Minimap const &);

    ~Minimap() override = default;

    Minimap &operator=(Minimap const &);

    void render(sf::RenderWindow *) const override;

    Level *getLevel() const;

    void setLevel(Level *);

    int getBlockSize() const;

    void setBlockSize(int);

    sf::Vector2u const &getMapPosition() const;

    void setMapPosition(sf::Vector2u const &);

    sf::Vector2u const &getMapDimensions() const;

    void setMapDimensions(sf::Vector2u const &);

    Position const &getPlayerPosition() const;

    void setPlayerPosition(Position const &);

private:
    Level *_level;
    int _blockSize;
    sf::Vector2u _mapPosition;
    sf::Vector2u _mapDimensions;
    Position _playerPosition;
};


#endif //WOLF3D_MINIMAP_HH
