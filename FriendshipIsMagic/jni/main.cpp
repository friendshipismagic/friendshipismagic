#include <SFML/Graphics.hpp>
#include "resourceholder.h"
#include "state.h"
#include "application.h"

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Friendship is magic");
    window.setFramerateLimit(60);
    TextureHolder textures;
    textures.loadFromFile("Config/TextureConfig.txt");
    FontHolder fonts;
    fonts.load("font", "font/text.ttf");
    struct State::Context context(window, textures, fonts);

    Application app(context);
    int truc = app.run();

    return truc;
}
