#include "mancala.h"

bool OpponentMove(Circles * circles)
{
	int i, j;
	int oppBeads = 0;
	bool moved = false;

	PerfectMove(circles);	//Move priority 1: try to land perfectly into own macala, granting the opponent another turn.

	moved = Steal(circles); //Move priority 2: try to land on an empty pit and steal beads from other side of board.

	if(!moved)				//Move priority 3:
	{
		for(i = 4; i >= 0; i--)														//This move (3rd priority move) is confusing to look at but is just following
		{																			//a strategy I made to try and fill any empty pits on the opposing
			if(circles[i].beads == 0)												//side of the board using the circle that is farthest from your own mancala.
			{																		//It usually executes this move. Here, j is representing the player's circles
				for(j = 6; j < 12 ; j++)											//(excluding the last one as it ould not be beneficial to give the player a
				{																	//bead there if it was empty) if it finds an empty one it will try to place a
					if(circles[j].beads > 0 && circles[j].beads - (12-j) -1 %13>=i) //bead there using the cup farthest away from its own terminal.
					{
						moved = MakeMove(j, circles);
						j = 13;
						i = -1;
					}
				}
			}
		}
	}
	if(!moved)			//Move priority 4: Rarely executed, if all else fails it moves the beads in the circle closest to its own terminal.
	{
		for(i = 11; i>5; i--)
		{
			if(circles[i].beads > 0)
			{
				moved = MakeMove(i, circles);
				i = 4;
			}	
		}
	}
	for(i = 6; i < 12; i++)										//count beads and check if game should end
	{
		oppBeads +=circles[i].beads;
	}
	if(oppBeads < 1)
		return false;
	if(moved)													//exits function and sets playerTurn back to 'true' if the computer took a turn
			return true;

	printf("ERROR: couldn't move\n");							//error checking. If the computer can't move for some reason it will just end the game.
	return false;
}

bool MakeMove(int picked, Circles * circles)					//Here is where the computer actually moves its pieces. The computer is not all that
{																//hard to beat if you play smart however it does try to win.
	int i, curCircle = picked, curBeads;
	curBeads = circles[curCircle].beads;
	circles[curCircle].beads = 0;
	for(i = curBeads; i>0; i--)
	{
		if(curCircle == 11)
		{
			curCircle = 0;
			if(i<=0)
				return true;
			i--;
			circles->terminal[OPPONENT]++;
			if(i>0)
				circles[curCircle].beads++;
			i--;
		}
		if(i<=0)
			return true;
		curCircle++;
		if(curCircle == 11)
		{
			circles[curCircle].beads++;
			i--;
			curCircle = 0;
			if(i<=0)
				return true;
			circles->terminal[OPPONENT]++;
			i--;
			
			if(i<=0)
				return true;
			circles[curCircle].beads++;
		}
		else
			circles[curCircle].beads++;
	}
	
	return true;
}

void PerfectMove(Circles * circles)														//Perfect move refers to the case in which there is a circle on the computer's side
{																						//that has just enough beads in it that the last bead dropped goes into the terminal
	int i;																				//which resets the for loop so they can go again.
	for(i = 11; i > 5; i--)
	{
		if(i + circles[i].beads == 12 || i + circles[i].beads == 24)
		{
			MakeMove(i, circles);
			i = 11;
		}
	}
}

bool Steal(Circles * circles)
{
	int i;
	int lastSpot;
	for(i = 11; i>5; i--)
	{
		lastSpot = (i+circles[i].beads)%13;																					 //this algorithm for 'lastSpot' breaks if the value
		if(circles[lastSpot].id == OPPONENT && circles[lastSpot].beads == 0 && circles[i].beads > 0 && circles[11-i].beads>0)//is 12 but luckily if that is the case then that 
		{																													 //move has already been done with PerfectMove()
			MakeMove(i, circles);//
			circles->terminal[OPPONENT] += (1 + circles[11-lastSpot].beads);
			circles[11-lastSpot].beads = 0;
			circles[lastSpot].beads = 0;
			return true;
		}
	}
	return false;
}