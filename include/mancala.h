#ifndef MANCALA_H
#define MANCALA_H
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

enum ID{PLAYER, OPPONENT};

typedef struct Circles
{
	int id;
	int beads;
	int boundBox;
	int x;
	int y;
	int terminal[2];				//the two terminals (where you put the beads to score points) are accessed with the enum ID using PLAYER and OPPONENT as the array elements
	double xvcoord[48];
	double yvcoord[48];
}Circles;


ALLEGRO_DISPLAY *display;
ALLEGRO_EVENT_QUEUE *eventQueue;
ALLEGRO_TIMER *timer;
ALLEGRO_FONT *font24;

void Init();
void InitCircles(Circles * circles);
void DrawBoard();
void FindCoords(Circles * circles);
bool OpponentMove(Circles * circles);
bool MakeMove(int picked, Circles * circles);
void PerfectMove(Circles * circles);
bool Steal(Circles * circles);



extern const int w, h, fps;

#endif