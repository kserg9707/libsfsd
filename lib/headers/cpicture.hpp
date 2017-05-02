#ifndef CPICTURE_H
#define CPICTURE_H

//COMMIT: added frames to class Picture

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
	sf::Vector2i _frames; //frames count
	
	int _frame;
	bool _mirrored;
	
	
	void _FrameSizeCheck();
	
	//load image from file. center origin, mask color if needed
	void _LoadImage(bool centrepivot, const sf::Color& maskclr, bool mask);
	
	void _SetImage(bool centrepivot, const sf::Color& maskclr, bool mask);
	
	void _UpdateImage();

	//copy sprite to *this
	void _SetSprite(const sf::Sprite& srcsprite);

	void _SetSprite(const sf::Image& srcimage, const sf::Texture& srctexture, const sf::Sprite& srcsprite);
	
	//count number of frames
	void _CountFrames();
public:
	  //////////////////
	 // Constructors //
	//////////////////

	//not full init
	Picture();
	
	//full init
	Picture(const sf::String& file, const sf::Vector2f& fsize, bool setpivot = false);
	
	Picture(const sf::String& file, const sf::Vector2f& fsize, const sf::Color& maskclr, bool setpivot = false);
	
	Picture(const sf::Image& file, const sf::Vector2f& fsize, bool setpivot = false);
	
	Picture(const sf::Image& file, const sf::Vector2f& fsize, const sf::Color& maskclr, bool setpivot = false);
	
	Picture(const Picture& src);
	
	//for init after empty ctor
	Picture& operator = (const Picture& src);

	
	  ///////////////////
	 // Complete init //
	///////////////////
	//?????????????????????where???

	
	  /////////////////////
	 // Get/Set methods //
	/////////////////////
	
	// initok
	bool IsInit() const;

	// _image
	sf::Image GetImage() const;
	
	// _texture
	sf::Texture GetTexture() const;

	// _sprite
	//    rotation
	float GetRotation() const;
	
	void SetRotation(float rot);
	
	//    scale
	sf::Vector2f GetScale() const;
	
	void SetScale(float x, float y);
	
	void SetScale(const sf::Vector2f& src);
	
	//    size of a frame
	sf::Vector2f GetLocalSize() const;
	
	sf::Vector2f GetGlobalSize() const;
	
	void SetSize(float x, float y);
	
	void SetSize(sf::Vector2f size);
	
	//    pivot
	sf::Vector2f GetOrigin() const;
	
	void SetOrigin(float x, float y);
	
	void SetOrigin(const sf::Vector2f& src);
	
	void CentreOrigin();
	
	//    color
	sf::Color GetColor() const;
	
	void SetColor(const sf::Color& clr);
	
	
	  ///////////////////
	 // Other methods //
	///////////////////
	
	//draw on coords with current transform to target window
	void Draw(float x, float y, sf::RenderWindow& targetwindow);
	
	void Draw(const sf::Vector2f& pos, sf::RenderWindow& targetwindow);
	
	//draw with shader
	void Draw(float x, float y, sf::RenderWindow& targetwindow, sf::Shader* shader);
	
	void Draw(const sf::Vector2f& pos, sf::RenderWindow& targetwindow, sf::Shader* shader);
};

}

#endif
