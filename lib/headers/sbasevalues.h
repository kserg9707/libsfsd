#ifndef BASEVALUES_H
#define BASEVALUES_H

#include <SFML/Graphics.hpp>

namespace sd
{

class Global
{
private:
	static sf::Color _colorpressed;
	static sf::Color _colordisabled;
	static sf::Color _colordisabledtext;
	static sf::Font _font;
public:
	static const sf::Color& ColorPressed;
	static const sf::Color& ColorDisabled;
	static const sf::Color& ColorDisabledText;
	static const sf::Font& Font;
	
	static void Init();
};

}

#endif
