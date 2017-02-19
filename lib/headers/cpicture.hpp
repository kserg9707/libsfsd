#ifndef CPICTURE_H
#define CPICTURE_H

#include <SFML/Graphics.hpp>

namespace sd
{

class Picture
{
private:
	bool initok; //initialization completed
	
	sf::String _file; //filename
	sf::Image _image;
	sf::Texture _texture;
	sf::Sprite _sprite;
	
	sf::Vector2u _size; //size of texture
	sf::Vector2f _fsize; //size of one frame
	
	//load image from file. center origin, mask color if needed
	void _LoadImage(bool centrepivot, const sf::Color& maskclr, bool mask);
	
	void _SetImage(bool centrepivot, const sf::Color& maskclr, bool mask);
	
	//copy sprite to *this
	void _SetSprite(const sf::Image& srcimage, const sf::Texture& srctexture, const sf::Sprite& srcsprite);
public:
	//empty ctor, initok = false;
	Picture();
	
	//init
	Picture(const sf::String& file, const sf::Vector2f& fsize, bool setpivot = false);
	
	Picture(const sf::String& file, const sf::Vector2f& fsize, const sf::Color& maskclr, bool setpivot = false);
	
	Picture(const sf::Image& file, const sf::Vector2f& fsize, bool setpivot = false);
	
	Picture(const sf::Image& file, const sf::Vector2f& fsize, const sf::Color& maskclr, bool setpivot = false);
	
	Picture(const Picture& src);
	
	//for init after empty ctor
	Picture& operator = (const Picture& src);
	
	//same to sf::Sprite, simply calling it
	float GetRotation() const;
	
	void SetRotation(float rot);
	
	
	sf::Vector2f GetScale() const;
	
	void SetScale(float x, float y);
	
	void SetScale(const sf::Vector2f& src);
	
	
	sf::Vector2f GetOrigin() const;
	
	void SetOrigin(float x, float y);
	
	void SetOrigin(const sf::Vector2f& src);
	
	void CentreOrigin();
	
	
	sf::Color GetColor() const;
	
	void SetColor(const sf::Color& clr);
	
	
	//draw on coords with current transform to target window
	void Draw(float x, float y, sf::RenderWindow& targetwindow);
	
	void Draw(const sf::Vector2f& pos, sf::RenderWindow& targetwindow);
	
	//get frame size
	sf::Vector2f GetLocalSize() const;
	
	sf::Vector2f GetGlobalSize() const;
	
	void SetSize(float x, float y);
	
	void SetSize(sf::Vector2f size);
};

}

#endif
