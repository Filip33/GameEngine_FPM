#include "Button.h"

Button::Button() = default;

Button::Button(sf::Vector2f size, sf::Color color, std::string text)
{
    bPressed = false;
    bReleased = false;
    bClicked = false;
    bHighlighted = false;
    defaultColor = sf::Color(color);
    highlightedColor = sf::Color(defaultColor.r + 50, defaultColor.g + 50, defaultColor.b + 50);
    buttonBG.setSize(size);
    buttonBG.setFillColor(defaultColor);
    buttonBG.setPosition(sf::Vector2f(0, 0));
    buttonText.setCharacterSize(12);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(sf::Vector2f(0, 0));
    buttonText.setString(text);
}

bool Button::IsHighlighted()
{
    return bHighlighted;
}

void Button::Highlight(sf::RenderWindow* window)
{
    // Check boundaries of button when the cursor hovwers over it
    if (buttonBG.getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window))))
    {
        buttonBG.setFillColor(sf::Color(highlightedColor));
        this->bHighlighted = true;
    }
    else
    {
        buttonBG.setFillColor(sf::Color(defaultColor));
        this->bHighlighted = false;
    }
}

void Button::Update(sf::Event event, float deltaTime)
{
    CheckPressed(event);
}

void Button::Render(sf::RenderWindow* window, float deltaTime)
{
    window->draw(buttonBG);
    window->draw(buttonText);
    window->display();
}

void Button::CheckPressed(sf::Event event)
{
    if (bHighlighted == true)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
        {
            bPressed = true;
        }
        else
        {
            bPressed = false;
            bClicked = false;
        }
    }
    if (bPressed == true)
    {
        if (event.type == sf::Event::MouseButtonReleased)
        {
            bReleased = true;
            bClicked = true;
        }
    }
    else
    {
        bReleased = false;
        bClicked = false;
    }
}

Button::~Button() = default;