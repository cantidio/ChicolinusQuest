#ifndef _BG_LAYER_
#define _BG_LAYER_
#include "object.hpp"
#include "include.hpp"

class BGLayer
{
	protected:
		ALLEGRO_BITMAP* mImage;		/**<< the image of the layer*/
		Point mScrollingVelocity;

		std::vector<Object*> mObjects;/**list of all layer's objects */
	public:
		BGLayer(const std::string& pImage, const Point& pScrollingVelocity);
		~BGLayer();
		void addObject(Object* pObject);
		void draw(const Point& pPosition) const;
		void logic();
};

#endif
