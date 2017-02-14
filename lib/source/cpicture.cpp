#include <SFML/Graphics.hpp>

#include "../headers/cpicture.h"



//private
void sd::Picture::_LoadImage(bool centrepivot, const sf::Color& maskclr, bool mask)
{
	_image.loadFromFile("resources/images/" + _file);
	if (mask)
		_image.createMaskFromColor(maskclr);
	
	_size = _image.getSize();
	if (_fsize.x <= 0 || _fsize.y <= 0)
		_fsize = sf::Vector2f(_size.x, _size.y);
	
	_texture.loadFromImage(_image);
	
	_sprite.setTexture(_texture);
	_sprite.setTextureRect(sf::IntRect(0, 0, _fsize.x, _fsize.y));
	if (centrepivot)
		_sprite.setOrigin(_fsize.x / 2, _fsize.y / 2);
}

void sd::Picture::_SetSprite(const sf::Image& srcimage, const sf::Texture& srctexture, const sf::Sprite& srcsprite)
{
	_image = srcimage;
	_texture = srctexture;
	_texture.setSmooth(true);
	_sprite.setTexture(_texture);
	_sprite.setTextureRect(srcsprite.getTextureRect());
	_sprite.setOrigin(srcsprite.getOrigin());
	_sprite.setPosition(srcsprite.getPosition());
	_sprite.setRotation(srcsprite.getRotation());
	_sprite.setScale(srcsprite.getScale());
	_sprite.setColor(srcsprite.getColor());
}


//public
sd::Picture::Picture()
{initok = false;}

sd::Picture::Picture(const sf::String& file, const sf::Vector2f& fsize, bool setpivot)
: _file(file), _fsize(fsize)
{
	_LoadImage(setpivot, sf::Color::White, false);
	initok = true;
}

sd::Picture::Picture(const sf::String& file, const sf::Vector2f& fsize, const sf::Color& maskclr, bool setpivot)
: _file(file), _fsize(fsize)
{
	_LoadImage(setpivot, maskclr, true);
	initok = true;
}

sd::Picture::Picture(const sd::Picture& src)
{
	_size = src._size;
	_fsize = src._fsize;
	_file = src._file;
	_SetSprite(src._image, src._texture, src._sprite);
	initok = true;
}

sd::Picture& sd::Picture::operator = (const Picture& src)
{
	if (!src.initok)
	{
		//log
		return *this;
	}
	_size = src._size;
	_fsize = src._fsize;
	_file = src._file;
	_SetSprite(src._image, src._texture, src._sprite);
	initok = true;
	return *this;
}

float sd::Picture::GetRotation() const
{ return _sprite.getRotation(); }

void sd::Picture::SetRotation(float rot)
{ _sprite.setRotation(rot); }


sf::Vector2f sd::Picture::GetScale() const
{ return _sprite.getScale(); }

void sd::Picture::SetScale(float x, float y)
{ _sprite.setScale(x,y); }

void sd::Picture::SetScale(const sf::Vector2f& src)
{ _sprite.setScale(src); }


sf::Vector2f sd::Picture::GetOrigin() const
{ return _sprite.getOrigin(); }

void sd::Picture::SetOrigin(float x, float y)
{ _sprite.setOrigin(x,y); }

void sd::Picture::SetOrigin(const sf::Vector2f& src)
{ _sprite.setOrigin(src); }

void sd::Picture::CentreOrigin()
{ _sprite.setOrigin(_fsize.x/2, _fsize.y/2); }


sf::Color sd::Picture::GetColor() const
{ return _sprite.getColor(); }

void sd::Picture::SetColor(const sf::Color& clr)
{ _sprite.setColor(clr); }

void sd::Picture::Draw(float x, float y, sf::RenderWindow& targetwindow)
{
	if (!initok)
	{
		//log
		return;
	}
	_sprite.setPosition(x,y);
	targetwindow.draw(_sprite);
}

void sd::Picture::Draw(const sf::Vector2f& pos, sf::RenderWindow& targetwindow)
{
	if (!initok)
	{
		//log
		return;
	}
	Draw(pos.x, pos.y, targetwindow);
}

sf::Vector2f sd::Picture::GetLocalSize() const
{
	return _fsize;
}

sf::Vector2f sd::Picture::GetGlobalSize() const
{
	sf::Vector2f scale = GetScale();
	sf::Vector2f ret = sf::Vector2f(_fsize.x * scale.x, _fsize.y * scale.y);
	return ret;
}

void sd::Picture::SetSize(float x, float y)
{
	float multx = 0, multy = 0;
	multx = x / _fsize.x;
	multy = y / _fsize.y;
	SetScale(multx, multy);
}

void sd::Picture::SetSize(sf::Vector2f size)
{
	float multx = 0, multy = 0;
	multx = size.x / _fsize.x;
	multy = size.y / _fsize.y;
	SetScale(multx, multy);
}
