#ifndef CSLIDE_H
#define CSLIDE_H

#include <SFML/Graphics.hpp>

#include "vcontrol.h"
#include "eaction.h"
#include "sbasevalues.h"
#include "cpicture.h"
#include "cbutton.h"

//TODO: set button text

namespace sd
{

class Slide : public Control
{
private:
	static sd::Picture _basepic; //default slide picture, if not given another
	static sd::Picture _basebuttonpic;
	
	bool _initok; //initialization completed
	sf::Vector2f _mousedelta;
	bool _waspressed; //when mouse pressed
	bool _state; //when was pressed and mouse in button. need for result when released
	int _value, _valuemin, _valuemax;
	
	//sf::Vector2f _pos; //slide left top pos
	//sf::Vector2f _size; //x - size.x of bgpic, y - size.y of button 
	
	sd::Picture _bgpic; //so background picture
	sd::Button _slidebutton;
	
	sf::Color _pressedcolor; //sprite color when button pressed
	sf::Color _disabledcolor; //sprite color when button disabled
	
	//bool _enabled;
	//bool _visible;
	
	
	void _Init();
	
	void _PicSet(const Picture pic);
	
	//takes coords of left top corner, but pivots set to centre. so need to move.
	void _PosSet(sf::Vector2f pos);
	
	void _UpdateValue();
	
	void _UpdateButton();
	
public:
	Type GetType() const;
	
	//empty ctor, initok = false;
	Slide();
	
	//init
	Slide(const sf::Vector2f& pos, const sf::Vector2f& size, int valuemin = 0, int valuemax = 100);
	
	Slide(const Slide& src);
	
	//for init after empty ctor
	Slide& operator = (const Slide& src);
	
	
	//init static vars. New vars applies to objects creted after setting it
	static void SetBasePicture(const sd::Picture& pic);
	
	static void SetBaseButtonPicture(const sd::Picture& pic);
	
	
	//sets var _pos. takes/returns coord of left top corner; _pos - centre of button
	sf::Vector2f GetPosition() const;
	
	void SetPosition(float x, float y);
	
	void SetPosition(const sf::Vector2f& src);
	
	
	//size of background picture so size of button
	sf::Vector2f GetSize() const;
	
	void SetSize(float x, float y);
	
	void SetSize(sf::Vector2f size);
	
	
	int GetValue() const;
	
	void SetValue(int value);
	

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
