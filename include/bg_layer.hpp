#ifndef _BG_LAYER_
#define _BG_LAYER_
#include "object.hpp"
#include "include.hpp"

class BGLayer
{
	protected:
		ALLEGRO_BITMAP* mTileSheet;	/**<< the image with all the tiles of the layer*/
		int **mTileMap;				/**<< the matrix with the definitions of the tiles of the layer*/
		int mWidth;					/**<< the width of the layer*/
		int mHeight;				/**<< the height of the layer*/
		int mHTiles;
		int mVTiles;
		Point mScrollingVelocity;

		std::vector<Object*> mObjects;/**list of all layer's objects */



		static int mTileSize;
	public:
		BGLayer(const std::string& pScript);
		~BGLayer();
		void addObject(Object* pObject);
		void draw(const Point& pPosition) const;
		void logic();
		int inline getTileSize() const
		{
			return mTileSize;
		}

};

#endif
