#include <SFML/Graphics.hpp>

#include "../headers/sbasevalues.h"

sf::Color sd::Global::_colorbase = sf::Color(170, 170, 170);
sf::Color sd::Global::_colorpressed = sf::Color(200, 200, 200);
sf::Color sd::Global::_colordisabled = sf::Color(215, 215, 215);
sf::Color sd::Global::_colordisabledtext = sf::Color(120, 120, 120);
sf::Font sd::Global::_font;

const sf::Color& sd::Global::ColorBase = sd::Global::_colorbase;
const sf::Color& sd::Global::ColorPressed = sd::Global::_colorpressed;
const sf::Color& sd::Global::ColorDisabled = sd::Global::_colordisabled;
const sf::Color& sd::Global::ColorDisabledText = sd::Global::_colordisabledtext;
const sf::Font& sd::Global::Font = sd::Global::_font;

void sd::Global::Init()
{
	_font.loadFromFile("resources/fonts/DroidSans.ttf");
}
