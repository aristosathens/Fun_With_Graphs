#ifndef MAPPER_GRAPHICS_H
#define MAPPER_GRAPHICS_H

#include "mapper.h"

#include <SDL.h>

#define DEFAULT_POINT_SIZE 5

struct Color
{
    int r, g, b;
};

const Color Black = Color {0x00, 0x00, 0x00};
const Color White = Color {0xFF, 0xFF, 0xFF};
const Color Red = Color {0xFF, 0x00, 0x00};

const Color DefaultColor = Black;

class Graphics
{
    //
    // Public
    //
    public:
    // Destructor
    ~Graphics();
    void setup_window();

    void add_point(Point*, Color color = White);
    void add_point(int, int, Color color = White);
    void draw_point(int, int, Color color = White);

    void add_edge(Point*, Point*, Color color = Red);
    void add_edge(int, int, int, int, Color color = Red);
    void draw_line(int, int, int, int, Color color = Red);

    void display();

    //
    // Private
    //
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif /* MAPPER_GRAPHICS_H */