#include "game.hpp"
#include "bg.hpp"
#include "sprite_manager.hpp"
#include "player.hpp"
#include "input.hpp"
#include "magic.hpp"

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

std::vector<Object*>	Game::mObjects;
std::vector<Player*>	Game::mPlayers;
std::vector<Magic*>		Game::mMagics;

int Game::mWidth	= 320;
int Game::mHeight	= 240;
ALLEGRO_VOICE* voice;
ALLEGRO_MIXER* mixer;

Game::Game()
{
	printf( "game on...\n" );
	mDisplay		= NULL;
	this->mState	= &Game::stateInit;
}

Game::~Game()
{
	printf("game off...\n");

	for(int i = 0; i < mObjects.size(); ++i)
	{
		delete mObjects[i];
	}
	if(mDisplay != NULL)
	{
		al_destroy_display(mDisplay);
	}

	/*al_detach_voice(voice);
	al_detach_mixer(mixer);
	al_destroy_voice(voice);
	al_destroy_mixer(mixer);
*/
	al_uninstall_audio();
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

void Game::addObject(Object* pObject)
{
	mObjects.push_back( pObject );
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
	printf("aqui\n");
	if(!al_install_audio())
	{
		printf("failed to initialize audio!\n");
		return -1;
	}
	printf("aqui\n");
	if(!al_init_acodec_addon())
	{
		printf("failed to initialize audio codecs!\n");
		return -1;
	}

/*	voice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);
    mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);
    al_attach_mixer_to_voice(mixer, voice);
	al_set_default_mixer(mixer);*/
	if (!al_reserve_samples(1))
	{
		printf("failed to reserve samples!\n");
		return -1;
	}

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
	addPlayer( player );
	bg.getLayer(3)->addObject(player);
	Magic *a = new Magic(Point( 0, 230 ) , 1, Magic::FIRE, NULL);
	al_set_target_backbuffer( mDisplay );

	bg.setCameraTarget(player);

	do
	{
	//	printf("magic on the game: %d\n",mMagics.size()); //deletar as magias manolo
		Input::get().update();
		al_clear_to_color( al_map_rgb( 0, 0, 0 ) );

		bg.draw();
		bg.logic();
		for( int i = 0; i < mMagics.size(); ++i )
		{
			mMagics[i]->draw(Point(0,0));
			mMagics[i]->logic();
		}
		/*
		for( int i = 0; i < mObjects.size(); ++i )
		{
			mObjects[i]->draw(Point(0,0));
			mObjects[i]->logic();
		}
		for( int i = 0; i < mPlayers.size(); ++i )
		{
			mPlayers[i]->draw(Point(0,0));
			mPlayers[i]->logic();
		}*/

	/*	if(a.colide(b))
		{
			printf("colidiu com o mago safado!\n");
		}
*/
//b.logic();



		al_flip_display();
	//	al_rest(0.01);
	}while(! Input::get().buttonStart() );

	 this->mState	= &Game::stateQuit;
	 return true;
}
