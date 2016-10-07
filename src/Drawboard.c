#include "mancala.h"

void DrawBoard()
{
	al_draw_filled_rounded_rectangle(40, 120, 600, 320, 10, 10, al_map_rgb(240,220,130));

	al_draw_filled_rounded_rectangle(50, 140, 100, 300, 10, 10, al_map_rgb(255,255,255));		//terminal[OPPONENT]
	al_draw_filled_rounded_rectangle(540, 140, 590, 300, 10, 10, al_map_rgb(255,255,255));		//terminal[PLAYER]
}