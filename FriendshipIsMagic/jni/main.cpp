#ifdef ANDROID_BUILD
    #include <android/native_activity.h>
    #include <SFML/System/NativeActivity.hpp>
#endif

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ressources/resourceholder.h"
#include "states/state.h"
#include "application.h"
//#include <iostream>
#include <fstream>

#include <exception>

int main()
{
    std::string sourceDir = "";


 //   std::cout << "friendship is magic log" << std::endl;
    // Create the main window

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "");
    window.setFramerateLimit(60);
    TextureHolder textures;
    textures.loadFromFile("Config/TextureConfig.txt");
    FontHolder fonts;
    fonts.load("font", "font/text.ttf");
    SoundBufferHolder sounds;
    sounds.loadFromFile("Config/SoundConfig.txt");
    struct State::Context context(window, textures, fonts, sounds);

    Application app(context);
	int truc = app.run();

    return truc;
}
