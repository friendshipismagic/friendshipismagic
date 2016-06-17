#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"
#include "State.h"
#include "Application.h"

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 640), "Friendship is magic");
    window.setFramerateLimit(60);
    TextureHolder textures;
    FontHolder fonts;
    fonts.load("font", "font/text.ttf");
    struct State::Context context(window, textures, fonts);

    Application app(context);
    int truc = app.run();

    return truc;
}
