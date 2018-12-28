#include "mapper_graphics.h"

#define NO_STDIO_REDIRECT
#include <iostream>
#include <unistd.h>

using namespace::std;

Graphics::~Graphics()
{
    SDL_DestroyWindow(window); 
    SDL_Quit();
}

void Graphics::setup_window()
{
    SDL_Window* window;                    // Declare a pointer

    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "Graphics",                        // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        640,                               // width, in pixels
        480,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        throw runtime_error("Could not create SDL window.");
    }

    // We create a renderer with hardware acceleration, we also present according with the vertical sync refresh.
    renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void Graphics::add_point(Point* point, Color color /* = White */)
{

}

void Graphics::draw_point(int x, int y, Color color /* = White */)
{
    // Set our color for the draw functions
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0xFF);
    // Now we can draw our point
    SDL_RenderDrawPoint(renderer, x, y);
    // Set the color to what was before
    SDL_SetRenderDrawColor(renderer, DefaultColor.r, DefaultColor.g, DefaultColor.b, 0xFF);
}

void Graphics::add_edge(Point*, Point*, Color color /* = Red */)
{

}

void Graphics::draw_line(int x1, int y1, int x2, int y2, Color color /* = Red */)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0xFF);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    SDL_SetRenderDrawColor(renderer, DefaultColor.r, DefaultColor.g, DefaultColor.b, 0xFF);

}

void Graphics::display() 
{
    SDL_RenderPresent(renderer);
    sleep(5);
}

// int main ( int argc, char *argv[] )
int test_graphics()
{
    std::cout << "In test_graphics()." << std::endl << std::flush;
    SDL_SetHint(SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING, "1");
    SDL_SetMainReady();
    SDL_Window *window;

    SDL_Point window_position = {         //    Position of window
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED
    };
    SDL_Point window_size = {640, 480};   //    Size of window

    SDL_Point mouse_position;             //    Mouse position coords

    SDL_Init(SDL_INIT_VIDEO);             //    Initialize SDL2
    freopen( "CON", "w", stdout );
    freopen( "CON", "w", stderr );
    std::cout << "HERE" << std::endl << std::flush;

    // Create an application window with the following settings:
    window = SDL_CreateWindow( 
        "SDL_Point usage",                //    window title
        window_position.x,                //    initial x position
        window_position.y,                //    initial y position
        window_size.x,                    //    width, in pixels
        window_size.y,                    //    height, in pixels
        SDL_WINDOW_OPENGL                 //    flags - see below
    );

    // Check that the window was successfully made
    if (window == NULL) {
        SDL_Log("Could not create window: %s", SDL_GetError());
        return 1;
    }

    SDL_GetMouseState(                    //    Sets mouse_position to...
        &mouse_position.x,                // ...mouse arrow coords on window
        &mouse_position.y
    );

    SDL_Log("Mouse position: x=%i y=%i",  //    Print mouse position
         mouse_position.x, mouse_position.y
    );

    // sleep(5);

    // Close and destroy the window
    SDL_DestroyWindow(window); 

    // Clean up
    SDL_Quit();
    return 0;
}