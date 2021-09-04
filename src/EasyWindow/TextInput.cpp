#include "../../include/EasyWindow/EasyWindow.hpp"

TextInput::TextInput(int new_identifier, sf::Font& new_font, std::unordered_map<std::string,std::function<void()>> new_event_reponses):
    GuiElementInterface(new_identifier,new_font,new_event_reponses),
    background(sf::Vector2f(300,20)),
    content("")
{
    this->background.setFillColor(sf::Color::White);
    this->background.setOutlineColor(sf::Color::Black);
    this->background.setOutlineThickness(1);
}

void TextInput::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= this->getTransform();
    target.draw(this->background, states);
    target.draw(sf::Text(this->content,this->font,16), states);
}

std::unordered_map<std::string,std::string> TextInput::getElementData() const
{
    return {
        {"type", "text_input"},
        {"identifier", std::to_string(this->identifier)},
        {"content",this->content}
    };
}

void TextInput::gainFocus()
{
    this->focus = true;
    this->background.setFillColor(sf::Color::Red);
}

void TextInput::loseFocus()
{
    this->focus = false;
    this->background.setFillColor(sf::Color::White);
}

sf::Rect<float> TextInput::getRect() const
{
    return sf::Rect<float>(this->getPosition().x,this->getPosition().y,this->background.getGlobalBounds().width,this->background.getGlobalBounds().height);
}
