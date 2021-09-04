#include "../../include/EasyWindow/EasyWindow.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

EasyWindow::EasyWindow(std::pair<int,int> dimensions, std::string window_title):
    window(sf::VideoMode(dimensions.first,dimensions.second), window_title),
    do_close(false),
    exit_code(0),
    interface()
{
    this->window.setVisible(false);
    this->calibri.loadFromFile("assets/calibri.ttf");
}

void EasyWindow::addButton(int identifier, std::pair<int,int> coords, std::string text, std::unordered_map<std::string,std::function<void()>> event_reponses)
{
    GuiElementInterface* button = dynamic_cast<GuiElementInterface*>(new Button(identifier, text, this->calibri, event_reponses));
    button->setPosition(coords.first,coords.second);
    this->interface.insert(this->interface.end(),button);
}

void EasyWindow::addTextInput(int identifier, std::pair<int,int> coords, std::unordered_map<std::string,std::function<void()>> event_reponses)
{
    GuiElementInterface* text_input = dynamic_cast<GuiElementInterface*>(new TextInput(identifier, this->calibri, event_reponses));
    text_input->setPosition(coords.first,coords.second);
    this->interface.insert(this->interface.end(),text_input);
}

void EasyWindow::addTextView(int identifier, std::pair<int,int> coords, std::string text, std::unordered_map<std::string,std::function<void()>> event_reponses)
{
    GuiElementInterface* text_view = dynamic_cast<GuiElementInterface*>(new TextView(identifier, text, this->calibri, event_reponses));
    text_view->setPosition(coords.first,coords.second);
    this->interface.insert(this->interface.end(),text_view);
}

void EasyWindow::setFullScreen(bool do_set_fullscreen)
{
    /* Method to set full screen in the different platforms */
}

void EasyWindow::close()
{
    this->do_close = true;
}

std::unordered_map<std::string,std::string> EasyWindow::getElementDataByIdentifier(int identifier) const
{
    for(GuiElementInterface* gui_element: this->interface)
        if(gui_element->getElementData()["identifier"] == std::to_string(identifier))
            return gui_element->getElementData();
    std::cerr << "EasyWindowError: Unknown identifier." << std::endl;
    return {};
}

void EasyWindow::run(std::unordered_map<std::string,std::function<void()>> event_reponses)
{
    this->window.setVisible(true);
    GuiElementInterface* last_focused_element = nullptr;
    while(!this->do_close)
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::Closed:
                if(event_reponses.find("close") != event_reponses.end())
                {
                    event_reponses["close"]();
                }
                else
                {
                    window.close();
                    this->do_close = true;
                }
                break;
            /* Launch events */
            case sf::Event::MouseButtonPressed:
                last_focused_element = nullptr;
                for(GuiElementInterface* gui_element: this->interface)
                {
                    if(last_focused_element == nullptr && gui_element->touchesPoint({event.mouseButton.x,event.mouseButton.y}))
                    {
                        last_focused_element = gui_element;
                        last_focused_element->gainFocus();
                        break;
                    }
                }
                for(GuiElementInterface* gui_element: this->interface)
                    if(gui_element->isFocused() && gui_element != last_focused_element)
                        gui_element->loseFocus();
                break;
            case sf::Event::MouseButtonReleased:
                if(last_focused_element != nullptr && last_focused_element->touchesPoint({event.mouseButton.x,event.mouseButton.y}))
                {
                    last_focused_element->launchEvent("onclick");
                }
                break;
            default:
                break;
            }
        }
        window.clear(sf::Color::White);
        for(GuiElementInterface* gui_element: this->interface)
            this->window.draw(*gui_element);
        window.display();
    }
    this->window.setVisible(false);
}

EasyWindow::~EasyWindow()
{
    for(GuiElementInterface* gui_element: this->interface)
        delete gui_element;
    this->window.close();
}
