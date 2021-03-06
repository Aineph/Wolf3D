/*
 * Created by Nicolas Fez for Wolf3D.
 * Started on 2020-04-08.
 */

#ifndef WOLF3D_LEVEL_HH
#define WOLF3D_LEVEL_HH

#define LEVEL_DEFAULT_NAME "Default Level"
#define LEVEL_DEFAULT_FILE "../resources/levels/default.lvl"

class Level
{
public:
    enum BlockType
    {
        BLOCK_EMPTY = '0',
        BLOCK_BARREL = 'b',
        BLOCK_BLUE_WALL = '1',
        BLOCK_COLOR_WALL = '2',
        BLOCK_EAGLE_WALL = '3',
        BLOCK_GREEN_LIGHT = 'g',
        BLOCK_GREY_WALL = '4',
        BLOCK_MOSSY_WALL = '5',
        BLOCK_PILLAR = 'p',
        BLOCK_PURPLE_WALL = '6',
        BLOCK_RED_WALL = '7',
        BLOCK_WOODEN_WALL = '8',
        BLOCK_START_UP = 'A',
        BLOCK_START_RIGHT = '>',
        BLOCK_START_DOWN = 'V',
        BLOCK_START_LEFT = '<'
    };

    Level();

    Level(Level const &);

    virtual ~Level() = default;

    Level &operator=(Level const &);

    friend std::ostream &operator<<(std::ostream &, Level const &);

    static bool isLevelWall(int);

    Position loadLevelMap();

    std::string const &getLevelName() const;

    void setLevelName(std::string const &);

    std::string const &getLevelFile() const;

    void setLevelFile(std::string const &);

    int getLevelWidth() const;

    void setLevelWidth(int);

    int getLevelHeight() const;

    void setLevelHeight(int);

    std::vector<std::vector<int>> const &getLevelMap() const;

    void setLevelMap(std::vector<std::vector<int>> const &);

private:
    std::string _levelName;
    std::string _levelFile;
    int _levelWidth;
    int _levelHeight;
    std::vector<std::vector<int>> _levelMap;
};


#endif //WOLF3D_LEVEL_HH
