/*
*	John A. Merullo
*	Belmont High School
*	Belmont, MA 02478
*
*	Last edit: 4/8/16
*
*
*
*/

#include "mancala.h"

double pi = 3.14159265359;	//close enough
const int w = 640, h = 480, fps = 60;

int main()
{
	int i, j, mousex, mousey, curCircle, curBeads;									//curBeads temporarily stores the value of the beads in the circle the player
	bool done = false, isGameOver = false, playerTurn = true;						//chooses. curCircle changes with the loop and increments up by one and determines
	int playerBeads;																//which circle to drop the next bead when the player makes a move.
	Circles circles[12];
	
	Init();
	InitCircles(circles);
	FindCoords(circles);

	bool redraw;
	al_start_timer(timer);
	while(!done)
	{
		
		ALLEGRO_EVENT event;
		al_wait_for_event(eventQueue, &event);
		if(event.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;
			if(!playerTurn && !isGameOver)
			{
				playerTurn = OpponentMove(circles);
				if(!playerTurn)
					isGameOver = true;
			else
				FindCoords(circles);
			}
			playerBeads = 0;
			for(i = 0; i<6; i++)
			{
				playerBeads+=circles[i].beads;
			}
			if(playerBeads  == 0)
				isGameOver = true;
		}
		else if(event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)	
				done = true;
		}
		else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			done = true;
		if(event.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			mousex = event.mouse.x;
			mousey = event.mouse.y;
		}
		else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && playerTurn && !isGameOver)
		{
			if(event.mouse.button & 1)
				for(i = 0; i<6; i++)
				{
					
					if(mousex > circles[i].x - circles->boundBox && mousex < circles[i].x + circles->boundBox &&
						mousey > circles[i].y - circles->boundBox && mousey < circles[i].y + circles->boundBox && circles[i].beads > 0)    
					{
						playerTurn = false;
						curCircle = i;
						curBeads = circles[curCircle].beads;
						circles[curCircle].beads = 0;
						if(i + curBeads == 6 || i + curBeads == 18)							
							playerTurn = true;													
						for(j = curBeads; j>0; j--)
						{																	
								if(curCircle == 5)
								{
									if(j <= 0)
										break;
									j--;
									circles->terminal[PLAYER]++;
								}
								
								curCircle++;

								if(curCircle ==11)
								{	
									circles[11].beads++;
									curCircle = 0;
									j--;		
								}
								if(j>0)
									circles[curCircle].beads++;
						}
						if(circles[curCircle].id == PLAYER && circles[curCircle].beads == 1 && circles[11-curCircle].beads > 0)		
						{																							//This if statement checks to see if the player is able to steal.
							printf("stealing for Player\ncircle: %i stealing from %i\n", curCircle, 11-curCircle);	//It is much more efficient than the method used for the computer
							circles->terminal[PLAYER] += (1 + circles[11-curCircle].beads);							//player because it only has to check if the player executed a
							circles[11-curCircle].beads = 0;														//move to an eligible circle.
							circles[curCircle].beads = 0;
						}
						FindCoords(circles);
						i = 7;						//The computer doesn't need to finish the for loop so it puts i out of bounds.
						
					}
				}

		}
		else if(redraw && al_is_event_queue_empty(eventQueue))
		{
			redraw = false;
			DrawBoard();
			al_draw_textf(font24, al_map_rgb(0,0,255), 550, 210, 0, "%i", circles->terminal[PLAYER]);
			al_draw_textf(font24, al_map_rgb(0,0,255), 65, 210, 0, "%i", circles->terminal[OPPONENT]);
			if(!isGameOver)
			{
				for(i = 0; i < 12; i++)
				{
					al_draw_filled_circle(circles[i].x, circles[i].y, 30, al_map_rgb(255,255,255));
					if(i<6)
						al_draw_textf(font24, al_map_rgb(255,255,255), circles[i].x - 10, 320, 0, "%i", circles[i].beads);
					else
						al_draw_textf(font24, al_map_rgb(255,255,255), circles[i].x - 10, 80, 0, "%i", circles[i].beads);
					for(j = 0; j < circles[i].beads; j++)
					{
						al_draw_filled_circle(circles[i].xvcoord[j] + circles[i].x, circles[i].yvcoord[j] + circles[i].y, 4, al_map_rgb(211, 25, 25));
					}
				}
				if(playerBeads < 1)
						{
							isGameOver = true;
							printf("gameover\n");
						}
			}
			else
			{
				al_draw_textf(font24, al_map_rgb(0,0,255), w/2, 190, 0, "Player Score: %i", circles->terminal[PLAYER]);
				al_draw_textf(font24, al_map_rgb(0,0,255), 120, 190, 0, "Opp. Score: %i", circles->terminal[OPPONENT]);
			}

			al_flip_display();
			al_clear_to_color(al_map_rgb(0,50,100));

			
		}
		
				
	}
	FILE *fp;
	fp = fopen("hexmem.txt", "w+");
	fprintf(fp, "MEMORY USE AT TERMINATION\n\n");
	for(i = 0; i<12; i++)
	{
		fprintf(fp, "circles[%i]:\t%p\n", i, &circles[i]);
	}
	fprintf(fp, "curCircle:\t%p\n", &curCircle);
	fprintf(fp, "ALLEGRO 5 COMPONENTS:\ndisplay:\t%p\n", &display);
	fprintf(fp, "eventQueue:\t%p\n", &eventQueue);
	fprintf(fp, "timer:\t%p\n", &timer);
	fprintf(fp, "font24:\t%p\n", &font24);
	fprintf(fp, "CONSTANTS:\nw:\t%p\n", &w);
	fprintf(fp, "h:\t%p\n", &h);
	fprintf(fp, "fps:\t%p\n", &fps);
	fclose(fp);

	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(eventQueue);
	return 0;
}



void FindCoords(Circles * circles)
{
	double curPoint = -1.571;
	int r = 10, i, j;
	double deltaRads;

	for(i = 0; i < 12; i++)
	{
		if(circles[i].beads == 0)
			continue;

		deltaRads = (pi/180) * (360/circles[i].beads);
		for(j = 0; j < circles[i].beads; j++)
		{
			circles[i].xvcoord[j] = (r * (cos(curPoint)));
			circles[i].yvcoord[j] = (r * (sin(curPoint)));
			curPoint+=deltaRads;
		}	
		
	}
}