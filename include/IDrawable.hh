/*
 * Created by Nicolas Fez for Wolf3D.
 * Started on 2020-04-22.
 */

#ifndef WOLF3D_IDRAWABLE_HH
#define WOLF3D_IDRAWABLE_HH

class IDrawable
{
public:
    virtual ~IDrawable() = default;

    virtual void render(sf::RenderWindow *) const = 0;
};

#endif //WOLF3D_IDRAWABLE_HH
