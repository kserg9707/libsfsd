#include <SFML/Graphics.hpp>

#include "../headers/cpicture.hpp"



//private
void sd::Picture::_FrameSizeCheck()
{
	if (_fsize.x <= 0 || _fsize.y <= 0 || _fsize.x > _size.x || _fsize.y > _size.y)
		_fsize = sf::Vector2f(_size.x, _size.y);
}

void sd::Picture::_LoadImage(bool centrepivot, const sf::Color& maskclr, bool mask)
{
	_image.loadFromFile("resources/images/" + _file);
	if (mask)
		_image.createMaskFromColor(maskclr);
	
	_UpdateImage();
	
	_texture.loadFromImage(_image);
	
	_sprite.setTexture(_texture);
	_sprite.setTextureRect(sf::IntRect(0, 0, _fsize.x, _fsize.y));
	if (centrepivot)
		_sprite.setOrigin(_fsize.x / 2, _fsize.y / 2);
}

void sd::Picture::_SetImage(bool centrepivot, const sf::Color& maskclr, bool mask)
{
	if (mask)
		_image.createMaskFromColor(maskclr);
	
	_UpdateImage();
	
	_texture.loadFromImage(_image);
	
	_sprite.setTexture(_texture);
	_sprite.setTextureRect(sf::IntRect(0, 0, _fsize.x, _fsize.y));
	if (centrepivot)
		_sprite.setOrigin(_fsize.x / 2, _fsize.y / 2);
}

void sd::Picture::_UpdateImage()
{
	_size = _image.getSize();
	_FrameSizeCheck();
	
	_CountFrames();
}

void sd::Picture::_SetSprite(const sf::Sprite& src)
{
	if (src.getTexture() == NULL)
		return;
	_image = src.getTexture()->copyToImage();
	_UpdateImage();
	_CountFrames();
	_texture.loadFromImage(_image);
	_texture.setSmooth(src.getTexture()->isSmooth());
	_sprite.setTexture(_texture);
	_sprite.setTextureRect(src.getTextureRect());
	_sprite.setOrigin(src.getOrigin());
	_sprite.setPosition(src.getPosition());
	_sprite.setRotation(src.getRotation());
	_sprite.setScale(src.getScale());
	_sprite.setColor(src.getColor());
}

void sd::Picture::_SetSprite(const sf::Image& srcimage, const sf::Texture& srctexture, const sf::Sprite& srcsprite)
{
	_image = srcimage;
	_UpdateImage();
	_CountFrames();
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

//count number of frames
void sd::Picture::_CountFrames()
{
	_frames.x = _size.x / _fsize.x;
	_frames.y = _size.y / _fsize.y;
	//if (_framws
}

void sd::Picture::_CheckFrame()
{
	//TODO: below zero doesn't work
	if (_frame.x >= _frames.x || _frame.x < 0)
		_frame.x %= _frames.x;
	if (_frame.y >= _frames.y || _frame.y < 0)
		_frame.y %= _frames.y;
}

void sd::Picture::_UpdateFrame()
{
	sf::IntRect f(_frame.x * _fsize.x, _frame.y * _fsize.y, (int)_fsize.x, (int)_fsize.y);
	if (_mirrored)
	{
		f.left += _fsize.x;
		f.width = -f.width;
	}
	_sprite.setTextureRect(f);
}


//public
  //////////////////
 // Constructors //
//////////////////

//not full init
sd::Picture::Picture()
{
	_frame = sf::Vector2i();
	_mirrored = false;
	initok = false;
}

sd::Picture::Picture(const sf::String& file, const sf::Vector2f& fsize, bool setpivot)
: _file(file), _fsize(fsize)
{
	_frame = sf::Vector2i();
	_mirrored = false;
	_LoadImage(setpivot, sf::Color::White, false);
	initok = true;
}

sd::Picture::Picture(const sf::String& file, const sf::Vector2f& fsize, const sf::Color& maskclr, bool setpivot)
: _file(file), _fsize(fsize)
{
	_frame = sf::Vector2i();
	_mirrored = false;
	_LoadImage(setpivot, maskclr, true);
	initok = true;
}

sd::Picture::Picture(const sf::Image& image, const sf::Vector2f& fsize, bool setpivot)
: _image(image), _fsize(fsize)
{
	_file = "";
	_frame = sf::Vector2i();
	_mirrored = false;
	_SetImage(setpivot, sf::Color::White, false);
	initok = true;
}

sd::Picture::Picture(const sf::Image& image, const sf::Vector2f& fsize, const sf::Color& maskclr, bool setpivot)
: _image(image), _fsize(fsize)
{
	_file = "";
	_frame = sf::Vector2i();
	_mirrored = false;
	_SetImage(setpivot, maskclr, true);
	initok = true;
}

sd::Picture::Picture(const sd::Picture& src)
: _file(src._file), _size(src._size), _fsize(src._fsize), _frame(src._frame), _mirrored(src._mirrored)
{
//	if (src.initok)
	//_SetSprite(src._image, src._texture, src._sprite);
	_SetSprite(src._sprite);
	initok = src.initok;
}

sd::Picture& sd::Picture::operator = (const Picture& src)
{
	_size = src._size;
	_fsize = src._fsize;
	_file = src._file;
	_frame = src._frame;
	_mirrored = src._mirrored;
	//_SetSprite(src._image, src._texture, src._sprite);
	_SetSprite(src._sprite);
	initok = src.initok;
	return *this;
}


bool sd::Picture::IsInit() const
{ return initok; }


sf::Image sd::Picture::GetImage() const
{ return _image; }

sf::Texture sd::Picture::GetTexture() const
{ return _texture; }


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


// _frames
int sd::Picture::FramesCount() const
{ return _frames.x * _frames.y; }

sf::Vector2i sd::Picture::FramesCountCoord() const
{ return _frames; }

// _frame
int sd::Picture::GetFrame() const
{ return _frame.y * _frames.x + _frame.x; }

sf::Vector2i sd::Picture::GetFrameCoord() const //return _frame
{ return _frame; }

void sd::Picture::SetFrame(int frame, bool mirrored)
{
	if (_frames.y == 0)
		SetFrameCoord(sf::Vector2i(), mirrored);
	else if (_frames.y == 1)
		SetFrameCoord(sf::Vector2i(frame, 0), mirrored);
	else
		SetFrameCoord(sf::Vector2i(frame % _frames.x, frame / _frames.x), mirrored);
}

void sd::Picture::SetFrame(const sf::Vector2i& frame, bool mirrored)
{
	SetFrameCoord(frame, mirrored);
}

void sd::Picture::SetFrame(int x, int y, bool mirrored) //same but another name ('cause Get)
{
	SetFrameCoord(sf::Vector2i(x, y), mirrored);
}

void sd::Picture::SetFrameCoord(const sf::Vector2i& frame, bool mirrored) //same but another name ('cause Get)
{
	_frame = frame;
	_CheckFrame();
	_mirrored = mirrored;
	_UpdateFrame();
}



void sd::Picture::Draw(float x, float y, sf::RenderWindow& targetwindow)
{
	if (!initok)
	{ return; }
	_sprite.setPosition(x,y);
	targetwindow.draw(_sprite);
}

void sd::Picture::Draw(const sf::Vector2f& pos, sf::RenderWindow& targetwindow)
{
	if (!initok)
	{ return; }
	Draw(pos.x, pos.y, targetwindow);
}

void sd::Picture::Draw(float x, float y, sf::RenderWindow& targetwindow, sf::Shader* shader)
{
	if (!initok)
	{ return; }
	_sprite.setPosition(x,y);
	targetwindow.draw(_sprite, shader);
}

void sd::Picture::Draw(const sf::Vector2f& pos, sf::RenderWindow& targetwindow, sf::Shader* shader)
{
	if (!initok)
	{ return; }
	Draw(pos.x, pos.y, targetwindow, shader);
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
