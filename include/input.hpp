#ifndef _INPUT_
#define _INPUT_
#include <iostream>
#include <fstream>
#include "include.hpp"

class Input
{
	protected:
		static Input* mSingleton;
		ALLEGRO_KEYBOARD_STATE* mKeyboardState;

		int mKey_start;
		int mKey_up;
		int mKey_down;
		int mKey_left;
		int mKey_right;
		int mKey_button1;
		int mKey_button2;
		int mKey_button3;
		int mKey_button4;
		int mKey_button5;
		int mKey_button6;
		int mKey_button7;
		int mKey_button8;
	protected:
		Input();
		virtual ~Input();
		void loadConfiguration();
		void saveConfiguration() const;
		void createDefaultConfiguration();
    public:
		static void halt();
		static Input& get();
		bool buttonStart();
		bool buttonUp();
		bool buttonRight();
		bool buttonDown();
		bool buttonLeft();
		bool button1();
		bool button2();
		bool button3();
		bool button4();
		bool button5();
		bool button6();
		bool button7();
		bool button8();
		void cleanKeyBuffer();
		void update();
};

#endif

