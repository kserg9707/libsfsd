#include <SFML/Graphics.hpp>

#include "../headers/vcontrol.hpp"
#include "../headers/eaction.hpp"
#include "../headers/sglobal.hpp"
#include "../headers/cpicture.hpp"
#include "../headers/cbutton.hpp"

//static vars
sd::Picture sd::Button::_basepic;
sf::Font sd::Button::_basefont;

void sd::Button::_Init()
{
	//no pic = basepic cause one of ctors; so font
	_pressedcolor = sd::Global::ColorPressedBase;
	_disabledcolor = sd::Global::ColorDisabledBase;
	_disabledtextcolor = sd::Global::ColorDisabledText;
	
	//size like that for now
	_fontsize = 14;
	
	SetEnabled(true);
	SetVisible(true);
}

void sd::Button::_PosFixOnSet()
{
	//_pos is centre, outside class - coords of left top corner
	_pos += _bgpic.GetGlobalSize() / (float)2;
	_pos = sf::Vector2f((int)(_pos.x), (int)(_pos.y));
}

sf::Vector2f sd::Button::_PosFixOnGet() const
{
	//same
	return (_pos - (_bgpic.GetGlobalSize() / (float)2));
}



sd::Type sd::Button::GetType() const
{ return button; }

sd::Button::Button()
{_initok = false;}

sd::Button::Button(const sf::String& str, const sf::Vector2f& pos)
: _str(str)
{
	_Init();
	_pos = pos;
	_bgpic = _basepic;
	_font = _basefont;
	_text = sf::Text(str, _font, _fontsize);
	_text.setColor(sf::Color::Black);
	//_text.setStyle(sf::Text::Bold);// | sf::Text::Underlined);
	sf::Vector2f textsize(_text.getLocalBounds().width, _text.getLocalBounds().height);
	_text.setOrigin((int)(textsize.x / 2), (int)(textsize.y / 2) + 3);
	
	_bgpic.CentreOrigin();
	_PosFixOnSet();
	
	_initok = true;
}

sd::Button::Button(const sf::String& str, const sf::Vector2f& pos,
const sf::Font& font, const sd::Picture& pic)
: _str(str), _font(font), _bgpic(pic)
{
	_Init();
	_pos = pos;
	_text = sf::Text(str, _font, _fontsize);
	_text.setColor(sf::Color::Black);
	//_text.setStyle(sf::Text::Bold);// | sf::Text::Underlined);
	sf::Vector2f textsize(_text.getLocalBounds().width, _text.getLocalBounds().height);
	_text.setOrigin((int)(textsize.x / 2), (int)(textsize.y / 2) + 3);
	
	_bgpic.CentreOrigin();
	_PosFixOnSet();
	
	_initok = true;
}

sd::Button::Button(const sd::Button& src)
: _str(src._str), _font(src._font), _bgpic(src._bgpic)
{
	_Init();
	_pos = src._pos;
	_text = sf::Text(_str, _font, _fontsize);
	_text.setColor(sf::Color::Black);
	//_text.setStyle(sf::Text::Bold);// | sf::Text::Underlined);
	sf::Vector2f textsize(_text.getLocalBounds().width, _text.getLocalBounds().height);
	_text.setOrigin((int)(textsize.x / 2), (int)(textsize.y / 2) + 3);
	
	_bgpic.CentreOrigin();
	_PosFixOnSet();
	
	_initok = true;
}

sd::Button& sd::Button::operator = (const sd::Button& src)
{
	_Init();
	_str = src._str;
	_pos = src._pos;
	_bgpic = src._bgpic;
	_font = src._font;
	
	_text = sf::Text(_str, _font, _fontsize);
	_text.setColor(sf::Color::Black);
	//_text.setStyle(sf::Text::Bold);// | sf::Text::Underlined);
	sf::Vector2f textsize(_text.getLocalBounds().width, _text.getLocalBounds().height);
	//int (in setpos too) to avoid blur with float coords
	_text.setOrigin((int)(textsize.x / 2), (int)(textsize.y / 2) + 3);
	
	_bgpic.CentreOrigin();
	_PosFixOnSet();
	
	_initok = true;
	
	return *this;
}


//static
void sd::Button::SetBasePicture(const sd::Picture& pic)
{
	_basepic = pic;
}

//static
void sd::Button::SetBaseFont(const sf::Font& font)
{
	_basefont = font;
}


//TODO: correct pic size according to _size (do this too) and then put to _bgpic
void sd::Button::SetPicture(sd::Picture pic, bool savesize)
{
	_bgpic = pic;
}


sf::Vector2f sd::Button::GetPosition() const
{
	return _PosFixOnGet();
}

void sd::Button::SetPosition(float x, float y)
{
	_pos = sf::Vector2f(x, y);
	_PosFixOnSet();
}

void sd::Button::SetPosition(const sf::Vector2f& src)
{
	_pos = src;
	_PosFixOnSet();
}


sf::Vector2f sd::Button::GetSize() const
{
	sf::Vector2f ret = _bgpic.GetGlobalSize();
	return ret;
}

void sd::Button::SetSize(float x, float y)
{
	float multx = 0, multy = 0;
	multx = x / _bgpic.GetLocalSize().x;
	multy = y / _bgpic.GetLocalSize().y;
	//_text.SetScale(multx, multy);
	_bgpic.SetScale(multx, multy);
}

void sd::Button::SetSize(sf::Vector2f size)
{
	float multx = 0, multy = 0;
	multx = size.x / _bgpic.GetLocalSize().x;
	multy = size.y / _bgpic.GetLocalSize().y;
	//_text.SetScale(multx, multy);
	_bgpic.SetScale(multx, multy);
}


void sd::Button::Draw(sf::RenderWindow& targetwindow)
{
	if (!_initok)
	{
		//log
		return;
	}
	if (_visible)
	{
		_bgpic.Draw(_pos, targetwindow);
		_text.setPosition(_pos);
		targetwindow.draw(_text);
	}
}


bool sd::Button::PressedTest(sf::Vector2f mousepos)
{
	if (_enabled && _visible)
	{
		if (mousepos.x >= _PosFixOnGet().x && mousepos.x < _PosFixOnGet().x + GetSize().x
		&& mousepos.y >= _PosFixOnGet().y && mousepos.y < _PosFixOnGet().y + GetSize().y)
		{
			_waspressed = true;
			_state = true;
			_bgpic.SetColor(_pressedcolor);
		}
	}
	if (_state)
		return true;
	return false;
}

bool sd::Button::DownTest(sf::Vector2f mousepos)
{
	if (_waspressed)
	{
		if (_enabled && _visible)
		{
			if (mousepos.x >= _PosFixOnGet().x && mousepos.x < _PosFixOnGet().x + GetSize().x
			&& mousepos.y >= _PosFixOnGet().y && mousepos.y < _PosFixOnGet().y + GetSize().y)
			{
				if (!_state)
				{
					_state = true;
					_bgpic.SetColor(_pressedcolor);
				}
			}
			else
			{
				if (_state)
				{
					_state = false;
					_bgpic.SetColor(sf::Color::White);
				}
			}
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

bool sd::Button::ReleasedTest(sf::Vector2f mousepos)
{
	if (_waspressed)
	{
		_waspressed = false;
		if (_enabled && _visible)
		{
			_bgpic.SetColor(sf::Color::White);
			if (_state)
			{
				_state = false;
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


bool sd::Button::IsEnabled()
{ return _enabled; }

void sd::Button::SetEnabled(bool enabled)
{
	_enabled = enabled;
	if (_enabled)
	{
		_bgpic.SetColor(sf::Color::White);
		_text.setColor(sf::Color::Black);
	}
	else
	{
		_bgpic.SetColor(_disabledcolor);
		_text.setColor(_disabledtextcolor);
	}
}

bool sd::Button::IsVisible()
{ return _visible; }

void sd::Button::SetVisible(bool visible)
{ _visible = visible; }
