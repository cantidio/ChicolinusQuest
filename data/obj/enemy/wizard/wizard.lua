name				= "Wizard"
direction			= 0 --can be 0 or 1  - right or left I mean
move_acceleration	= { 0.5, 15.0 } -- x, y
max_acceleration	= { 3.0, 5.0 } -- x, y in absolute values
offset				= {33, 59}							-- the y offset
collision			= { 20, 2, 44, 63	} -- colision def
sprites				= {
	file	= "data/obj/enemy/wizard/wizard.png",	-- the image file
	width	= 56,									-- the width
	height	= 66,									-- the height
	alpha	= {r = 255, g = 0, b = 255}				-- the alpha color
}

animation	= "data/obj/enemy/wizard/animation.lua"

level		= 1
levelMax	= 99
life		= 5
lifeMax		= 99
hunger		= 10
hungerMax	= 99

