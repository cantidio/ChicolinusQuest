#include "game.hpp"
#include "bg.hpp"
#include "sprite_manager.hpp"
#include "player.hpp"
#include "input.hpp"
#include "magic.hpp"
#include "hud.hpp"
#include "enemy_wizard.hpp"

std::vector<Enemy*>		Game::mEnemies;
std::vector<Player*>	Game::mPlayers;
std::vector<Magic*>		Game::mMagics;
audiere::AudioDevicePtr	Game::mAudioDevice;
int						Game::mWidth	= 320;
int						Game::mHeight	= 240;

Game::Game()
{
	printf( "game on...\n" );
	mDisplay		= NULL;
	this->mState	= &Game::stateInit;
}

Game::~Game()
{
	printf("game off...\n");

	/*for(int i = 0; i < mEnemies.size(); ++i)
	{
		delete mObjects[i];
	}*/
	if(mDisplay != NULL)
	{
		al_destroy_display(mDisplay);
	}

	SpriteManager::clear();
}

void Game::addPlayer(Player* pPlayer)
{
	mPlayers.push_back( pPlayer );
}

void Game::addMagic(Magic* pMagic)
{
	mMagics.push_back( pMagic );
}

void Game::addEnemy(Enemy* pEnemy)
{
	mEnemies.push_back( pEnemy );
}

int Game::run()
{
	printf("game running...\n");

	while (  ((this)->*mState) () ) ;

	return 0;
}
//states
bool Game::stateInit()
{
	printf("game state: init\n");
	al_init();
	if(!al_init_image_addon())
	{
		printf("failed to initialize image addon!\n");
		return -1;
	}
/*	voice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);
    mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);
    al_attach_mixer_to_voice(mixer, voice);
	al_set_default_mixer(mixer);*/

	al_set_new_display_flags(ALLEGRO_OPENGL);
	al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP);
    srand(NULL);
	mDisplay = al_create_display(mWidth, mHeight);
	if(mDisplay	== NULL) exit(0);

	//BGLayer a("data/bg/teste/layer0.lua");

	this->mState	= &Game::stateQuit;
	this->mState	= &Game::stateDisclaimer;

	return true;
}

bool Game::stateQuit()
{
	printf("game state: quit\n");
	return false;
}

bool Game::stateDisclaimer()
{
	BG bg("data/bg/bg1/bg1.lua");
	Player* player = new Player ( Point( 0, 230 ), &bg );
	EnemyWizard* wizard = new EnemyWizard( Point( 250, 230 ), &bg );
	HUD hud(player->getLifeMax(), 0.4f );
	addPlayer( player );
	addEnemy( wizard );
	bg.getLayer(3)->addObject(player);
	bg.getLayer(3)->addObject(wizard);
	bg.setCameraTarget(player);

	Magic *a = new Magic(Point( 0, 230 ) , 1, Magic::FIRE, NULL);


	al_set_target_backbuffer( mDisplay );
	do
	{
		Input::get().update();
		al_clear_to_color( al_map_rgb( 0, 0, 0 ) );
		printf("numero de magias em cena: %d \n",mMagics.size() );
		bg.logic();
		bg.draw();
		for( int i = 0; i < mMagics.size(); ++i )
		{
			mMagics[i]->logic();
			if( mMagics[i]->needToDestroy() )
			{
				printf("tchau\n");
				delete mMagics[i];
				mMagics.erase(mMagics.begin() + i);
				continue;
			}
			mMagics[i]->draw(Point( -bg.getPosition().x, -bg.getPosition().y ) );
		}
		hud.setLife( player->getLife() );
		hud.logic();
		hud.draw( Point(10, 10) );
		for( int i = 0; i < mEnemies.size(); ++i)
		{
			for(int j = 0; j < mMagics.size(); ++j)
			{
				if( mMagics[j]->isActive() && mMagics[j]->colide( *mEnemies[i] ) )
				{
					mMagics[j]->destroy();
					mEnemies[i]->hurt( 1.0f );
					printf("colidiu com o mago safado!\n");
				}
			}
			/*if( player->colide( *mEnemies[i] ))
			{

			}*/
		}
	/*	if(a.colide(b))
		{

		}
*/
//b.logic();

		al_flip_display();
	//	al_rest(0.01);
		if( Input::get().button5() )
		{
			player->hurt( 1.0 );
		}
	}while(! Input::get().buttonStart() );

	 this->mState	= &Game::stateQuit;
	 return true;
}
