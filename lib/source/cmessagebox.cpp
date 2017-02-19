#include <SFML/Graphics.hpp>
#include <cstdio>
#include <iostream>

#include "../headers/eaction.hpp"
#include "../headers/cpicture.hpp"
#include "../headers/cbutton.hpp"
#include "../headers/cmessagebox.hpp"

const int sd::MessageBox::ResultNull = -1;
/*const sd::MessageBox::MessageBoxResult sd::MessageBox::ResultOK = OK; //info, ask 1
const sd::MessageBox::MessageBoxResult sd::MessageBox::ResultCancel = Cancel; //ask, choose 0
const sd::MessageBox::MessageBoxResult sd::MessageBox::ResultYes = Yes; //choose 1
const sd::MessageBox::MessageBoxResult sd::MessageBox::ResultNo = No; 2*/

sd::Picture sd::MessageBox::_basebuttonpic; //default button picture, if not given another
sf::Font sd::MessageBox::_basefont; //so font

//private
void sd::MessageBox::_Init()
{
	_buttons = std::vector<sd::Button>();
	_fontsize = 16;
	_result = sd::MessageBox::ResultNull;
}

void sd::MessageBox::_ButtonsInit()
{}

void sd::MessageBox::_ButtonsDraw()
{}

//call checks for buttons
sd::Action sd::MessageBox::_MousePressedTest(sf::Vector2f mouse)
{
	for (unsigned int i = 0; i < _buttons.size(); i++)
		_buttons.at(i).PressedTest(mouse);
	return sd::ActionEmpty;
}

sd::Action sd::MessageBox::_MouseTest(sf::Vector2f mouse)
{
	for (unsigned int i = 0; i < _buttons.size(); i++)
		_buttons.at(i).DownTest(mouse);
	return sd::ActionEmpty;
}

//checks what button pressed
sd::Action sd::MessageBox::_MouseReleasedTest(sf::Vector2f mouse)
{
	//set _result here
	for (unsigned int i = 0; i < _buttons.size(); i++)
		_buttons.at(i).ReleasedTest(mouse);
	return sd::ActionEmpty;
}

void sd::MessageBox::_KeyEnterPressed()
{ _Close(false); }

void sd::MessageBox::_KeyEscapePressed()
{ _Close(false); }

void sd::MessageBox::_Close(bool buttonclicked)
{
	_msgwindow->close();
}


//public
sd::MessageBox::MessageBox()
{}

sd::MessageBox::MessageBox(const sf::String& windowname, const sf::String& text, sf::RenderWindow* parentwindow)
: _windowname(windowname), _windowtext(text), _parentwindow(parentwindow)
{
	_Init();
	
	//set font
	_font = _basefont;
	//set text
	_text = sf::Text(_windowtext, _font, _fontsize-2);
	_text.setColor(sf::Color::Black);
	//set text pivot
	sf::Vector2f textsize(_text.getLocalBounds().width, _text.getLocalBounds().height);
	_text.setOrigin((int)(textsize.x / 2), (int)(textsize.y / 2) + 3);
	
	//_buttonok = sd::Button("OK", sf::Vector2f(55, 105), _font, _basebuttonpic);
}


//static
void sd::MessageBox::SetBaseButtonPicture(const sd::Picture& pic)
{
	sd::MessageBox::_basebuttonpic = pic;
	sd::InfoMessageBox::SetBaseButtonPicture(pic);
	sd::AskMessageBox::SetBaseButtonPicture(pic);
	sd::ChooseMessageBox::SetBaseButtonPicture(pic);
}

//static
void sd::MessageBox::SetBaseFont(const sf::Font& font)
{
	sd::MessageBox::_basefont = font;
	sd::InfoMessageBox::SetBaseFont(_basefont);
	sd::AskMessageBox::SetBaseFont(_basefont);
	sd::ChooseMessageBox::SetBaseFont(_basefont);
}

int sd::MessageBox::Show()
{
	_result = ResultNull;
	
	_msgwindow = new sf::RenderWindow(sf::VideoMode(500, 150), _windowname, sf::Style::Titlebar);
	_msgwindow->setVerticalSyncEnabled(true);
	
	_ButtonsInit();
	
	_text.setPosition((int)(_msgwindow->getSize().x / 2), (int)(_msgwindow->getSize().y/3));
	
	while (_msgwindow->isOpen())
	{
		sf::Vector2i mousewindowpos = sf::Mouse::getPosition(*_msgwindow);
		sf::Vector2f mouseglobalpos = _msgwindow->mapPixelToCoords(mousewindowpos);
		
		sf::Event event;
		while (_msgwindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				_Close(false);
			
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					_KeyEscapePressed(); //closed there
				
				if (event.key.code == sf::Keyboard::Return)
					_KeyEnterPressed(); //closed there
			}
			
			//MouseHit
			if (event.type == sf::Event::MouseButtonPressed)
				if (event.mouseButton.button == sf::Mouse::Left)
					_MousePressedTest(mouseglobalpos);
			
			//mouse released
			if (event.type == sf::Event::MouseButtonReleased)
				if (event.mouseButton.button == sf::Mouse::Left)
					if (_MouseReleasedTest(mouseglobalpos) == sd::ActionButtonClicked)
						_Close(true);
		}
		
		//MouseDown
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			_MouseTest(mouseglobalpos);
		
		if (_parentwindow->hasFocus())
			_msgwindow->requestFocus();
		
		_msgwindow->clear(sf::Color(170,170,170));
		_msgwindow->draw(_text);
		for (unsigned int i = 0; i < _buttons.size(); i++)
			_buttons.at(i).Draw(*_msgwindow);
		_msgwindow->display();
	}
	
	return _result;
}





//////////////////
//InfoMessageBox//
//////////////////

const int sd::InfoMessageBox::ResultNull = -1;
const int sd::InfoMessageBox::ResultOK = 1; //info, ask 1

sd::Picture sd::InfoMessageBox::_basebuttonpic; //default button picture, if not given another
sf::Font sd::InfoMessageBox::_basefont; //so font



void sd::InfoMessageBox::_AdditionalInit()
{
	//call from sd::MessageBox and init buttons
	_buttons.clear();
	_buttons.push_back(sd::Button("OK", sf::Vector2f(0, 0), _font, _basebuttonpic));
}

void sd::InfoMessageBox::_ButtonsInit()
{
	_buttons.front().SetPosition(sf::Vector2f(250, 115) - (_buttons.front().GetSize() / (float)2));
}

//checks what button pressed
sd::Action sd::InfoMessageBox::_MouseReleasedTest(sf::Vector2f mouse)
{
	//set _result here
	for (unsigned int i = 0; i < _buttons.size(); i++)
		if(_buttons.at(i).ReleasedTest(mouse))
		{
			_result = sd::InfoMessageBox::ResultOK;
			return sd::ActionButtonClicked;
		}
	return sd::ActionEmpty;
}

void sd::InfoMessageBox::_KeyEnterPressed()
{
	_result = sd::InfoMessageBox::ResultOK;
	sd::MessageBox::_KeyEnterPressed();
}

void sd::InfoMessageBox::_KeyEscapePressed()
{}

//public
sd::InfoMessageBox::InfoMessageBox(const sf::String& windowname, const sf::String& text, sf::RenderWindow* parentwindow)
: sd::MessageBox::MessageBox(windowname, text, parentwindow)
{ _AdditionalInit(); }


//static
void sd::InfoMessageBox::SetBaseButtonPicture(const sd::Picture& pic)
{
	sd::InfoMessageBox::_basebuttonpic = pic;
}

//static
void sd::InfoMessageBox::SetBaseFont(const sf::Font& font)
{
	sd::InfoMessageBox::_basefont = font;
}





/////////////////
//AskMessageBox//
/////////////////

const int sd::AskMessageBox::ResultNull = -1;
const int sd::AskMessageBox::ResultOK = 1;
const int sd::AskMessageBox::ResultCancel = 0;

sd::Picture sd::AskMessageBox::_basebuttonpic; //default button picture, if not given another
sf::Font sd::AskMessageBox::_basefont; //so font



void sd::AskMessageBox::_AdditionalInit()
{
	//call from sd::MessageBox and init buttons
	_buttons.clear();
	_buttons.push_back(sd::Button("OK", sf::Vector2f(0, 0), _font, _basebuttonpic));
	_buttons.push_back(sd::Button("Cancel", sf::Vector2f(0, 0), _font, _basebuttonpic));
}

void sd::AskMessageBox::_ButtonsInit()
{
	_buttons.at(0).SetPosition(sf::Vector2f(180, 115) - (_buttons.front().GetSize() / (float)2));
	_buttons.at(1).SetPosition(sf::Vector2f(320, 115) - (_buttons.front().GetSize() / (float)2));
}

//checks what button pressed
sd::Action sd::AskMessageBox::_MouseReleasedTest(sf::Vector2f mouse)
{
	//set _result here
	for (unsigned int i = 0; i < _buttons.size(); i++)
		if(_buttons.at(i).ReleasedTest(mouse))
		{
			if (i == 0)
				_result = sd::AskMessageBox::ResultOK;
			if (i == 1)
				_result = sd::AskMessageBox::ResultCancel;
			return sd::ActionButtonClicked;
		}
	return sd::ActionEmpty;
}

void sd::AskMessageBox::_KeyEnterPressed()
{
	_result = sd::AskMessageBox::ResultOK;
	sd::MessageBox::_KeyEnterPressed();
}

void sd::AskMessageBox::_KeyEscapePressed()
{
	_result = sd::AskMessageBox::ResultCancel;
	sd::MessageBox::_KeyEscapePressed();
}

//public
sd::AskMessageBox::AskMessageBox(const sf::String& windowname, const sf::String& text, sf::RenderWindow* parentwindow)
: sd::MessageBox::MessageBox(windowname, text, parentwindow)
{ _AdditionalInit(); }


//static
void sd::AskMessageBox::SetBaseButtonPicture(const sd::Picture& pic)
{
	sd::AskMessageBox::_basebuttonpic = pic;
}

//static
void sd::AskMessageBox::SetBaseFont(const sf::Font& font)
{
	sd::AskMessageBox::_basefont = font;
}





////////////////////
//ChooseMessageBox//
////////////////////

const int sd::ChooseMessageBox::ResultNull = -1;
const int sd::ChooseMessageBox::ResultYes = 1;
const int sd::ChooseMessageBox::ResultNo = 2;
const int sd::ChooseMessageBox::ResultCancel = 0;

sd::Picture sd::ChooseMessageBox::_basebuttonpic; //default button picture, if not given another
sf::Font sd::ChooseMessageBox::_basefont; //so font



void sd::ChooseMessageBox::_AdditionalInit()
{
	//call from sd::MessageBox and init buttons
	_buttons.clear();
	_buttons.push_back(sd::Button("Yes", sf::Vector2f(0, 0), _font, _basebuttonpic));
	_buttons.push_back(sd::Button("No", sf::Vector2f(0, 0), _font, _basebuttonpic));
	_buttons.push_back(sd::Button("Cancel", sf::Vector2f(0, 0), _font, _basebuttonpic));
}

void sd::ChooseMessageBox::_ButtonsInit()
{
	_buttons.at(0).SetPosition(sf::Vector2f(110, 115) - (_buttons.front().GetSize() / (float)2));
	_buttons.at(1).SetPosition(sf::Vector2f(250, 115) - (_buttons.front().GetSize() / (float)2));
	_buttons.at(2).SetPosition(sf::Vector2f(390, 115) - (_buttons.front().GetSize() / (float)2));
}

//checks what button pressed
sd::Action sd::ChooseMessageBox::_MouseReleasedTest(sf::Vector2f mouse)
{
	//set _result here
	for (unsigned int i = 0; i < _buttons.size(); i++)
		if(_buttons.at(i).ReleasedTest(mouse))
		{
			if (i == 0)
				_result = sd::ChooseMessageBox::ResultYes;
			if (i == 1)
				_result = sd::ChooseMessageBox::ResultNo;
			if (i == 2)
				_result = sd::ChooseMessageBox::ResultCancel;
			return sd::ActionButtonClicked;
		}
	return sd::ActionEmpty;
}

void sd::ChooseMessageBox::_KeyEnterPressed()
{
	_result = sd::ChooseMessageBox::ResultYes;
	sd::MessageBox::_KeyEnterPressed();
}

void sd::ChooseMessageBox::_KeyEscapePressed()
{
	_result = sd::ChooseMessageBox::ResultCancel;
	sd::MessageBox::_KeyEscapePressed();
}

//public
sd::ChooseMessageBox::ChooseMessageBox(const sf::String& windowname, const sf::String& text, sf::RenderWindow* parentwindow)
: sd::MessageBox::MessageBox(windowname, text, parentwindow)
{ _AdditionalInit(); }


//static
void sd::ChooseMessageBox::SetBaseButtonPicture(const sd::Picture& pic)
{
	sd::ChooseMessageBox::_basebuttonpic = pic;
}

//static
void sd::ChooseMessageBox::SetBaseFont(const sf::Font& font)
{
	sd::ChooseMessageBox::_basefont = font;
}
