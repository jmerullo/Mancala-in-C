#include "mancala.h"

void Init()
{
	if(!al_init())
		exit(1);
	display = al_create_display(w,h);
	al_set_new_display_flags(ALLEGRO_WINDOWED);
	if(!display)
		exit(1);
	if(!al_install_keyboard())
		exit(1);
	if(!al_install_mouse())
		exit(1);
	timer = al_create_timer(1.0 / fps);
	if(!timer)
		exit(1);
	eventQueue = al_create_event_queue();
	if(!eventQueue)
		exit(1);

	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	font24 = al_load_font("src//CaviarDreams_BoldItalic.ttf", 24, 0);
	al_register_event_source(eventQueue, al_get_keyboard_event_source());
    al_register_event_source(eventQueue, al_get_timer_event_source(timer));
    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_register_event_source(eventQueue, al_get_mouse_event_source());
}

void InitCircles(Circles * circles)							//The board is essentially set up like this:
{															//	11,10,9,8,7,6
	int i;													//[]			 []
	int xValue = 140, yValue = 260;							//	0, 1, 2,3,4,5
	circles->terminal[PLAYER] = 0;							//circles 0-5 are the player's boxes and 6-12 are the opponent's boxes.
	circles->terminal[OPPONENT] = 0;
	for(i = 0; i < 12; i++)
	{
		if(i<6)
			circles[i].id = PLAYER;
		else
			circles[i].id = OPPONENT;

		if(i == 6)
		{
			xValue = 490;
			yValue = 165;
		}
		circles[i].beads = 4;
		circles[i].boundBox = 20;	
		circles[i].x = xValue;
		circles[i].y = yValue;
		if(i < 6)
			xValue += 70;
		else
			xValue -= 70;
		
	}
}