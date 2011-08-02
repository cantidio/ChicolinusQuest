#include "../include/input.hpp"

Input* Input::mSingleton= NULL;

Input::Input()
{
	al_install_keyboard();
	mKeyboardState = new ALLEGRO_KEYBOARD_STATE;
	loadConfiguration();
}

Input::~Input()
{
	delete mKeyboardState;
}

void Input::halt()
{
	if( mSingleton != NULL )
	{
		delete mSingleton;
		mSingleton = NULL;
	}
}

Input& Input::get()
{
	if(mSingleton == NULL)
	{
		mSingleton = new Input();
	}
	return *mSingleton;
}

void Input::createDefaultConfiguration()
{
    mKey_start      = ALLEGRO_KEY_ENTER;
    mKey_up         = ALLEGRO_KEY_UP;
    mKey_down       = ALLEGRO_KEY_DOWN;
    mKey_left       = ALLEGRO_KEY_LEFT;
    mKey_right      = ALLEGRO_KEY_RIGHT;
    mKey_button1    = ALLEGRO_KEY_Q;
    mKey_button2    = ALLEGRO_KEY_W;
    mKey_button3    = ALLEGRO_KEY_E;
    mKey_button4    = ALLEGRO_KEY_R;
    mKey_button5    = ALLEGRO_KEY_A;
    mKey_button6    = ALLEGRO_KEY_S;
    mKey_button7    = ALLEGRO_KEY_D;
    mKey_button8    = ALLEGRO_KEY_F;
}

void Input::loadConfiguration()
{
    std::fstream* file;
    file = new std::fstream("data/input.cfg",std::ios::in|std::ios::binary);

    if(!file->is_open())
    {
        createDefaultConfiguration();
        saveConfiguration();
    }
    else
    {
        file->read( (char*)&mKey_start      , sizeof(int) );
        file->read( (char*)&mKey_up         , sizeof(int) );
        file->read( (char*)&mKey_down       , sizeof(int) );
        file->read( (char*)&mKey_left       , sizeof(int) );
        file->read( (char*)&mKey_right      , sizeof(int) );
        file->read( (char*)&mKey_button1    , sizeof(int) );
        file->read( (char*)&mKey_button2    , sizeof(int) );
        file->read( (char*)&mKey_button3    , sizeof(int) );
        file->read( (char*)&mKey_button4    , sizeof(int) );
        file->read( (char*)&mKey_button5    , sizeof(int) );
        file->read( (char*)&mKey_button6    , sizeof(int) );
        file->read( (char*)&mKey_button7    , sizeof(int) );
        file->read( (char*)&mKey_button8    , sizeof(int) );
    }
    file->close();
    delete file;
}

void Input::saveConfiguration() const
{
    std::fstream* file;
    file = new std::fstream("data/input.cfg",std::ios::out|std::ios::binary);

    if(file->is_open())
    {
        file->write((char*)&mKey_start	, sizeof(int));
        file->write((char*)&mKey_up		, sizeof(int));
        file->write((char*)&mKey_down	, sizeof(int));
        file->write((char*)&mKey_left	, sizeof(int));
        file->write((char*)&mKey_right	, sizeof(int));
        file->write((char*)&mKey_button1, sizeof(int));
        file->write((char*)&mKey_button2, sizeof(int));
        file->write((char*)&mKey_button3, sizeof(int));
        file->write((char*)&mKey_button4, sizeof(int));
        file->write((char*)&mKey_button5, sizeof(int));
        file->write((char*)&mKey_button6, sizeof(int));
        file->write((char*)&mKey_button7, sizeof(int));
        file->write((char*)&mKey_button8, sizeof(int));
    }
    file->close();
    delete file;
}

bool Input::buttonStart()   { return al_key_down(mKeyboardState, mKey_start  );  }
bool Input::buttonUp()      { return al_key_down(mKeyboardState, mKey_up     );  }
bool Input::buttonDown()    { return al_key_down(mKeyboardState, mKey_down   );  }
bool Input::buttonLeft()    { return al_key_down(mKeyboardState, mKey_left   );  }
bool Input::buttonRight()   { return al_key_down(mKeyboardState, mKey_right  );  }
bool Input::button1()       { return al_key_down(mKeyboardState, mKey_button1 ); }
bool Input::button2()       { return al_key_down(mKeyboardState, mKey_button2 ); }
bool Input::button3()       { return al_key_down(mKeyboardState, mKey_button3 ); }
bool Input::button4()       { return al_key_down(mKeyboardState, mKey_button4 ); }
bool Input::button5()       { return al_key_down(mKeyboardState, mKey_button5 ); }
bool Input::button6()       { return al_key_down(mKeyboardState, mKey_button6 ); }
bool Input::button7()       { return al_key_down(mKeyboardState, mKey_button7 ); }
bool Input::button8()       { return al_key_down(mKeyboardState, mKey_button8 ); }
void Input::cleanKeyBuffer()
{
    //mKeyboard->clearBuffer();
    /**@todo implementar o método acima*/
}

void Input::update()
{
	al_get_keyboard_state(mKeyboardState);
}
