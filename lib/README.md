## Classes
### class Picture
Improved sf::Sprite adapted for using in controls.

```c++
{
private:
//variables
        bool initok; //is initialization completed and object can be used

       	sf::String _file; //image file name
        sf::Image _image; //each object stored to modify and copy picture
        sf::Texture _texture;
        sf::Sprite _sprite;

       	sf::Vector2u _size; //size of texture
        sf::Vector2f _fsize; //size of one frame

//methods
        //load image from file. Can center origin, mask color if needed
        void _LoadImage(bool centrepivot, const sf::Color& maskclr, bool mask);

	//update picture from _image
       	void _SetImage(bool centrepivot, const sf::Color& maskclr, bool mask);

       	//copy image, texture and sprite to *this
        void _SetSprite(const sf::Image& srcimage, const sf::Texture& srctexture, const sf::Sprite& srcsprite);

public:
//methods
	//ctors:
       	//empty ctor, initok = false;
        Picture();

       	//load from file, set size. if (setpivot = true) then pivot is centred
	Picture(const sf::String& file, const sf::Vector2f& fsize, bool setpivot = false);
	//same but set mask color
       	Picture(const sf::String& file, const sf::Vector2f& fsize, const sf::Color& maskclr, bool setpivot = false);
	//same but load from ready image
       	Picture(const sf::Image& file, const sf::Vector2f& fsize, bool setpivot = false);
	//...same
       	Picture(const sf::Image& file, const sf::Vector2f& fsize, const sf::Color& maskclr, bool setpivot = false);
	//copy ctor
       	Picture(const Picture& src);

       	//for init after empty ctor
        Picture& operator = (const Picture& src);

       	//same to sf::Sprite::getRotation(), simply calling it
        float GetRotation() const;

       	//same to sf::Sprite::setRotation(float), simply calling it
       	void SetRotation(float rot);


	//same to sf::Sprite methods
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

	//get real size (with applied scale)
       	sf::Vector2f GetGlobalSize() const;

	//set real size (apply scale)
       	void SetSize(float x, float y);
        void SetSize(sf::Vector2f size);
};

```

### class Global
Initialize and load global variables (needs char** env from main())

```c++
{
private:
        static sf::Color _colorbg;		//background (window) color
        static sf::Color _colorfg;		//foreground (controls) color
        static sf::Color _colorbase;		//?
        static sf::Color _colortext;		//controls' text color
        static sf::Color _colorpressedbase;	//pressed control color
        static sf::Color _colordisabledbase;	//(enanled = false) color
        static sf::Color _colordisabledtext;	//same but for text
        static sf::Font _font; //base font, loaded from path $(PATH)/../share/sfsd/

       	static std::vector<sf::Image> _images;
        static sd::Picture _picturebutton;
        static sd::Picture _picturesliderail;
        static sd::Picture _pictureslidebutton;

       	//merge two vectors in one, excluding empty strings
        static std::vector<std::string> _VectorMerge
                (const std::vector<std::string>& a, const std::vector<std::string>& b, bool noempty = true);

       	//find cariable and get it's value, dividing on elements by separators
        static std::vector<std::string> _EnvParse(char** env, std::string variable, std::string separator);

       	static int _LoadFont(std::vector<std::string> paths);

       	static int _LoadImages(std::vector<std::string> paths);
public:
       	static const sf::Color& ColorBackground;
        static const sf::Color& ColorForeground;
        static const sf::Color& ColorBase;
        static const sf::Color& ColorText;
        static const sf::Color& ColorPressedBase;
        static const sf::Color& ColorDisabledBase;
        static const sf::Color& ColorDisabledText;
        static const sf::Font& Font;

       	static const sd::Picture& PictureButton;
        static const sd::Picture& PictureSlideRail;
        static const sd::Picture& PictureSlideButton;
        //static const sf::Image& ImageCheckBox;
        //static const sf::Image& ImageRadioButton;

       	static int Init(char** env);
};
```

### class Control
Base class for each object.
All methods are virtual so you can add all controls to an array of type (Control*) ex. to call Draw() method.

```c++
{
protected:
//variables
	Type type; //TODO: use this variable in other classes; rename to _type
        sf::Vector2f _pos; //left top corner of object (if not stated other)
        sf::Vector2f _size; //is it used?

       	bool _enabled;
        bool _visible;

public:
//enums
	enum Type {empty, button, slide}; //type of object, set in ctors

//methods
	//returns _type
       	virtual Type GetType() const { return type; } //TODO: move realization to .cpp

	//returns coordinates of top left corner
       	virtual sf::Vector2f GetPosition() const = 0;

	//sets coordinates of top left corner
       	virtual void SetPosition(float x, float y) = 0;
       	virtual void SetPosition(const sf::Vector2f& src) = 0;


       	//returns size of object
        virtual sf::Vector2f GetSize() const = 0;

	//sets size of object
       	virtual void SetSize(float x, float y) = 0;
       	virtual void SetSize(sf::Vector2f size) = 0;


	//draw an object to window. Any control can be stated as (control*)
       	virtual void Draw(sf::RenderWindow& targetwindow) = 0;


	////update object according to mouse state
	//if mouse hit on object
       	virtual bool PressedTest(sf::Vector2f mousepos) { return false; }

	//if mouse held on object
       	virtual bool DownTest(sf::Vector2f mousepos) { return false; }

	//if mouse released on object 
       	virtual bool ReleasedTest(sf::Vector2f mousepos) { return false; }


	//returns _enabled
       	virtual bool IsEnabled() = 0;

	//sets _enabled. If false, user can't interact with it
       	virtual void SetEnabled(bool enabled) = 0;

	//returns _visible
       	virtual bool IsVisible() = 0;

	//sets _visible. If false, object is not drawn and is not interactible.
       	virtual void SetVisible(bool visible) = 0;
};
```

### class Button
Simple button withh ability to set any picture as background.

```c++
class Button : public Control
{
private:
	static sd::Picture _basepic; //default picture, if not given another
	static sf::Font _basefont; //so font
	
	bool _initok; //is initialization completed
	bool _waspressed; //true when pressed by mouse
	bool _state; //when was pressed and mouse on button. need for result when released
	
	sf::String _str; //text on button
	sf::Text _text; //to draw this text
	int _fontsize;
	
	//sf::Vector2f _pos; //button center pos
	//sf::Vector2f _size; //is it used?
	
	sd::Picture _bgpic; //so background picture
	sf::Font _font; //_font = _basefont, if not set
	
	sf::Color _pressedcolor; //sprite color when button pressed
	sf::Color _disabledcolor; //sprite color when button disabled
	sf::Color _disabledtextcolor;
	
	//bool _enabled;
	//bool _visible; //declared in class Control
	
	
	void _Init();
	
	//takes coords of left top corner, but pivots set to centre. so need to move.
	void _PosFixOnSet();
	
	//same: returns coord of left top corner, _pos set to centre.
	sf::Vector2f _PosFixOnGet() const;
public:
	Type GetType() const; //virtual in Control
	
	//empty ctor, initok = false;
	Button();
	
	//init
	Button(const sf::String& str, const sf::Vector2f& pos);

	Button(const sf::String& str, const sf::Vector2f& pos, const sf::Font& font, const sd::Picture& pic);
	
	Button(const Button& src);
	
	//to init after empty ctor
	Button& operator = (const Button& src);
	
	
	//init static vars. New vars applies to objects created after setting it
	static void SetBasePicture(const sd::Picture& pic);
	static void SetBaseFont(const sf::Font& font);
	
	
	//set new bg picture. if savesize == true, button is not resized
	void SetPicture(sd::Picture pic, bool savesize = true);
	
	
	//sets var _pos. takes/returns coord of left top corner; _pos - centre of button
	sf::Vector2f GetPosition() const;
	
	void SetPosition(float x, float y);
	
	void SetPosition(const sf::Vector2f& src);
	
	
	//size of background picture so size of button
	sf::Vector2f GetSize() const;
	
	void SetSize(float x, float y);
	
	void SetSize(sf::Vector2f size);
	

	//draws bg, sets text position, draws text
	void Draw(sf::RenderWindow& targetwindow);
	
	
	//takes mouse position, called on events according to name.
	bool PressedTest(sf::Vector2f mousepos);
	
	bool DownTest(sf::Vector2f mousepos);
	
	bool ReleasedTest(sf::Vector2f mousepos);
	
	
	bool IsEnabled();
	
	void SetEnabled(bool enabled);
	
	bool IsVisible();
	
	void SetVisible(bool visible);
};
```
