#include <iostream> /* Debug only */
#include <SFML/Graphics.hpp>
#include <string>
#include <list>
#include <functional>

class GuiElementInterface: public sf::Drawable, public sf::Transformable
{
protected:
    const int identifier;
    bool focus;
    const sf::Font& font;
    std::unordered_map<std::string,std::function<void()>> event_reponses;
public:
    GuiElementInterface(int new_identifier, sf::Font& new_font, std::unordered_map<std::string,std::function<void()>> new_event_reponses);
    virtual std::unordered_map<std::string,std::string> getElementData() const {return {};}
    virtual void gainFocus() {}
    virtual void loseFocus() {}
    virtual sf::Rect<float> getRect() const {return sf::Rect<float>(0,0,0,0);}
    bool touchesPoint(std::pair<int,int> point);
    bool isFocused() const {return this->focus;}
    void launchEvent(std::string event_name);
};

class Button: public GuiElementInterface
{
private:
    sf::RectangleShape background;
    sf::Text text;
public:
    Button(int new_identifier,std::string new_text, sf::Font& font, std::unordered_map<std::string,std::function<void()>> new_event_reponses);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    std::unordered_map<std::string,std::string> getElementData() const override;
    void gainFocus() override;
    void loseFocus() override;
    sf::Rect<float> getRect() const override;
};

class TextView: public GuiElementInterface
{
private:
    sf::Text text;
public:
    TextView(int new_identifier, std::string new_text, sf::Font& new_font, std::unordered_map<std::string,std::function<void()>> new_event_reponses);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    std::unordered_map<std::string,std::string> getElementData() const override;
    void gainFocus() override;
    void loseFocus() override;
    sf::Rect<float> getRect() const override;
};

class TextInput: public GuiElementInterface
{
private:
    sf::RectangleShape background;
    const std::string content;
public:
    TextInput(int new_identifier, sf::Font& new_font, std::unordered_map<std::string,std::function<void()>> new_event_reponses);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    std::unordered_map<std::string,std::string> getElementData() const override;
    void gainFocus() override;
    void loseFocus() override;
    sf::Rect<float> getRect() const override;
};

class EasyWindow
{
private:
    sf::RenderWindow window;
    bool do_close;
    int exit_code;
    std::list<GuiElementInterface*> interface;
    sf::Font calibri;
public:
    EasyWindow(std::pair<int,int> dimensions, std::string window_title);
    void addButton(int identifier, std::pair<int,int> coords, std::string text, std::unordered_map<std::string,std::function<void()>> event_reponses = {});
    void addTextInput(int identifier, std::pair<int,int> coords, std::unordered_map<std::string,std::function<void()>> event_reponses = {});
    void addTextView(int identifier, std::pair<int,int> coords, std::string text, std::unordered_map<std::string,std::function<void()>> event_reponses = {});
    void setFullScreen(bool do_set_fullscreen);
    void run(std::unordered_map<std::string,std::function<void()>> event_reponses = {});
    void close();
    std::unordered_map<std::string,std::string> getElementDataByIdentifier(int identifier) const;
    ~EasyWindow();
};
