#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"
#include "State.h"
#include "Application.h"

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "");
    window.setFramerateLimit(60);
    TextureHolder textures;
    //FontHolder fonts;
    //fonts.load("font", "font/text.ttf");
    //struct State::Context context(window, textures, fonts);

    sf::Event event;
    //Application app(context);
    //int truc = app.run();
    while(window.isOpen()) {
        while(window.pollEvent(event)) {
            
        }
        window.clear();
        window.display();
    }


    return 0;
}
