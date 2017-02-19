# libsfsd
controls for UI based on **SFML** lib.

#### Currently released controls:
* Button
* Slide
* Message box

#### Additional classes:
* sd::Global (static methods and variables)
* sd::Picture (keeps all of sf::Image, sf::Texture and sf::Sprite)
* sd::Control (base class for controls)

#### enums:
* sd::Action
  * sd::ActionEmpty
  * sd::ActionClose
  * sd::ActionButtonClicked

### TODO:
- [X] Base class for controls
- [ ] More virtual methods in base class
- [ ] Checkbox
- [ ] Radio button
- [ ] Progress bar
- [ ] Scroll
- [ ] List

##### Compiling program which is using sfsd:
```bash
g++ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfsd main.cpp -o main
```

### Usage example:
```c++
#include <iostream>
#include <cstdlib>
#include <vector>

#include <SFML/Graphics.hpp>
#include <sfsd/controls.hpp>

sd::Action MousePressedTest(sf::Vector2f mouse);
sd::Action MouseReleasedTest(sf::Vector2f mouse);

sf::RenderWindow* mainwindow;
std::vector<sd::Control*> controls;

void Init(char** env)
{
	sd::Global::Init(env);
	
	mainwindow = new sf::RenderWindow(sf::VideoMode(800,600), "sfsd test", sf::Style::Close | sf::Style::Titlebar);
	mainwindow->setVerticalSyncEnabled(true);
}

void UnInit()
{
	delete mainwindow;
}

sd::Action KeyTest(sf::Event event)
{
	return sd::ActionEmpty;
}

sd::Action MouseTest(sf::Event event, sf::Vector2f mouse)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		return MousePressedTest(mouse);
	if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		return MouseReleasedTest(mouse);
	return sd::ActionEmpty;
}

sd::Action MousePressedTest(sf::Vector2f mouse)
{
	//check if any pressed
	for (unsigned int i = 0; i < controls.size(); i++)
		controls.at(i)->PressedTest(mouse);
	return sd::ActionEmpty;
}

sd::Action MouseDownTest(sf::Vector2f mouse)
{
	for (unsigned int i = 0; i < controls.size(); i++)
		controls.at(i)->DownTest(mouse);
	return sd::ActionEmpty;
}

sd::Action MouseReleasedTest(sf::Vector2f mouse)
{
	if (controls.at(0)->ReleasedTest(mouse))
		return sd::ActionClose;
	return sd::ActionEmpty;
}

void Draw()
{
	for (unsigned int i = 0; i < controls.size(); i++)
		controls.at(i)->Draw(*mainwindow);
}

int main(int argc, char* argv[], char* env[])
{
	Init(env);
	
	sf::RenderWindow& window = *mainwindow;
	
	sd::Button buttonquit("Quit", sf::Vector2f(5,5));
	controls.push_back(&buttonquit);
	
	sf::Clock fpstimer;
	
	float frametime = 0;
	while (window.isOpen())
	{
		sf::Vector2i mousewindowpos = sf::Mouse::getPosition(window);
		sf::Vector2f mouseglobalpos = window.mapPixelToCoords(mousewindowpos);
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			sd::Action action = sd::ActionEmpty;
			
			if (event.type == sf::Event::KeyPressed)
			{
				//action = KeyTest(event);
			}
			
			if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased)
			{
				action = MouseTest(event, mouseglobalpos);
			}
      
			if (event.type == sf::Event::Closed)
				action = sd::ActionClose;
			
			//apply action
			if (action == sd::ActionClose)
				window.close();
		}
		
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			MouseDownTest(mouseglobalpos);
		
		//draw
		window.clear(sd::Global::ColorBackground);
		
		Draw();
		
		window.display();
		
		do
			frametime = fpstimer.getElapsedTime().asMilliseconds();
		while (frametime < 1000/60);
		fpstimer.restart();
	}
	
	UnInit();
	return 0;
}
```


> We do what we must because we can.
