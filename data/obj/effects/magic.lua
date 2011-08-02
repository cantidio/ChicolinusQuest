name				= "Magic"
direction			= 0 --can be 0 or 1  - right or left I mean
move_acceleration	= { 1.0, 5.0		} -- x, y
max_acceleration	= { 2.0, 3.5		} -- x, y in absolute values
offset				= { 30, 62			} -- the offset
collision			= { 13, 17, 31, 31	} -- colision def
sprites				= {
	file	= "data/obj/effects/effects.png",	-- the image file
	width	= 49,							-- the width
	height	= 49,							-- the height
	alpha	= {r = 255, g = 0, b = 255}		-- the alpha color
}

animation	= "data/obj/effects/magic_animation.lua"

