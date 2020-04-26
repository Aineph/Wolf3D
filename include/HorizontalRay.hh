/*
 * Created by Nicolas Fez for Wolf3D.
 * Started on 2020-04-24.
 */

#ifndef WOLF3D_HORIZONTALRAY_HH
#define WOLF3D_HORIZONTALRAY_HH

namespace RayCaster
{
    class HorizontalRay : virtual public ARay
    {
    public:
        HorizontalRay();

        explicit HorizontalRay(sf::Vector2u const &, Display::DisplayType);

        HorizontalRay(HorizontalRay const &);

        ~HorizontalRay() override = default;

        HorizontalRay &operator=(HorizontalRay const &);

        void initialize(Position const &, sf::Vector2u const &) override;

        void cast(Position const &, Level *, std::map<Level::BlockType, sf::Texture *> const &,
                  sf::Vector2u const &) override;

        Position const &getFirstRayPosition() const;

        void setFirstRayPosition(Position const &);

        Position const &getLastRayPosition() const;

        void setLastRayPosition(Position const &);

    private:
        Position _firstRayPosition;
        Position _lastRayPosition;
    };
}


#endif //WOLF3D_HORIZONTALRAY_HH
