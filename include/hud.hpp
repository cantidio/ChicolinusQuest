#ifndef _HUD_
#define _HUD_
class HUD
{
	protected:
		float mLifeSpeed;				/**<< velocity that the life "runs"*/
		float mLifeValue;			/**<< life value*/
		float mLifeValueNow;		/**<< life actual position*/
		float mLifeMax;				/**<< max life*/
		ALLEGRO_BITMAP* mLifeBar;	/**<< image of the life bar*/
		ALLEGRO_BITMAP* mLife		/**<< image of the life enclusure*/
	public:
		HUD();
		~HUD();
		void draw(const Point& pPosition) const
		{
			al_draw_bitmap( mLife, pPosition.x, pPosition.y, 0);
			al_draw_bitmap_section();
		}

		void logic()
		{
			if( mLifeValueNow > mLifeValue )
			{
				mLifeValueNow -= mLifeSpeed;
				if( mLifeValueNow < mLifeValue )
				{
					mLifeValueNow = mLifeValue;
				}
			}
			else if( mLifeValueNow < mLifeValue )
			{
				mLifeValueNow += mLifeSpeed;
				if( mLifeValueNow > mLifeValue )
				{
					mLifeValueNow = mLifeValue;
				}
			}
		}
		void addLife(const float& pLife)
		{
			mLifeValue += pLife;
			if( mLifeValue > mLifeMax )
			{
				mLifeValue = mLifeMax;
			}
		}
		void subLife(const float& pLife)
		{
			mLifeValue -= pLife;
			if( mLifeValue < 0 )
			{
				mLifeValue = 0;
			}
		}
};
#endif
