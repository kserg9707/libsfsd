#include <SFML/Graphics.hpp>

#include "../headers/vcontrol.hpp"
#include "../headers/eaction.hpp"
#include "../headers/sglobal.hpp"
#include "../headers/cpicture.hpp"
#include "../headers/cradiobutton.hpp"

//static vars
sd::Picture sd::RadioButton::_basepicoff;
sd::Picture sd::RadioButton::_basepicon;
sf::Font sd::RadioButton::_basefont;

void sd::RadioButton::_Init()
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

void sd::RadioButton::_PosFixOnSet()
{
	//_pos is centre, outside class - coords of left top corner
	_pos += _bgpicoff.GetGlobalSize() / (float)2;
	_pos = sf::Vector2f((int)(_pos.x), (int)(_pos.y));
}

sf::Vector2f sd::RadioButton::_PosFixOnGet() const
{
	//same
	return (_pos - (_bgpicoff.GetGlobalSize() / (float)2));
}



sd::Control::Type sd::RadioButton::GetType() const
{ return button; }

sd::RadioButton::RadioButton()
{_initok = false;}

sd::RadioButton::RadioButton(const sf::String& str, const sf::Vector2f& pos)
: _str(str)
{
	_Init();
	_pos = pos;
	_bgpicoff = _basepicoff;
	_bgpicon = _basepicon;
	_font = _basefont;
	_text = sf::Text(str, _font, _fontsize);
	_text.setColor(sf::Color::Black);
	//_text.setStyle(sf::Text::Bold);// | sf::Text::Underlined);
	sf::Vector2f textsize(_text.getLocalBounds().width, _text.getLocalBounds().height);
	_text.setOrigin((int)(textsize.x / 2), (int)(textsize.y / 2) + 3);
	
	_bgpicoff.CentreOrigin();
	_bgpicon.CentreOrigin();
	_PosFixOnSet();
	
	_initok = true;
}

sd::RadioButton::RadioButton(const sf::String& str, const sf::Vector2f& pos,
const sf::Font& font, const sd::Picture& picoff, const sd::Picture& picon)
: _str(str), _font(font), _bgpicoff(picoff), _bgpicon(picon)
{
	_Init();
	_pos = pos;
	_text = sf::Text(str, _font, _fontsize);
	_text.setColor(sf::Color::Black);
	//_text.setStyle(sf::Text::Bold);// | sf::Text::Underlined);
	sf::Vector2f textsize(_text.getLocalBounds().width, _text.getLocalBounds().height);
	_text.setOrigin((int)(textsize.x / 2), (int)(textsize.y / 2) + 3);
	
	_bgpicoff.CentreOrigin();
	_bgpicon.CentreOrigin();
	_PosFixOnSet();
	
	_initok = true;
}

sd::RadioButton::RadioButton(const sd::RadioButton& src)
: _str(src._str), _font(src._font), _bgpicoff(src._bgpicoff), _bgpicon(src._bgpicon)
{
	_Init();
	_pos = src._pos;
	_text = sf::Text(_str, _font, _fontsize);
	_text.setColor(sf::Color::Black);
	//_text.setStyle(sf::Text::Bold);// | sf::Text::Underlined);
	sf::Vector2f textsize(_text.getLocalBounds().width, _text.getLocalBounds().height);
	_text.setOrigin((int)(textsize.x / 2), (int)(textsize.y / 2) + 3);
	
	_bgpicoff.CentreOrigin();
	_bgpicon.CentreOrigin();
	_PosFixOnSet();
	
	_initok = true;
}

sd::RadioButton& sd::RadioButton::operator = (const sd::RadioButton& src)
{
	_Init();
	_str = src._str;
	_pos = src._pos;
	_bgpicoff = src._bgpicoff;
	_bgpicon = src._bgpicon;
	_font = src._font;
	
	_text = sf::Text(_str, _font, _fontsize);
	_text.setColor(sf::Color::Black);
	//_text.setStyle(sf::Text::Bold);// | sf::Text::Underlined);
	sf::Vector2f textsize(_text.getLocalBounds().width, _text.getLocalBounds().height);
	//int (in setpos too) to avoid blur with float coords
	_text.setOrigin((int)(textsize.x / 2), (int)(textsize.y / 2) + 3);
	
	_bgpicoff.CentreOrigin();
	_bgpicon.CentreOrigin();
	_PosFixOnSet();
	
	_initok = true;
	
	return *this;
}


//static
void sd::RadioButton::SetBaseOffPicture(const sd::Picture& pic)
{
	_basepicoff = pic;
}
void sd::RadioButton::SetBaseOnPicture(const sd::Picture& pic)
{
	_basepicon = pic;
}

//static
void sd::RadioButton::SetBaseFont(const sf::Font& font)
{
	_basefont = font;
}


//TODO: correct pic size according to _size (do this too) and then put to _bgpic
void sd::RadioButton::SetOffPicture(sd::Picture pic, bool savesize)
{
	_bgpicoff = pic;
}
void sd::RadioButton::SetOnPicture(sd::Picture pic, bool savesize)
{
	_bgpicon = pic;
}


sf::Vector2f sd::RadioButton::GetPosition() const
{
	return _PosFixOnGet();
}

void sd::RadioButton::SetPosition(float x, float y)
{
	_pos = sf::Vector2f(x, y);
	_PosFixOnSet();
}

void sd::RadioButton::SetPosition(const sf::Vector2f& src)
{
	_pos = src;
	_PosFixOnSet();
}


sf::Vector2f sd::RadioButton::GetSize() const
{
	sf::Vector2f ret = _bgpicoff.GetGlobalSize();
	return ret;
}

void sd::RadioButton::SetSize(float x, float y)
{
	float multx = 0, multy = 0;
	multx = x / _bgpicoff.GetLocalSize().x;
	multy = y / _bgpicoff.GetLocalSize().y;
	//_text.SetScale(multx, multy);
	_bgpicoff.SetScale(multx, multy);
	multx = x / _bgpicon.GetLocalSize().x;
	multy = y / _bgpicon.GetLocalSize().y;
	_bgpicon.SetScale(multx, multy);
}

void sd::RadioButton::SetSize(sf::Vector2f size)
{
	SetSize(size.x, size.y);
}


void sd::RadioButton::Draw(sf::RenderWindow& targetwindow)
{
	if (!_initok)
	{
		//log
		return;
	}
	if (_visible)
	{
		//TODO
		_bgpicoff.Draw(_pos, targetwindow);
		_bgpicon.Draw(_pos, targetwindow);
		_text.setPosition(_pos);
		targetwindow.draw(_text);
	}
}


bool sd::RadioButton::PressedTest(sf::Vector2f mousepos)
{
	if (_enabled && _visible)
	{
		if (mousepos.x >= _PosFixOnGet().x && mousepos.x < _PosFixOnGet().x + GetSize().x
		&& mousepos.y >= _PosFixOnGet().y && mousepos.y < _PosFixOnGet().y + GetSize().y)
		{
			_waspressed = true;
			_state = true;
			_bgpicoff.SetColor(_pressedcolor);
			_bgpicon.SetColor(_pressedcolor);
		}
	}
	if (_state)
		return true;
	return false;
}

bool sd::RadioButton::DownTest(sf::Vector2f mousepos)
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
					_bgpicoff.SetColor(_pressedcolor);
					_bgpicon.SetColor(_pressedcolor);
				}
			}
			else
			{
				if (_state)
				{
					_state = false;
					_bgpicoff.SetColor(sf::Color::White);
					_bgpicon.SetColor(sf::Color::White);
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

bool sd::RadioButton::ReleasedTest(sf::Vector2f mousepos)
{
	if (_waspressed)
	{
		_waspressed = false;
		if (_enabled && _visible)
		{
			_bgpicoff.SetColor(sf::Color::White);
			_bgpicon.SetColor(sf::Color::White);
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


bool sd::RadioButton::IsEnabled()
{ return _enabled; }

void sd::RadioButton::SetEnabled(bool enabled)
{
	_enabled = enabled;
	if (_enabled)
	{
		_bgpicoff.SetColor(sf::Color::White);
		_bgpicon.SetColor(sf::Color::White);
		_text.setColor(sf::Color::Black);
	}
	else
	{
		_bgpicoff.SetColor(_disabledcolor);
		_bgpicon.SetColor(_disabledcolor);
		_text.setColor(_disabledtextcolor);
	}
}

bool sd::RadioButton::IsVisible()
{ return _visible; }

void sd::RadioButton::SetVisible(bool visible)
{ _visible = visible; }
