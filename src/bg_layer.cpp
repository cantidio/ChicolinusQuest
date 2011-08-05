#include "bg_layer.hpp"
#include "lua.hpp"

using namespace Gorgon::Script;
BGLayer::BGLayer(const std::string& pImage, const Point& pScrollingVelocity)
{
	mImage = al_load_bitmap( pImage.c_str() );
	al_convert_mask_to_alpha(mImage, al_map_rgb(255,0,255));
	mScrollingVelocity.x = pScrollingVelocity.x;
	mScrollingVelocity.y = pScrollingVelocity.y;
}

BGLayer::~BGLayer()
{
	al_destroy_bitmap( mImage );
}

void BGLayer::addObject(Object* pObject)
{
	mObjects.push_back(pObject);
}

void BGLayer::draw(const Point& pPosition) const
{
	const float base_x = pPosition.x * mScrollingVelocity.x;
	const float base_y = pPosition.y * mScrollingVelocity.y;

	const int init_x1= (int)base_x % al_get_bitmap_width(mImage);
	//const double init_x1 = base_x - base_x/al_get_bitmap_width(mImage) ;
	const int end_x1 = al_get_bitmap_width(mImage) - init_x1;

	al_draw_bitmap_region
	(
		mImage,
		init_x1,
		0,
		al_get_bitmap_width(mImage) - init_x1,
		al_get_bitmap_height(mImage),
		0, 0,
		0
	 );
	al_draw_bitmap_region
	(
		mImage,
		0,0,
		init_x1,
		al_get_bitmap_height(mImage),
		end_x1,
		0,
		0
	);

	//draw objects
	for(register unsigned int i = 0; i < mObjects.size(); ++i)
	{
		mObjects[i]->draw( Point( 0,0 ) );
	}
}

void BGLayer::logic()
{
	for(register unsigned int i = 0; i < mObjects.size(); ++i)
	{
		mObjects[i]->logic();
	}
}
