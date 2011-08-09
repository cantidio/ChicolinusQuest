#ifndef _BG_
#define _BG_
#include "bg_layer.hpp"
#include "collision_box.hpp"
#include "lua.hpp"

struct ALLEGRO_SAMPLE;
class BG
{
	protected:
		std::vector<BGLayer*>		mLayers;
		audiere::OutputStreamPtr	mMusic;
		Collision					mCollisionBox;
		std::string					mName;
		int							mWidth;
		int							mHeight;
		int							mPlayerLayer;
		Object*						mCameraTarget;
		Point						mPosition;
	public:
		inline Point getPosition() const
		{
			return mPosition;
		}
		BG(const std::string& pScript);
		~BG();
		void draw() const;
		void logic();
		BGLayer* getLayer(const unsigned int& pLayer);
		void setCameraTarget(Object* pObject);
};
#endif
