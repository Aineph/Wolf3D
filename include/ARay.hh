/*
 * Created by Nicolas Fez for Wolf3D.
 * Started on 2020-04-23.
 */

#ifndef WOLF3D_ARAY_HH
#define WOLF3D_ARAY_HH

#define RAY_VERTEX_NUMBER 2

namespace RayCaster
{
    class ARay : public IDrawable
    {
    public:
        ARay();

        explicit ARay(sf::Vector2u const &, Display::DisplayType);

        ARay(ARay const &);

        ~ARay() override;

        ARay &operator=(ARay const &);

        void render(sf::RenderWindow *) const override;

        virtual void initialize(Position const &, sf::Vector2u const &) = 0;

        virtual void
        cast(Position const &, Level *, std::map<Level::BlockType, sf::Texture *> const &, sf::Vector2u const &) = 0;

        long getRayDistance() const;

        void setRayDistance(long);

        sf::Vector2i *getRayCoordinates() const;

        void setRayCoordinates(sf::Vector2i *);

        sf::Vector2f *getRayTextureCoordinates() const;

        void setRayTextureCoordinates(sf::Vector2f *);

        sf::Vector2i const &getIncrementalSteps() const;

        void setIncrementalSteps(sf::Vector2i const &);

        Display::DisplayType getRayDisplayType() const;

        void setRayDisplayType(Display::DisplayType);

        sf::Color const &getRayColor() const;

        void setRayColor(sf::Color const &);

        sf::Texture *getRayTexture() const;

        void setRayTexture(sf::Texture *);

    private:
        long _rayDistance;
        sf::Vector2i *_rayCoordinates;
        sf::Vector2f *_rayTextureCoordinates;
        sf::Vector2i _incrementalSteps;
        Display::DisplayType _rayDisplayType;
        sf::Color _rayColor;
        sf::Texture *_rayTexture;
    };
}


#endif //WOLF3D_ARAY_HH
