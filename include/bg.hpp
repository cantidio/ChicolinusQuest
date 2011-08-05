#ifndef _BG_
#define _BG_
#include "bg_layer.hpp"
#include "collision_box.hpp"
#include "lua.hpp"

class BG
{
	protected:
		std::vector<BGLayer*>	mLayers;
		Collision				mCollisionBox;
		std::string				mName;
		int						mWidth;
		int						mHeight;
		int						mPlayerLayer;
	public:
		Point					mPosition;
		BG(const std::string& pScript);
		~BG();
		void draw() const;
		void logic();
		BGLayer* getLayer(const unsigned int& pLayer);
};
#endif
