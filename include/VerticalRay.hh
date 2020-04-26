/*
 * Created by Nicolas Fez for Wolf3D.
 * Started on 2020-04-24.
 */

#ifndef WOLF3D_VERTICALRAY_HH
#define WOLF3D_VERTICALRAY_HH

namespace RayCaster
{
    class VerticalRay : virtual public ARay
    {
    public:
        VerticalRay();

        explicit VerticalRay(sf::Vector2u const &, Display::DisplayType);

        VerticalRay(VerticalRay const &);

        ~VerticalRay() override = default;

        VerticalRay &operator=(VerticalRay const &);

        void initialize(Position const &, sf::Vector2u const &) override;

        void cast(Position const &, Level *, std::map<Level::BlockType, sf::Texture *> const &,
                  sf::Vector2u const &) override;

        void fillCoordinates(int, Position const &, sf::Vector2u const &);

        Position const &getRayPosition() const;

        void setRayPosition(Position const &);

        Position const &getIncrementalPosition() const;

        void setIncrementalPosition(Position const &);

    private:
        Position _rayPosition;
        Position _incrementalPosition;
    };
}


#endif //WOLF3D_VERTICALRAY_HH
