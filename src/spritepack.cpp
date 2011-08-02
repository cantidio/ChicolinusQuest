#include "spritepack.hpp"

SpritePack::SpritePack()
{
    mSprites.clear();
}

SpritePack::SpritePack
(
	const std::string&		pSpriteFile,
	const int&				pSpriteWidth,
	const int&				pSpriteHeight,
	const ALLEGRO_COLOR&	pAlpha
)
{
    mSprites.clear();
	ALLEGRO_BITMAP* spritesheet = al_load_bitmap( pSpriteFile.c_str() );
	ALLEGRO_BITMAP* display		= al_get_target_bitmap();

	if( spritesheet != NULL)
	{
		for(register int i = 0 ; i < al_get_bitmap_height(spritesheet); i+=pSpriteHeight )
		{
			for(register int j = 0; j < al_get_bitmap_width(spritesheet); j+=pSpriteWidth )
			{
				al_set_target_bitmap(display);

				ALLEGRO_BITMAP* aux = al_create_bitmap(pSpriteWidth, pSpriteHeight);
				al_set_target_bitmap( aux );

				al_draw_bitmap_region
				(
					spritesheet,
					j, i,
					pSpriteWidth,
					pSpriteHeight,
					0,0,0
				);
				al_convert_mask_to_alpha(aux, pAlpha);
				mSprites.push_back(aux);
			}
		}
		al_destroy_bitmap( spritesheet );
	}
	else
	{
		printf("error\n");
	}
}

SpritePack::~SpritePack()
{
	for(register unsigned int i = 0; i < mSprites.size(); ++i)
	{
	    if(mSprites[i] != NULL)
	    {
            al_destroy_bitmap( mSprites[i] );
            mSprites[i] = NULL;
	    }

	}
}

int SpritePack::size() const
{
	return mSprites.size();
}

ALLEGRO_BITMAP* SpritePack::operator[](const unsigned int& pIndex) const
{
	return (pIndex < mSprites.size()) ? mSprites[pIndex] : NULL;
}

