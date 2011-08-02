#ifndef _BG_
#define _BG_
#include "bg_layer.hpp"
#include "collision_box.hpp"
#include "lua.hpp"

class BG
{
	protected:
		std::vector<BGLayer*>	mLayers;
		Point					mPosition;
		Collision				mCollisionBox;
		std::string				mName;
		int						mWidth;
		int						mHeight;
		int						mPlayerLayer;
	public:
		BG(std::string& pScript);
		~BG();
		void draw() const;
		void logic();
};
#endif
