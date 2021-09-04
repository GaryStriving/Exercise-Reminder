#include "../../include/EasyWindow/EasyWindow.hpp"

GuiElementInterface::GuiElementInterface(int new_identifier, sf::Font& new_font, std::unordered_map<std::string,std::function<void()>> new_event_reponses):
    identifier(new_identifier),
    focus(false),
    font(new_font),
    event_reponses(new_event_reponses)
{}

bool GuiElementInterface::touchesPoint(std::pair<int,int> point)
{
    return this->getRect().contains(point.first,point.second);
}

void GuiElementInterface::launchEvent(std::string event_name)
{
    if(this->event_reponses.find(event_name) != this->event_reponses.end())
        this->event_reponses[event_name]();
}
