#include "PauseMenu.h"

PauseMenu::PauseMenu() = default;

PauseMenu::PauseMenu(sf::RenderWindow* window)
{
	States::SetPauseState(false);
	InitButtons();
}

void PauseMenu::Update(sf::Event event, float deltaTime, sf::RenderWindow* window)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			States::SetPauseState(States::GetPausedState() == false);
		}
	}

	ButtonMap::GetMap() ["RESUME"]->Update(event, deltaTime);
	ButtonMap::GetMap()["LOAD"]->Update(event, deltaTime);
	ButtonMap::GetMap()["SAVE"]->Update(event, deltaTime);
	ButtonMap::GetMap()["QUIT"]->Update(event, deltaTime);

	if (ButtonMap::GetMap()["RESUME"]->bClicked == true)
	{
		States::SetPauseState(States::GetPausedState() == false);
		ButtonMap::GetMap()["RESUME"]->bClicked = false;
	}
	if (ButtonMap::GetMap()["QUIT"]->bClicked == true)
	{
		Quit(window);
		ButtonMap::GetMap()["QUIT"]->bClicked = false;
	}
}

void PauseMenu::Render(sf::RenderWindow* window, float deltaTime, sf::Vector2f resumePosition)
{
	sf::Font _Arial;

	_Arial.loadFromFile("../Debug/Fonts/Arial.ttf");
	sf::Vector2f _SizeOffset = sf::Vector2f(
		ButtonMap::GetMap()["RESUME"]->buttonBG.getSize().x / 2, 
		ButtonMap::GetMap()["RESUME"]->buttonBG.getSize().y / 2);

	// Resume Button
	ButtonMap::GetMap()["RESUME"]->buttonBG.setPosition(resumePosition + sf::Vector2f(0, -80) - _SizeOffset);
	ButtonMap::GetMap()["RESUME"]->buttonText.setFont(_Arial);
	ButtonMap::GetMap()["RESUME"]->buttonText.setPosition(ButtonMap::GetMap()["RESUME"]->buttonBG.getPosition());
	ButtonMap::GetMap()["RESUME"]->Highlight(window);
	ButtonMap::GetMap()["RESUME"]->Render(window, deltaTime);

	// Load Button
	ButtonMap::GetMap()["LOAD"]->buttonBG.setPosition(resumePosition + sf::Vector2f(0, -40) - _SizeOffset);
	ButtonMap::GetMap()["LOAD"]->buttonText.setFont(_Arial);
	ButtonMap::GetMap()["LOAD"]->buttonText.setPosition(ButtonMap::GetMap()["LOAD"]->buttonBG.getPosition());
	ButtonMap::GetMap()["LOAD"]->Highlight(window);
	ButtonMap::GetMap()["LOAD"]->Render(window, deltaTime);

	// Save Button
	ButtonMap::GetMap()["SAVE"]->buttonBG.setPosition(resumePosition + sf::Vector2f(0, 0) - _SizeOffset);
	ButtonMap::GetMap()["SAVE"]->buttonText.setFont(_Arial);
	ButtonMap::GetMap()["SAVE"]->buttonText.setPosition(ButtonMap::GetMap()["SAVE"]->buttonBG.getPosition());
	ButtonMap::GetMap()["SAVE"]->Highlight(window);
	ButtonMap::GetMap()["SAVE"]->Render(window, deltaTime);

	// Quit Button
	ButtonMap::GetMap()["QUIT"]->buttonBG.setPosition(resumePosition + sf::Vector2f(0, 40) - _SizeOffset);
	ButtonMap::GetMap()["QUIT"]->buttonText.setFont(_Arial);
	ButtonMap::GetMap()["QUIT"]->buttonText.setPosition(ButtonMap::GetMap()["QUIT"]->buttonBG.getPosition());
	ButtonMap::GetMap()["QUIT"]->Highlight(window);
	ButtonMap::GetMap()["QUIT"]->Render(window, deltaTime);

	window->display();
}

void PauseMenu::InitButtons()
{
	sf::Vector2f _Size = sf::Vector2f(125, 30);

	ButtonMap::GetMap().insert(
		{
			"RESUME",
			new Button(_Size, sf::Color(100, 100, 100, 255), "Resume Game")
		});

	ButtonMap::GetMap().insert(
		{
			"LOAD",
			new Button(_Size, sf::Color(100, 100, 100, 255), "Load Tile Map")
		});

	ButtonMap::GetMap().insert(
		{
			"SAVE",
			new Button(_Size, sf::Color(100, 100, 100, 255), "Save Tile Map")
		});

	ButtonMap::GetMap().insert(
		{
			"QUIT",
			new Button(_Size, sf::Color(100, 100, 100, 255), "Quit Game")
		});
}

void PauseMenu::Quit(sf::RenderWindow* window)
{
	window->close();
}

PauseMenu::~PauseMenu() = default;