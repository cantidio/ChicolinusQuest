#ifndef _GAME_
#define _GAME_
#include "include.hpp"
#include "enemy.hpp"
#include "player.hpp"
#include "magic.hpp"

class Game
{
	protected:
		static audiere::AudioDevicePtr	mAudioDevice;
		bool				(Game::*mState)();  /**<<	pointer to the game state*/
		static int			mWidth;				/**<< 	*/
		static int			mHeight;
		ALLEGRO_DISPLAY*	mDisplay;

		static std::vector<Player*>	mPlayers;
		static std::vector<Enemy*>	mEnemies;
		static std::vector<Magic*>	mMagics;

	public:
		static void addEnemy(Enemy* pEnemy);
		static void addPlayer(Player* pPlayer);
		static void addMagic(Magic* pMagic);
		static audiere::AudioDevicePtr getAudioDevice()
		{
			if(mAudioDevice == NULL)
			{
				mAudioDevice = audiere::OpenDevice( "autodetect" );
			}
			return mAudioDevice;
		}
		Game();
		~Game();
		int run();

		bool stateInit();
		bool stateDisclaimer();
		bool stateMenu();
		bool stateQuit();
};
#endif
/*


chico
{
	morrendo
	atirando
	atirando especial
	levando dano
	pulando
	caindo
}
andreias
{
	gluglu
	morrendo
}
mago
{
	porrada
	atirando
	morrendo
}

63x83
guilherminus
{
	atira,
	apanha1,
	apanha2,
	apanha3,
	ri,
	morre
}
*/
