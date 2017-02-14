#include <SFML/Graphics.hpp>

#include "../headers/sbasevalues.h"

sf::Color sd::Global::_colorbg = sf::Color(170, 170, 170);
sf::Color sd::Global::_colorfg = sf::Color(185, 185, 185);
sf::Color sd::Global::_colorbase = sf::Color(255, 255, 255);
sf::Color sd::Global::_colortext = sf::Color(0, 0, 0);
sf::Color sd::Global::_colorpressedbase = sf::Color(200, 200, 200);
sf::Color sd::Global::_colordisabledbase = sf::Color(215, 215, 215);
sf::Color sd::Global::_colordisabledtext = sf::Color(120, 120, 120);
sf::Font sd::Global::_font;

const sf::Color& sd::Global::ColorBackground = sd::Global::_colorbg;
const sf::Color& sd::Global::ColorForeground = sd::Global::_colorfg;
const sf::Color& sd::Global::ColorBase = sd::Global::_colorbase;
const sf::Color& sd::Global::ColorText = sd::Global::_colortext;
const sf::Color& sd::Global::ColorPressedBase = sd::Global::_colorpressedbase;
const sf::Color& sd::Global::ColorDisabledBase = sd::Global::_colordisabledbase;
const sf::Color& sd::Global::ColorDisabledText = sd::Global::_colordisabledtext;
const sf::Font& sd::Global::Font = sd::Global::_font;

void sd::Global::Init()
{
	_font.loadFromFile("resources/fonts/DroidSans.ttf");
}
