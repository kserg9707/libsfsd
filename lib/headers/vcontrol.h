#ifndef VCONTROL_H
#define VCONTROL_H

#include <SFML/Graphics.hpp>

namespace sd
{
enum Type {empty, button, slide};

class Control
{
protected:
	sf::Vector2f _pos; //button center pos
	sf::Vector2f _size; //is it used?
	
	bool _enabled;
	bool _visible;
	
public:
	virtual Type GetType() const { return empty; }
	
	virtual sf::Vector2f GetPosition() const = 0;
	
	virtual void SetPosition(float x, float y) = 0;
	
	virtual void SetPosition(const sf::Vector2f& src) = 0;
	
	
	//size of background picture so size of button
	virtual sf::Vector2f GetSize() const = 0;
	
	virtual void SetSize(float x, float y) = 0;
	
	virtual void SetSize(sf::Vector2f size) = 0;
	
	
	virtual void Draw(sf::RenderWindow& targetwindow) = 0;
	
	
	virtual bool PressedTest(sf::Vector2f mousepos) { return false; }
	
	virtual bool DownTest(sf::Vector2f mousepos) { return false; }
	
	virtual bool ReleasedTest(sf::Vector2f mousepos) { return false; }
	
	
	virtual bool IsEnabled() = 0;
	
	virtual void SetEnabled(bool enabled) = 0;
	
	virtual bool IsVisible() = 0;
	
	virtual void SetVisible(bool visible) = 0;
};

}

#endif
