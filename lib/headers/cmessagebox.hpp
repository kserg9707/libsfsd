#ifndef CMESSAGEBOX_H
#define CMESSAGEBOX_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "cpicture.hpp"
#include "cbutton.hpp"

//TODO: set own image for derived classes, font. mb set buttons text
namespace sd
{

class MessageBox
{
public:
	//message box result
	static const int ResultNull;
	/*static const MessageBoxResult ResultOK; //info, ask
	static const MessageBoxResult ResultCancel; //ask, choose
	static const MessageBoxResult ResultYes; //choose
	static const MessageBoxResult ResultNo; //choose*/
	
protected:
	static sd::Picture _basebuttonpic; //default button picture, if not given another
	static sf::Font _basefont; //so font
	
	sf::String _windowname;
	sf::String _windowtext;
	
	sf::RenderWindow* _parentwindow; //parent window to check focus
	
	sf::Font _font;
	int _fontsize;
	
	sf::Text _text; //message
	sf::Color _bgcolor; //color of window
	
	std::vector<sd::Button> _buttons;
	
	sf::RenderWindow* _msgwindow; //this window
	
	int _result; //mesage box result
	
	
	void _Init();
	
	virtual void _AdditionalInit() = 0;
	
	//init buttons, own in different message boxes
	virtual void _ButtonsInit();
	
	void _ButtonsDraw();
	
	//mouse test, returns ActionEmpty, except last
	Action _MousePressedTest(sf::Vector2f mouse);
	
	Action _MouseTest(sf::Vector2f mouse);
	
	//sets _result and returns ActionPuttonPressed if pressed
	virtual Action _MouseReleasedTest(sf::Vector2f mouse);
	
	//sets _result to 1
	virtual void _KeyEnterPressed();
	
	virtual void _KeyEscapePressed();
	
	//closes window
	void _Close(bool buttonclicked);
	
public:
	MessageBox();
	
	MessageBox(const sf::String& windowname, const sf::String& text, sf::RenderWindow* parentwindow);
	
	
	//sd::MessageBox sets all base pictures
	static void SetBaseButtonPicture(const sd::Picture& pic);
	
	//so this
	static void SetBaseFont(const sf::Font& font);
	
	
	//create window and etc.
	int Show();
};



class InfoMessageBox : public MessageBox
{
public:
	static const int ResultNull;
	static const int ResultOK; //info, ask
	
protected:
	static sd::Picture _basebuttonpic; //default button picture, if not given another
	static sf::Font _basefont; //so font
	
	
	void _AdditionalInit();

	void _ButtonsInit();
	
	//sets _result and returns ActionPuttonPressed if pressed
	Action _MouseReleasedTest(sf::Vector2f mouse);
	
	void _KeyEnterPressed();
	
	void _KeyEscapePressed();
	
public:
	InfoMessageBox();
	
	InfoMessageBox(const sf::String& windowname, const sf::String& text, sf::RenderWindow* parentwindow);
	
	
	static void SetBaseButtonPicture(const sd::Picture& pic);
	
	static void SetBaseFont(const sf::Font& font);
};



class AskMessageBox : public MessageBox
{
public:
	static const int ResultNull;
	static const int ResultOK;
	static const int ResultCancel;
	
protected:
	static sd::Picture _basebuttonpic; //default button picture, if not given another
	static sf::Font _basefont; //so font
	
	
	void _AdditionalInit();

	void _ButtonsInit();
	
	//sets _result and returns ActionPuttonPressed if pressed
	Action _MouseReleasedTest(sf::Vector2f mouse);
	
	void _KeyEnterPressed();
	
	void _KeyEscapePressed();
	
public:
	AskMessageBox();
	
	AskMessageBox(const sf::String& windowname, const sf::String& text, sf::RenderWindow* parentwindow);
	
	
	static void SetBaseButtonPicture(const sd::Picture& pic);
	
	static void SetBaseFont(const sf::Font& font);
};



class ChooseMessageBox : public MessageBox
{
public:
	static const int ResultNull;
	static const int ResultYes;
	static const int ResultNo;
	static const int ResultCancel;

protected:	
	static sd::Picture _basebuttonpic; //default button picture, if not given another
	static sf::Font _basefont; //so font
	
	
	void _AdditionalInit();

	void _ButtonsInit();
	
	//sets _result and returns ActionPuttonPressed if pressed
	Action _MouseReleasedTest(sf::Vector2f mouse);
	
	void _KeyEnterPressed();
	
	void _KeyEscapePressed();
	
public:
	ChooseMessageBox();
	
	ChooseMessageBox(const sf::String& windowname, const sf::String& text, sf::RenderWindow* parentwindow);
	
	
	static void SetBaseButtonPicture(const sd::Picture& pic);
	
	static void SetBaseFont(const sf::Font& font);
};

}

#endif
