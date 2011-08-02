#include "game.hpp"
#include "bg_layer.hpp"
#include "sprite_manager.hpp"
#include "player.hpp"
#include "input.hpp"
#include "magic.hpp"

std::vector<Object*> Game::mObjects;
std::vector<Player*> Game::mPlayers;
std::vector<Magic*> Game::mMagics;


int Game::mWidth	= 320;
int Game::mHeight	= 240;

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
	al_init_image_addon();
	al_set_new_display_flags(ALLEGRO_OPENGL);
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
	//Object b ( Point( 150, 230 ), "data/obj/enemy/wizard/wizard.lua" );

	addObject( new Player ( Point( 0, 230 ) ) );
	Magic *a = new Magic(Point( 0, 230 ) , 1, Magic::FIRE);
	//addObject( new Magic(Point( 0, 230 ) , 1, Magic::FIRE) );
	//;
	al_set_target_backbuffer( mDisplay );

	double x = 0;
	//printf("logic\n");
	do
	{
		Input::get().update();
		al_clear_to_color( al_map_rgb( 0, 255, 0 ) );

		for( int i = 0; i < mObjects.size(); ++i )
		{
			mObjects[i]->draw(Point(0,0));
			mObjects[i]->logic();
		}
		for( int i = 0; i < mPlayers.size(); ++i )
		{
			mPlayers[i]->draw(Point(0,0));
			mPlayers[i]->logic();
		}
		for( int i = 0; i < mMagics.size(); ++i )
		{
			mMagics[i]->draw(Point(0,0));
			mMagics[i]->logic();
		}

		x+=1.5;
		if(x>320) x = 0;

	/*	if(a.colide(b))
		{
			printf("colidiu com o mago safado!\n");
		}
*/
//b.logic();



		al_flip_display();
		al_rest(0.01);
	}while(! Input::get().buttonStart() );

	 this->mState	= &Game::stateQuit;
	 return false;
}
