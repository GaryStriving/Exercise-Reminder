#include "../../include/EasyWindow/EasyWindow.hpp"

Button::Button(int new_identifier,std::string new_text, sf::Font& new_font, std::unordered_map<std::string,std::function<void()>> new_event_reponses):
    GuiElementInterface(new_identifier,new_font,new_event_reponses),
    background(sf::Vector2f(150,20)),
    text(new_text,this->font,16)
{
    this->text.setFillColor(sf::Color::Black);
    this->background.setFillColor(sf::Color::White);
    this->background.setOutlineColor(sf::Color::Black);
    this->background.setOutlineThickness(1);
    this->text.setOrigin(this->text.getGlobalBounds().width/2,0);
    this->text.setPosition(this->background.getGlobalBounds().width/2,0);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= this->getTransform();
    target.draw(this->background, states);
    target.draw(this->text, states);
}

std::unordered_map<std::string,std::string> Button::getElementData() const
{
    return {
        {"type", "button"},
        {"identifier", std::to_string(this->identifier)},
        {"text",this->text.getString()}
    };
}

void Button::gainFocus()
{
    this->focus = true;
    this->background.setFillColor(sf::Color::Red);
}

void Button::loseFocus()
{
    this->focus = false;
    this->background.setFillColor(sf::Color::White);
}

sf::Rect<float> Button::getRect() const
{
    return sf::Rect<float>(this->getPosition().x,this->getPosition().y,this->background.getGlobalBounds().width,this->background.getGlobalBounds().height);
}
