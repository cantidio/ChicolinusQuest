name				= "Chicus"
direction			= 0 					-- can be 0 or 1  - right or left I mean
move_acceleration	= { 1.0, 5.0		}	-- x, y
max_acceleration	= { 2.5, 3.5		}	-- x, y in absolute values
offset				= { 30, 62			}	-- the offset
collision			= { 16, 7, 47, 62	}	-- colision def
sprites				= {
	file	= "data/obj/player/Chicus/chicus.png",	-- the image file
	width	= 79,									-- the width
	height	= 79,									-- the height
	alpha	= {r = 255, g = 0, b = 255}				-- the alpha color
}

animation	= "data/obj/player/Chicus/animation.lua"

level		= 1
levelMax	= 99
life		= 99
lifeMax		= 99
hunger		= 10
hungerMax	= 99

