#ifndef CGLYPHTEXT_H
#define CGLYPHTEXT_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

namespace sd
{

class GlyphText
{
private:
	//sf::String _str; //text on button
	std::string _str;
	sf::Font _font;
	int _fontsize;
	//sf::Texture _fonttexture; cause Font returns const Texture&
	//const sf::Texture& ft = fontsans.getTexture(14);
	sf::Glyph _glyph; // = fontsans.getGlyph('Q', 14, false); //will keep glyph when drawing
	sf::Sprite _sprite; //sprite for glyph
	
	bool FIRST;
	
	void _Init()
	{}
	
	void _UpdateSprite()
	{
		_sprite.setTexture(_font.getTexture(_fontsize));
		_sprite.setColor(sf::Color::Black);
	}
public:
	GlyphText()
	{}
	
	GlyphText(const std::string& str, const sf::Font& font, int fontsize)
	: _str(str), _font(font), _fontsize(fontsize)
	{
		_UpdateSprite();
	}
	
	void SetFont(const sf::Font font)
	{
		_font = font;
		_UpdateSprite();
	}
	
	void Draw(float x, float y, sf::RenderWindow& targetwindow)
	{
		int curx = x, cury = y;
		for (unsigned int i = 0; i < _str.length(); i++)
		{
			_glyph = _font.getGlyph(_str.at(i), _fontsize, false);
			if (_str.at(i) == '\n')
			{
				curx = x;
				cury += _font.getLineSpacing(_fontsize);
				continue;
			}
			_sprite.setTextureRect(_glyph.textureRect);
			_sprite.setPosition(curx + _glyph.bounds.left, cury + _glyph.bounds.top);
			targetwindow.draw(_sprite);
			curx += _glyph.advance;
		}
	}
	
	void Draw(const sf::Vector2f& pos, sf::RenderWindow& targetwindow)
	{
		Draw(pos.x, pos.y, targetwindow);
	}
};

}

#endif
