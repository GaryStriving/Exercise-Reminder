#include <SFML/Graphics.hpp>
#include <ctime>

int main()
{
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width,sf::VideoMode::getDesktopMode().height), "Let's do exercise!", sf::Style::None);
    int resting_time = 600;
    std::time_t last_time = std::time(0);
    sf::Texture texture;
    if(!texture.loadFromFile("./assets/exercise.jpg"))
        throw;
    sf::Sprite sprite(texture);
    sprite.setScale(sf::VideoMode::getDesktopMode().width/sprite.getGlobalBounds().width,sf::VideoMode::getDesktopMode().height/sprite.getGlobalBounds().height);
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event));
        window.clear();
        window.draw(sprite);
        window.display();
        std::time_t time_now = std::time(0);
        std::time_t elapsed_time = time_now - last_time;
        last_time = time_now;
        resting_time -= elapsed_time;
        if(resting_time <= 0)
            window.close();
    }
}