#include "bg.hpp"
using namespace Gorgon::Script;

BG::BG(const std::string& pScript)
{
	Lua lua(pScript);
	//register some help functions
	lua.executeString("function _getLayerNumber()		return #layers end");
	lua.executeString("function _getLayerImage(i)		return layers[i + 1].img end");
	lua.executeString("function _getLayerVelocityX(i)	return layers[i + 1].vel.x end");
	lua.executeString("function _getLayerVelocityY(i)	return layers[i + 1].vel.y end");
	lua.executeString("function _getPlayerXPosition()	return playerPosition[1] end");
	lua.executeString("function _getPlayerYPosition()	return playerPosition[2] end");

	mName				= lua.getNumericVar("BG_name");
	mWidth				= lua.getNumericVar("BG_width");
	mHeight				= lua.getNumericVar("BG_height");
	mPosition.x			= lua.function("_getXPosition"		, LuaParam(""), 1).getNumericValue();
	mPosition.y			= lua.function("_getYPosition"		, LuaParam(""), 1).getNumericValue();

	Point playerPosition;
	mPlayerLayer		= lua.getNumericVar("playerLayer");
	playerPosition.x	= lua.function("_getPlayerXPosition", LuaParam(""), 1).getNumericValue();
	playerPosition.y	= lua.function("_getPlayerYPosition", LuaParam(""), 1).getNumericValue();
	const int layerNum	= lua.function("_getLayerNumber"	, LuaParam(""), 1).getNumericValue();

	mCameraTarget	= NULL;
	mMusic			= al_load_sample( lua.getStringVar("music").c_str() );
	if (mMusic == NULL)
	{
		printf( "BG music:\"%s\" couldn't be loaded!\n", lua.getStringVar("music").c_str() );
	}
	else
	{
		mMusicInstance = al_create_sample_instance( mMusic );
		al_set_sample_instance_gain		( mMusicInstance, 1.0);
		al_set_sample_instance_pan		( mMusicInstance, 0.0);
		al_set_sample_instance_playmode	( mMusicInstance, ALLEGRO_PLAYMODE_LOOP );
		al_set_sample_instance_speed	( mMusicInstance, 1.0 );
		
		printf("time: %f\n", al_get_sample_instance_time( mMusicInstance ) );
		
		
		al_attach_sample_instance_to_mixer( mMusicInstance, al_get_default_mixer() );
		
	}

	for(register int i = 0 ; i < layerNum; ++i)
	{
		mLayers.push_back
		(
			new BGLayer
			(
				lua.function("_getLayerImage", LuaParam("i",i), 1).getStringValue(),
				Point
				(
					lua.function("_getLayerVelocityX", LuaParam("i",i), 1).getNumericValue(),
					lua.function("_getLayerVelocityY", LuaParam("i",i), 1).getNumericValue()
				)
			)
		);

		if(i == mPlayerLayer)
		{
//			mLayer[i]->addObject( PLAYER );
		}
	}
}

BG::~BG()
{
	for(unsigned int i = 0 ; i < mLayers.size(); ++i)
	{
		delete mLayers[i];
	}
	mLayers.clear();
	al_stop_sample_instance( mMusicInstance );
	al_destroy_sample_instance( mMusicInstance );
	al_destroy_sample( mMusic );
}

void BG::draw() const
{
	for(unsigned int i = 0 ; i < mLayers.size(); ++i)
	{
		mLayers[i]->draw(mPosition);;
	}
}

void BG::logic()
{
	if( mMusicInstance != NULL && !al_get_sample_instance_playing( mMusicInstance ) )//if no music is playing, play it!
	{
		printf("play the mothafucka\n");
		al_play_sample_instance( mMusicInstance );//, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL );
	}

	if( mCameraTarget != NULL )
	{
		Point cameraPos = mPosition;
		Point targetPos = mCameraTarget->getPosition();
		const int width = 320;
		const int height = 240;

		if( targetPos.x >= ( width / 2 ) )
		{
			if( targetPos.x <= ( 99999999 - width / 2 ) )
			{
				cameraPos.x = 1 * ( targetPos.x - width / 2 );
			}
			else if( targetPos.x >= (99999999 - width/2) )
			{
				cameraPos.x = 1 * (99999999 - width);
			}
		}
		else
		{
			cameraPos.x = 0;
		}
		mPosition.x = cameraPos.x;

			/*if	targetPos.y >= (window_height/2) then
				if targetPos.y <= (self.mHeight - window_height/2) then
					cameraPos.y = -1 * (targetPos.y - window_height/2 )
				elseif targetPos.y >= (self.mHeight - window_height/2) then
					cameraPos.y = -1 * (self.mHeight - window_height)
				end
			elseif targetPos.y <= (window_height/2) then
				cameraPos.y = 0
			end*/
	}
	for(unsigned int i = 0 ; i < mLayers.size(); ++i)
	{
		mLayers[i]->logic();
	}
}

BGLayer* BG::getLayer(const unsigned int& pLayer)
{
	return mLayers[pLayer];
}

void BG::setCameraTarget(Object* pObject)
{
	mCameraTarget = pObject;
}

