#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "../headers/sglobal.hpp"
#include "../headers/cpicture.hpp"
#include "../headers/cbutton.hpp"
#include "../headers/cslide.hpp"
#include "../headers/cmessagebox.hpp"

void __attribute__((constructor)) sfsdctor(void)
{}

sf::Color sd::Global::_colorbg = sf::Color(170, 170, 170);
sf::Color sd::Global::_colorfg = sf::Color(185, 185, 185);
sf::Color sd::Global::_colorbase = sf::Color(255, 255, 255);
sf::Color sd::Global::_colortext = sf::Color(0, 0, 0);
sf::Color sd::Global::_colorpressedbase = sf::Color(200, 200, 200);
sf::Color sd::Global::_colordisabledbase = sf::Color(215, 215, 215);
sf::Color sd::Global::_colordisabledtext = sf::Color(120, 120, 120);
sf::Font sd::Global::_font;

std::vector<sf::Image> sd::Global::_images(3);
sd::Picture sd::Global::_picturebutton;
sd::Picture sd::Global::_picturesliderail;
sd::Picture sd::Global::_pictureslidebutton;

const sd::Picture& sd::Global::PictureButton = _picturebutton;
const sd::Picture& sd::Global::PictureSlideRail = _picturesliderail;
const sd::Picture& sd::Global::PictureSlideButton = _pictureslidebutton;
//const sf::Image sd::Global::ImageCheckBox;
//const sf::Image sd::Global::ImageRadioButton;

//merge two vectors in one, excluding empty strings
std::vector<std::string> sd::Global::_VectorMerge(const std::vector<std::string>& a, const std::vector<std::string>& b, bool noempty)
{
	std::vector<std::string> res;
	for (unsigned int i = 0; i < a.size(); i++)
		if (a.at(i) != "" || !noempty)
			res.push_back(a.at(i));
	for (unsigned int i = 0; i < b.size(); i++)
		if (b.at(i) != "" || !noempty)
			res.push_back(b.at(i));
	return res;
}

//find cariable and get it's value, dividing on elements by separators
std::vector<std::string> sd::Global::_EnvParse(char** env, std::string variable, std::string separator)
{
	//find values if var exists
	std::string allvalues = "";
	variable += '=';
	for (int i = 0; env[i]; i++)
	{
		bool found = true;
		for (int j = 0; j < 5 && env[i][j] != 0; j++)
			if (env[i][j] != variable.at(j))
			{
				found = false;
				break;
			}
		
		if (found)
		{
			allvalues = env[i];
			allvalues = allvalues.substr(variable.length());
			break;
		}
	}
	
	std::string tempstr;
	std::vector<std::string> res;
	
	int found = 0;
	//while one of separator chars found
	while ((found = allvalues.find_first_of(separator)) != (int)std::string::npos)
	{
		//string between separators
		tempstr = allvalues.substr(0, found);
		res.push_back(tempstr);
		//cut added part
		allvalues = allvalues.substr(found+1, allvalues.length()-found-1);
	}
	//push string after last separator
	res.push_back(allvalues);
	
	return res;
}

int sd::Global::_LoadFont(std::vector<std::string> paths)
{
	std::ifstream testfile;
	std::string localpath = "/../share/sfsd/fonts/DroidSans.ttf";
	for (unsigned int i = 0; i < paths.size(); i++)
	{
		testfile.open((paths.at(i) + localpath).c_str(), std::ios_base::in);
		if (testfile.is_open())
		{
			testfile.close();
			_font.loadFromFile((paths.at(i) + localpath).c_str());
			break;
		}
		if (i >= paths.size()-1)
		{
			std::cout << "Error! Can't load font. Please, reinstall sfsd library." << std::endl;
			for (unsigned int i = 0; i < paths.size(); i++)
				std::cout << "    tried " << paths.at(i) + localpath << std::endl;
			return 10;
		}
	}
	sd::Button::SetBaseFont(_font);
	sd::MessageBox::SetBaseFont(_font);
	return 0;
}

int sd::Global::_LoadImages(std::vector<std::string> paths)
{
	std::ifstream testfile;
	std::vector<std::string> localpaths;
	localpaths.push_back("/../share/sfsd/images/button.png");
	localpaths.push_back("/../share/sfsd/images/slide.png");
	localpaths.push_back("/../share/sfsd/images/slidebutton.png");
	for (unsigned int j = 0; j < localpaths.size(); j++)
		for (unsigned int i = 0; i < paths.size(); i++)
		{
			testfile.open((paths.at(i) + localpaths.at(i)).c_str());
			if (testfile.is_open())
			{
				_images.at(j).loadFromFile((paths.at(i) + localpaths.at(j)).c_str());
				testfile.close();
				break;
			}
			if (i >= paths.size()-1)
			{
				std::cout << "Error! Can't load images. Please, reinstall sfsd library." << std::endl;
				return 11;
			}
		}
	
	sd::Button::SetBasePicture( sd::Picture(_images.at(0), sf::Vector2f(-1, -1), true) );
	sd::MessageBox::SetBaseButtonPicture( sd::Picture(_images.at(0), sf::Vector2f(-1, -1), true) );
	sd::Slide::SetBasePicture( sd::Picture(_images.at(1), sf::Vector2f(-1, -1), false) );
	sd::Slide::SetBaseButtonPicture( sd::Picture(_images.at(2), sf::Vector2f(-1, -1), false) );
	
	return 0;
}


const sf::Color& sd::Global::ColorBackground = sd::Global::_colorbg;
const sf::Color& sd::Global::ColorForeground = sd::Global::_colorfg;
const sf::Color& sd::Global::ColorBase = sd::Global::_colorbase;
const sf::Color& sd::Global::ColorText = sd::Global::_colortext;
const sf::Color& sd::Global::ColorPressedBase = sd::Global::_colorpressedbase;
const sf::Color& sd::Global::ColorDisabledBase = sd::Global::_colordisabledbase;
const sf::Color& sd::Global::ColorDisabledText = sd::Global::_colordisabledtext;
const sf::Font& sd::Global::Font = sd::Global::_font;

int sd::Global::Init(char** env)
{
	//_font.loadFromFile("resources/fonts/DroidSans.ttf"); //TODO: insert some pics and font in source files
	std::vector<std::string> paths;
	paths.push_back("./lib");
	paths = _VectorMerge(paths, _VectorMerge(_EnvParse(env, "LD_LIBRARY_PATH", ":"), _EnvParse(env, "PATH", ":")));
	int r = _LoadFont(paths);
	if (r)
		return r;
	
	r = _LoadImages(paths);
	if (r)
		return r;
	return 0;
}
