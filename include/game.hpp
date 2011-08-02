#ifndef _GAME_
#define _GAME_
#include "include.hpp"
#include "object.hpp"

class Game
{
	protected:
		bool				(Game::*mState)();  /**<<	pointer to the game state*/
		static int			mWidth;				/**<< 	*/
		static int			mHeight;
		ALLEGRO_DISPLAY*	mDisplay;
//		ALLEGRO_BITMAP*	disclaimer;

		static std::vector<Player*>	mPlayers;
		static std::vector<Object*>	mObjects;
		static std::vector<Magic*>	mMagics;

	public:
		static void addObject(Object* pObject);
		static void addPlayer(Player* pPlayer);
		static void addMagic(Magic* pMagic);

		Game();
		~Game();
		int run();

		bool stateInit();
		bool stateDisclaimer();
		bool stateMenu();
		bool stateQuit();
		//void state
};
#endif
