#include "../../include/EasyWindow/EasyWindow.hpp"

TextView::TextView(int new_identifier, std::string new_text, sf::Font& new_font, std::unordered_map<std::string,std::function<void()>> new_event_reponses):
    GuiElementInterface(new_identifier,new_font,new_event_reponses),
    text(new_text,this->font,16)
{
    this->text.setFillColor(sf::Color::Black);
}

void TextView::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= this->getTransform();
    target.draw(this->text,states);
}

std::unordered_map<std::string,std::string> TextView::getElementData() const
{
    return {
        {"type","text_view"},
        {"identifier", std::to_string(this->identifier)},
        {"text",this->text.getString()}
    };
}

void TextView::gainFocus(){}

void TextView::loseFocus(){}

sf::Rect<float> TextView::getRect() const
{
    return sf::Rect<float>(this->getPosition().x,this->getPosition().y,this->text.getGlobalBounds().width,this->text.getGlobalBounds().height);
}
