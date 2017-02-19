#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "../headers/vcontrol.hpp"
#include "../headers/eaction.hpp"
#include "../headers/sglobal.hpp"
#include "../headers/cpicture.hpp"
#include "../headers/cbutton.hpp"
#include "../headers/cslide.hpp"

sd::Picture sd::Slide::_basepic;
sd::Picture sd::Slide::_basebuttonpic;


//init new object
void sd::Slide::_Init()
{
	_value = 0;
	
	_PicSet(_basepic);
	
	_pressedcolor = sd::Global::ColorPressedBase;
	_disabledcolor = sd::Global::ColorDisabledBase;

	SetEnabled(true);
	SetVisible(true);
	
	_waspressed = false;
	_state = false;
}

//set rail (background) picture
void sd::Slide::_PicSet(const sd::Picture pic)
{
	_bgpic = pic;
	_bgpic.SetSize(_size.x, _bgpic.GetLocalSize().y);
	_bgpic.SetOrigin(0, (int)(_bgpic.GetLocalSize().y / 2));
}

//set control position
void sd::Slide::_PosSet(sf::Vector2f pos)
{
	_pos = pos;
	_slidebutton.SetPosition(_pos);
}

//if value delta << slide size.x, round button position to nearest value
void sd::Slide::_UpdateValue()
{
	if (_size.x == 0)
		return;
	
	_value = round(((float)_slidebutton.GetPosition().x - _pos.x) / (_size.x - _slidebutton.GetSize().x) * (_valuemax - _valuemin) + _valuemin);
	//update button so it shows real value, not between
	_UpdateButton();
}

//place button according to value
void sd::Slide::_UpdateButton()
{
	if (_size.x == 0)
		return;
	
	_slidebutton.SetPosition(((float)_value - _valuemin) / (_valuemax - _valuemin) * (_size.x - _slidebutton.GetSize().x) + _pos.x, _slidebutton.GetPosition().y);
}




//public
sd::Type sd::Slide::GetType() const
{ return slide; }

sd::Slide::Slide()
{ _initok = false; }

//init
sd::Slide::Slide(const sf::Vector2f& pos, const sf::Vector2f& size, int valuemin, int valuemax)
{
	_Init();
	_size = size;
	_valuemin = valuemin;
	_valuemax = valuemax;
	
	_slidebutton = sd::Button("", _pos);
	_slidebutton.SetPicture(_basebuttonpic, false);
	_bgpic.SetSize(_size.x, _bgpic.GetLocalSize().y);
	
	_PosSet(pos);
	_initok = true;
}

sd::Slide::Slide(const sd::Slide& src)
{
}

//for init after empty ctor
sd::Slide& sd::Slide::operator = (const sd::Slide& src)
{
	_Init();
	_pressedcolor = src._pressedcolor;
	_disabledcolor = src._disabledcolor;
	
	_size = src._size;
	
	_value = src._value;
	_valuemin = src._valuemin;
	_valuemax = src._valuemax;
	
	SetEnabled(src._enabled);
	SetVisible(src._visible);
	
	_initok = src._initok;
	
	_PicSet(src._bgpic);
	_slidebutton = src._slidebutton;
	
	_PosSet(src._pos);
	
	return *this;
}


//init static vars. New vars applied to objects creted after setting it
void sd::Slide::SetBasePicture(const sd::Picture& pic)
{
	_basepic = pic;
}

//init static vars. New vars applied to objects creted after setting it
void sd::Slide::SetBaseButtonPicture(const sd::Picture& pic)
{
	_basebuttonpic = pic;
}


sf::Vector2f sd::Slide::GetPosition() const
{
	return _pos;
}

void sd::Slide::SetPosition(float x, float y)
{
	_pos = sf::Vector2f(x, y);
	_slidebutton.SetPosition(_pos);
}

void sd::Slide::SetPosition(const sf::Vector2f& src)
{
	_pos = src;
	_slidebutton.SetPosition(_pos); //TODO: is it right? mb need to call UpdateButton?
}


sf::Vector2f sd::Slide::GetSize() const
{ return _size; }

//TODO:
void sd::Slide::SetSize(float x, float y)
{}

void sd::Slide::SetSize(sf::Vector2f size)
{}


int sd::Slide::GetValue() const
{ return _value; }

void sd::Slide::SetValue(int value)
{
	_value = value;
	if (_value < _valuemin)
		_value = _valuemin;
	if (_value > _valuemax)
		_value = _valuemax;
	_UpdateButton();
}


//draws bg, sets text position, draws text
void sd::Slide::Draw(sf::RenderWindow& targetwindow)
{
	if (!_initok)
	{
		//log
		return;
	}
	if (_visible)
	{
		_bgpic.Draw(_pos.x, _pos.y + _slidebutton.GetSize().y/2, targetwindow);
		_slidebutton.Draw(targetwindow);
	}
}


bool sd::Slide::PressedTest(sf::Vector2f mousepos)
{
	if (_enabled && _visible)
	{
		if (_slidebutton.PressedTest(mousepos))
		{
			_mousedelta = mousepos - _slidebutton.GetPosition();
			_waspressed = true;
			_state = true;
		}
	}
	if (_state)
		return true;
	return false;
}

bool sd::Slide::DownTest(sf::Vector2f mousepos)
{
	if (_waspressed)
	{
		if (_enabled && _visible)
		{
			_slidebutton.DownTest(mousepos);
			sf::Vector2f newpos = mousepos-_mousedelta;
			newpos.y = _pos.y;//_slidebutton.GetPosition().y;
			if (newpos.x < _pos.x)
				newpos.x = _pos.x;
			if (newpos.x + _slidebutton.GetSize().x > _pos.x + _size.x)
				newpos.x = _pos.x + _size.x - _slidebutton.GetSize().x;
			_slidebutton.SetPosition(newpos);
			_UpdateValue();
		}
		else
		{
			_waspressed = false;
			_state = false;
		}
	}
	if (_state)
		return true;
	return false;
}

bool sd::Slide::ReleasedTest(sf::Vector2f mousepos)
{
	if (_waspressed)
	{
		_waspressed = false;
		if (_enabled && _visible)
		{
			_slidebutton.ReleasedTest(mousepos);
			if (_state)
			{
				_state = false;
				_UpdateValue();
				return true;
			}
		}
		else
		{
			_state = false;
		}
	}
	return false;
}


bool sd::Slide::IsEnabled()
{ return _enabled; }

void sd::Slide::SetEnabled(bool enabled)
{
	_enabled = enabled;
	if (_enabled)
	{
		_bgpic.SetColor(sf::Color::White);
	}
	else
	{
		_bgpic.SetColor(_disabledcolor);
	}
	_slidebutton.SetEnabled(_enabled);
}

bool sd::Slide::IsVisible()
{ return _visible; }

void sd::Slide::SetVisible(bool visible)
{
	_visible = visible;
	_slidebutton.SetEnabled(_visible);
}
