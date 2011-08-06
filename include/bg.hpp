#ifndef _BG_
#define _BG_
#include "bg_layer.hpp"
#include "collision_box.hpp"
#include "lua.hpp"

struct ALLEGRO_SAMPLE;
class BG
{
	protected:
		std::vector<BGLayer*>	mLayers;
		ALLEGRO_SAMPLE*			mMusic;
		Collision				mCollisionBox;
		std::string				mName;
		int						mWidth;
		int						mHeight;
		int						mPlayerLayer;
		Object*					mCameraTarget;
	public:
		Point					mPosition;
		BG(const std::string& pScript);
		~BG();
		void draw() const;
		void logic();
		BGLayer* getLayer(const unsigned int& pLayer);
		void setCameraTarget(Object* pObject);
};
#endif
