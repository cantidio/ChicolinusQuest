#ifndef _HUD_
#define _HUD_
struct ALLEGRO_BITMAP;
class Point;
class HUD
{
	protected:
		float mLifeSpeed;			/**<< velocity that the life "runs"*/
		float mLifeValue;			/**<< life value*/
		float mLifeValueNow;		/**<< life actual position*/
		float mLifeMax;				/**<< max life*/
		ALLEGRO_BITMAP* mLifeBar;	/**<< image of the life bar*/
		ALLEGRO_BITMAP* mLife;		/**<< image of the life enclusure*/
	public:
		HUD(const float& pLifeMax, const float& pLifeSpeed = 1.0f);
		~HUD();
		void draw(const Point& pPosition) const;
		void logic();
		void setLife(const float& pLife);
};
#endif
