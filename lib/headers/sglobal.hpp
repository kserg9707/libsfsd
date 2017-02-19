#ifndef BASEVALUES_H
#define BASEVALUES_H

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "cpicture.hpp"

void __attribute__((constructor)) sfsdctor(void);

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
	
	static std::vector<sf::Image> _images;
	static sd::Picture _picturebutton;
	static sd::Picture _picturesliderail;
	static sd::Picture _pictureslidebutton;
	
	//merge two vectors in one, excluding empty strings
	static std::vector<std::string> _VectorMerge
		(const std::vector<std::string>& a, const std::vector<std::string>& b, bool noempty = true);
	
	//find cariable and get it's value, dividing on elements by separators
	static std::vector<std::string> _EnvParse(char** env, std::string variable, std::string separator);
	
	static int _LoadFont(std::vector<std::string> paths);
	
	static int _LoadImages(std::vector<std::string> paths);
public:
	static const sf::Color& ColorBackground;
	static const sf::Color& ColorForeground;
	static const sf::Color& ColorBase;
	static const sf::Color& ColorText;
	static const sf::Color& ColorPressedBase;
	static const sf::Color& ColorDisabledBase;
	static const sf::Color& ColorDisabledText;
	static const sf::Font& Font;
	
	static const sd::Picture& PictureButton;
	static const sd::Picture& PictureSlideRail;
	static const sd::Picture& PictureSlideButton;
	//static const sf::Image& ImageCheckBox;
	//static const sf::Image& ImageRadioButton;
	
	static int Init(char** env);
};

}

#endif
