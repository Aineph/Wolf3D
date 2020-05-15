/*
 * Created by Nicolas Fez for Wolf3D.
 * Started on 2020-04-10.
 */

#ifndef WOLF3D_ENGINE_HH
#define WOLF3D_ENGINE_HH

namespace RayCaster
{
    class Engine
    {
    public:
        Engine();

        Engine(sf::RenderWindow *, Level *);

        Engine(Engine const &);

        virtual ~Engine() = default;

        Engine &operator=(Engine const &);

        void
        raycast(Position const &, Level *, std::map<Level::BlockType, sf::Texture *> const &, Display::DisplayType);

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

#endif //WOLF3D_ENGINE_HH
