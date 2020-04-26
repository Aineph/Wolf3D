/*
 * Created by Nicolas Fez for Wolf3D.
 * Started on 2020-04-10.
 */

#ifndef WOLF3D_RAYCASTER_HH
#define WOLF3D_RAYCASTER_HH

namespace RayCaster
{
    class RayCaster
    {
    public:
        RayCaster();

        RayCaster(sf::RenderWindow *, Level *);

        RayCaster(RayCaster const &);

        virtual ~RayCaster() = default;

        RayCaster &operator=(RayCaster const &);

        void
        compute(Position const &, Level *, std::map<Level::BlockType, sf::Texture *> const &, Display::DisplayType);

        Minimap const &getMinimap() const;

        void setMinimap(Minimap const &);

        sf::RenderWindow *getWindow() const;

        void setWindow(sf::RenderWindow *);

        sf::Vector2u const &getWindowSize() const;

        void setWindowSize(sf::Vector2u const &);

    private:
        Minimap _minimap;
        sf::RenderWindow *_window;
        sf::Vector2u _windowSize;
    };
}

#endif //WOLF3D_RAYCASTER_HH
