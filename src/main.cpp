#include "../include/EasyWindow/EasyWindow.hpp"
#include "../include/App.hpp"
#include <SFML/Graphics.hpp>
#include <list>

int main(int argc, char* argv[])
{
    App app(argc == 1 ? RunType::Manual:RunType::Scheduled);
    return app.run();
}
