/* CPSC 599 - Assignment 2
 * By: Yue Chen, Laura Berry, Andrew Lata
 * 
 */


#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curses.h>
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)

int row;
int column;
int r,c,nrows,ncols;
WINDOW *wnd;
char *board[3][3];
int A = 6;
int B = 8;
int C = 10;
int ONE = 10;
int TWO = 12;
int THREE = 14;

void init() // Initializing tasks, run when the program starts
{
	wnd = initscr();
	
	clear();
	refresh();
	return;	
}

void drawBoard() // Draws the initial blank board
{
	move(4,8);
	addstr("  1 2 3");
	move(5,8);
	addstr(" -------");
	move(6,8);
	addstr("A| | | |");
	move(7,8);
	addstr(" -------");
	move(8,8);
	addstr("B| | | |");
	move(9,8);
	addstr(" -------");
	move(10,8);
	addstr("C| | | |");
	move(11,8);
	addstr(" -------");
	refresh();
	return;
}

void testDraw() // Just a sanity check
{
	mvprintw(6,10,"X"); // 6,10
	mvprintw(6,12,"X");
	move(13,6);
	refresh();	
}

bool isBlank(int number, int letter)
{
	int x;
	int y;
	if(number==ONE)
	{
		x = 0;
		if(letter==A)
		{
			y = 0;
			return !(board[x][y]==NULL);    // Return false if the intended space is empty
		}
		else if (letter==B)
		{
			y = 1;
			return !(board[x][y]==NULL);    // Return false if the intended space is empty
		}
		else if (letter==C)
		{
			y = 2;
			return !(board[x][y]==NULL);    // Return false if the intended space is empty
		}
	}
	else if(number==TWO)
	{
		x = 1;
		if(letter==A)
		{
			y = 0;
			return !(board[x][y]==NULL);    // Return false if the intended space is empty
		}
		else if (letter==B)
		{
			y = 1;
			return !(board[x][y]==NULL);    // Return false if the intended space is empty
		}
		else if (letter==C)
		{
			y = 2;
			return !(board[x][y]==NULL);    // Return false if the intended space is empty
		}
	}
	else if(number==THREE)
	{
		x = 2;
		if(letter==A)
		{
			y = 0;
			return !(board[x][y]==NULL);    // Return false if the intended space is empty
		}
		else if (letter==B)
		{
			y = 1;
			return !(board[x][y]==NULL);    // Return false if the intended space is empty
		}
		else if (letter==C)
		{
			y = 2;
			return !(board[x][y]==NULL);    // Return false if the intended space is empty
		}
	}
	return true;    // If no match is found, return true to continue looping in getPlayerInput()
}

void getPlayerInput() // This function collects player input for tile to play
{
	messages(1);    // Call to print function
	bool loop = true;
	int letter;
	int number;
	while(loop)
	{
		char choice = getch();
		if (choice == 'a' || choice == 'A')
		{
			mvprintw(14,8,"A");
			letter = A;
		}
		else if (choice == 'b' || choice == 'B')
		{
			mvprintw(14,8,"B");
			letter = B;
		}
		else if (choice == 'c' || choice == 'B')
		{
			mvprintw(14,8,"C");
			letter = C;
		}
		else if (choice == '1')
		{
			mvprintw(14,10,"1");
			number = ONE;
		}
		else if (choice == '2')
		{
			mvprintw(14,10,"2");
			number = TWO;
		}
		else if (choice == '3')
		{
			mvprintw(14,10,"3");
			number = THREE;
		}
		
		if (!(number==NULL) && !(letter==NULL))
		{
			loop = isBlank(number,letter);
			if(loop)
			{
				number = NULL;
				letter = NULL;
			}
		}
	}
	updateBoard(number, letter, 'X');
	mvprintw(letter,number,"X");
	number = NULL;
	letter = NULL;
	messages(2);
	return;
}

void messages(int opcode) // This function will be used for printing messages on screen
{ // Used to easily add in language localization
	if(opcode==1) // opcode for user space selection prompt
	{
		mvprintw(13,6,"Choose a space"); 
		mvprintw(14,7,"( , )");
	}
	else if(opcode==2) // opcode for resetting space selection output
	{
		mvprintw(14,7,"( , )");
	}

	return;
}


void updateBoard(int number, int letter, char player)
{
	int x;
	int y;

	if(number==ONE)
	{
		x = 0;
		if(letter==A)
		{
			y = 0;
		}
		else if (letter==B)
		{
			y = 1;
		}
		else if (letter==C)
		{
			y = 2;
		}
	}
	else if(number==TWO)
	{
		x = 1;
		if(letter==A)
		{
			y = 0;
		}
		else if (letter==B)
		{
			y = 1;
		}
		else if (letter==C)
		{
			y = 2;
		}
	}
	else if(number==THREE)
	{
		x = 2;
		if(letter==A)
		{
			y = 0;
		}
		else if (letter==B)
		{
			y = 1;
		}
		else if (letter==C)
		{
			y = 2;
		}
	}
	board[x][y] = player;
	return;
}

int main()
{
	init();    // Call function to initialize curses
	drawBoard();    // Call to draw the initial blank board
	cbreak();    // Curses call to not require enter key for input
	noecho();    // Curses call to not print input characters
	//testDraw();
	while(true)
	{
		getPlayerInput();    // This function call gets player input for a space to play
	}
//	if(mvscanw(6,10,"X")==1)
//	{
//		mvprintw(13,6,"Yes");
//	}
//	else
//	{
//		mvprintw(13,6,"No");
//	}
	refresh();

	return 0;
}

