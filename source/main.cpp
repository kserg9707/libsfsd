#include <iostream> 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

//#include "../headers/vcontrol.h"
#include "../lib/headers/vcontrol.h"
#include "../lib/headers/sbasevalues.h"
#include "../lib/headers/eaction.h"
#include "../lib/headers/cpicture.h"
#include "../lib/headers/cbutton.h"
#include "../lib/headers/cslide.h"
#include "../lib/headers/cmessagebox.h"
//#include "../headers/cglyphtext.h" not needed for now

sf::RenderWindow* mainwindow;
sd::Button b;
sd::Slide sl;
sd::Slide sl2;
sf::Font fontsans;
sf::Music music1;

std::vector<sd::Control*> controls;

std::vector< std::vector<char> > map;

void Init()
{
	sd::Global::Init();
	for (int i = 0; i < 15; i++)
	{
		map.push_back(std::vector<char>());
		map.at(i).push_back('#');
		for (int j = 1; j < 14; j++)
		{
			if (i == 0 || i == 14)
				map.at(i).push_back('#');
			else
				map.at(i).push_back(' ');
		}
		map.at(i).push_back('#');
	}
	
	//init main window pointer so no empty init needed
	mainwindow = new sf::RenderWindow(sf::VideoMode(640, 480), "Test", sf::Style::Close | sf::Style::Titlebar);
	mainwindow->setVerticalSyncEnabled(true);
	
	//fontsans.loadFromFile("resources/fonts/DroidSans.ttf");
	fontsans = sd::Global::Font;
	
	//init static variables
	sd::Button::SetBasePicture( sd::Picture("button.png", sf::Vector2f(-1, -1), true) );
	sd::Button::SetBaseFont( fontsans );
	sd::MessageBox::SetBaseButtonPicture( sd::Picture("button.png", sf::Vector2f(-1, -1), true) );
	sd::MessageBox::SetBaseFont( fontsans );
	sd::Slide::SetBasePicture( sd::Picture("slide.png", sf::Vector2f(-1, -1), false) );
	sd::Slide::SetBaseButtonPicture( sd::Picture("slidebutton.png", sf::Vector2f(-1, -1), false) );
}

void Uninit()
{
	delete mainwindow;
}

void KeyTest()
{

}

sd::Action MousePressedTest(sf::Vector2f mouse)
{
	for (unsigned int i = 0; i < controls.size(); i++)
		controls.at(i)->PressedTest(mouse);
	return sd::ActionEmpty;
}

sd::Action MouseTest(sf::Vector2f mouse)
{
	for (unsigned int i = 0; i < controls.size(); i++)
		if (controls.at(i)->GetType() == sd::button)
			controls.at(i)->DownTest(mouse);
	
	if (sl.DownTest(mouse))
		music1.setVolume(sl.GetValue());
	if (sl2.DownTest(mouse))
		music1.setPitch(((float)sl2.GetValue()) / 100);
	
	return sd::ActionEmpty;
}

sd::Action MouseReleasedTest(sf::Vector2f mouse)
{
	if (sl.ReleasedTest(mouse))
		music1.setVolume(sl.GetValue());
	if (sl2.ReleasedTest(mouse))
		music1.setPitch(((float)sl2.GetValue()) / 100);
	if (b.ReleasedTest(mouse))
		return sd::ActionClose;
	return sd::ActionEmpty;
}


void DrawMap()
{
	sf::RectangleShape rbg(sf::Vector2f(25, 25));
	rbg.setFillColor(sf::Color(120,120,120));
	sf::RectangleShape rb(sf::Vector2f(23, 23));
	rb.setFillColor(sf::Color(160,160,160));
	sf::RectangleShape re(sf::Vector2f(23, 23));
	re.setFillColor(sf::Color::White);
	sf::Text ch("", fontsans, 12);
	ch.setColor(sf::Color::Black);
	
	for (int i = 0; i < 15; i++)
	for (int j = 0; j < 15; j++)
	{
		rbg.setPosition(i*25, j*25);
		mainwindow->draw(rbg);
		if (map.at(i).at(j) == '#')
		{
			ch.setString("#");
			sf::Vector2f textsize(ch.getLocalBounds().width, ch.getLocalBounds().height);
			ch.setOrigin((int)(textsize.x / 2), (int)(textsize.y / 2 + 3));
			rb.setPosition(i*25+1, j*25+1);
			mainwindow->draw(rb);
			ch.setPosition(i*25+12, j*25+12);
			mainwindow->draw(ch);
		}
		if (map.at(i).at(j) == ' ')
		{
			ch.setString("?");
			sf::Vector2f textsize(ch.getLocalBounds().width, ch.getLocalBounds().height);
			ch.setOrigin((int)(textsize.x / 2), (int)(textsize.y / 2 + 3));
			re.setPosition(i*25+1, j*25+1);
			mainwindow->draw(re);
			ch.setPosition(i*25+12, j*25+12);
			mainwindow->draw(ch);
		}
	}
}


int main()
{
	Init();
	
	sf::RenderWindow& window = *mainwindow;
	
	sf::Clock fpstimer;
	
	music1.openFromFile("resources/music/rougelike1.wav");
	music1.setLoop(true);
	music1.setVolume(70);
	
	b = sd::Button("Quit", sf::Vector2f());
	b.SetPosition( sf::Vector2f(window.getSize().x, window.getSize().y) - b.GetSize() - sf::Vector2f(3, 3));
	//b.SetSize(250,15);
	
	sd::AskMessageBox mb("Quit?", "Really close?", mainwindow);
	sl = sd::Slide(sf::Vector2f(25, window.getSize().y - 75), sf::Vector2f(200, 20), 0, 100);
	sl.SetValue(music1.getVolume());
	sl2 = sd::Slide(sf::Vector2f(25, window.getSize().y - 100), sf::Vector2f(200, 20), 0, 300);
	sl2.SetValue(music1.getPitch() * 100);
	
	controls.push_back((sd::Control*)(&b));
	controls.push_back((sd::Control*)(&sl));
	controls.push_back((sd::Control*)(&sl2));
	//sl = sd::Slide(sf::Vector2f(0, 0));
	
	/////////////////test
	/*const sf::Texture& ft = fontsans.getTexture(14);
	sf::Glyph glyph = fontsans.getGlyph('Q', 14, false);
	sf::Sprite fs;
	fs.setTexture(ft);
	fs.setTextureRect(glyph.textureRect);
	fs.setColor(sf::Color::Black);*/
	//image.create(10,10, sf::Color(100,100,100,100));
	/////////////////////
	
	//float r = 50;
	float frametime = 0;
	music1.play();
	while (window.isOpen())
	{
		sf::Vector2i mousewindowpos = sf::Mouse::getPosition(window);
		sf::Vector2f mouseglobalpos = window.mapPixelToCoords(mousewindowpos);
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			
			if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) || 
			(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q))
				if (mb.Show() == sd::AskMessageBox::ResultOK)
					window.close();
			
			//KeyHit
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Return)
				{}
			}
			
			//MouseHit
			if (event.type == sf::Event::MouseButtonPressed)
				if (event.mouseButton.button == sf::Mouse::Left)
					MousePressedTest(mouseglobalpos);
			
			//mouse released
			if (event.type == sf::Event::MouseButtonReleased)
				if (event.mouseButton.button == sf::Mouse::Left)
					if (MouseReleasedTest(mouseglobalpos) == sd::ActionClose)
						if (mb.Show() == sd::AskMessageBox::ResultOK)
							window.close();
		}
		
		//MouseDown
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			MouseTest(mouseglobalpos);


		///////////////////////////////////////////Управление персонажем с анимацией////////////////////////////////////////////////////////////////////////
		/*if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
			p.dir = 1; p.speed = 1;//dir =1 - направление вверх, speed =0.1 - скорость движения. Заметьте - время мы уже здесь ни на что не умножаем и нигде не используем каждый раз
			CurrentFrame += 0.1;
			if (CurrentFrame > 3) CurrentFrame -= 3; 
			p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96)); //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)
		}

		if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
			p.dir = 0; p.speed = 1;//направление вправо, см выше
			CurrentFrame += 0.1;
			if (CurrentFrame > 3) CurrentFrame -= 3; 
			p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96));  //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)
		}

		if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) { 
			p.dir = 3; p.speed = 1;//направление вниз, см выше
			CurrentFrame += 0.1;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 288, 96, 96));  //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)
			
		}

		if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) { //если нажата клавиша стрелка влево или англ буква А
			p.dir = 2; p.speed = 1;//направление вверх, см выше
			CurrentFrame += 0.1; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (CurrentFrame > 3) CurrentFrame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
			p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
		
		}*/
		
		window.clear(sf::Color(170,170,170));
		DrawMap();
		for (unsigned int i = 0; i < controls.size(); i++)
			controls.at(i)->Draw(window);
		/*b.Draw(window);
		sl.Draw(window);
		sl2.Draw(window);*/
		//b.SetPosition(b.GetPosition() + sf::Vector2f(0.5, 0.5));
		//sf::Vector2f t = b.GetSize();
		//b.SetSize(t+sf::Vector2f(0.5, 0.5));
		window.display();

		do
			frametime = fpstimer.getElapsedTime().asMilliseconds();
		while (frametime < 1000/60);
		fpstimer.restart();
	}
	music1.stop();
	Uninit();

	return 0;
}