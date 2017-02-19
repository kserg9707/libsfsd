#ifndef CBUTTON_H
#define CBUTTON_H

#include <SFML/Graphics.hpp>

#include "vcontrol.hpp"
#include "eaction.hpp"
#include "sglobal.hpp"
#include "cpicture.hpp"

//TODO: set button text

namespace sd
{

class Button : public Control
{
private:
	static sd::Picture _basepic; //default picture, if not given another
	static sf::Font _basefont; //so font
	
	bool _initok; //initialization completed
	bool _waspressed; //when mouse pressed
	bool _state; //when was pressed and mouse in button. need for result when released
	
	sf::String _str; //text on button
	sf::Text _text; //like sprite
	int _fontsize;
	
	//sf::Vector2f _pos; //button center pos
	//sf::Vector2f _size; //is it used?
	
	sf::Font _font; //font == basefont, if not set
	
	sd::Picture _bgpic; //so background picture
	
	sf::Color _pressedcolor; //sprite color when button pressed
	sf::Color _disabledcolor; //sprite color when button disabled
	sf::Color _disabledtextcolor;
	
	//bool _enabled;
	//bool _visible;
	
	
	void _Init();
	
	//takes coords of left top corner, but pivots set to centre. so need to move.
	void _PosFixOnSet();
	
	//same: returns coord of left top corner, _pos set to centre.
	sf::Vector2f _PosFixOnGet() const;
public:
	Type GetType() const;
	
	//empty ctor, initok = false;
	Button();
	
	//init
	Button(const sf::String& str, const sf::Vector2f& pos);

	Button(const sf::String& str, const sf::Vector2f& pos, const sf::Font& font, const sd::Picture& pic);
	
	Button(const Button& src);
	
	//for init after empty ctor
	Button& operator = (const Button& src);
	
	
	//init static vars. New vars applies to objects creted after setting it
	static void SetBasePicture(const sd::Picture& pic);
	
	static void SetBaseFont(const sf::Font& font);
	
	
	void SetPicture(sd::Picture pic, bool savesize = true);
	
	
	//sets var _pos. takes/returns coord of left top corner; _pos - centre of button
	sf::Vector2f GetPosition() const;
	
	void SetPosition(float x, float y);
	
	void SetPosition(const sf::Vector2f& src);
	
	
	//size of background picture so size of button
	sf::Vector2f GetSize() const;
	
	void SetSize(float x, float y);
	
	void SetSize(sf::Vector2f size);
	

	//draws bg, sets text position, draws text
	void Draw(sf::RenderWindow& targetwindow);
	
	
	//takes mouse position, called on events according to name.
	bool PressedTest(sf::Vector2f mousepos);
	
	bool DownTest(sf::Vector2f mousepos);
	
	bool ReleasedTest(sf::Vector2f mousepos);
	
	
	bool IsEnabled();
	
	void SetEnabled(bool enabled);
	
	bool IsVisible();
	
	void SetVisible(bool visible);
};

}

#endif
