#ifndef BASEVALUES_H
#define BASEVALUES_H

#include <SFML/Graphics.hpp>

namespace sd
{

class Global
{
private:
	static sf::Color _colorbg;
	static sf::Color _colorfg;
	static sf::Color _colorbase;
	static sf::Color _colortext;
	static sf::Color _colorpressedbase;
	static sf::Color _colordisabledbase;
	static sf::Color _colordisabledtext;
	static sf::Font _font;
public:
	static const sf::Color& ColorBackground;
	static const sf::Color& ColorForeground;
	static const sf::Color& ColorBase;
	static const sf::Color& ColorText;
	static const sf::Color& ColorPressedBase;
	static const sf::Color& ColorDisabledBase;
	static const sf::Color& ColorDisabledText;
	static const sf::Font& Font;
	
	static void Init();
};

}

#endif
