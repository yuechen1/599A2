/* Assignment 2
* Laura Berry (10111166)
*
*/

#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curses.h>

int row;
int column;
int r,c,nrows,ncols;

bool isEmpty(const char *a[][6], int b, int c)
{
	r++;
	if(c=='A'||c== 'a')
	{
		row=1;
	}
	else if(c=='B'||c== 'b')
	{
		row= 3;
	}
	else if(c=='C'||c== 'c')
	{
		row=5;
	}
	else
	{
		mvprintw(r, 0, " letter input not valid");
	}
	if(b=='1')
	{
		column = 1;
	}
	else if (b =='2')
	{
		column = 3;
	}
	else if(b=='3')
	{
		column=5;
	}
	else
	{
		mvprintw(r, 0, " number input not valid");
	}
	const char *result=a[row][column];
	const char *space=" ";
	if(strcmp(result, space)==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool isDone(const char *a[][6], const char* b, int c, int d)
{
	
	if (c==1 &&d==1)
	{
		if(a[c+1][d+1]==b)
		{
			if(a[c+2][d+2]==b)
			{
				return true;
			}
		}
	}
	else if (a[c][1]==b && a[c][3]==b && a[c][5]==b)
	{
		return true;
	}
	else if(a[1][d]==b && a[3][d]==b && a[5][d]==b)
	{
		return true;
	}
	else 
	{
		return false;
	}
}
bool computerTurn(const char *a[][6], int b , int c)
{	
	const char *result=a[b][c];
	const char *space=" ";
	if(strcmp(result, space)==0)
	{
		if(c=='A'||c== 'a')
		{
			row=1;
		}
		else if(c=='B'||c== 'b')
		{
			row= 3;
		}
		else if(c=='C'||c== 'c')
		{
			row=5;
		}
		if(b=='1')
		{
			column = 1;
		}
		else if (b =='2')
		{
			column = 3;
		}
		else if(b=='3')
		{
			column=5;
		}
		return true;
	}
	else
	{
		return false;
	}
}

void printboard(const char *a[][6])
{
	r=0;
	c=0;
	for (int k=0; k<6;k++)
	{
		c=0;
		for (int m=0; m<6; m++)
		{
			mvprintw(r,c,a[k][m]);
			c++;
		}
		r++;
	}
	refresh();
}

main()
{
	WINDOW *wnd;

	wnd = initscr(); // curses call to initialize window
	cbreak(); // curses call to set no waiting for Enter key
	noecho(); // curses call to set no echoing
	getmaxyx(wnd,nrows,ncols);
	curs_set(FALSE);
	bool clear;
	bool done = false;
	int letter;
	int num;
	const char *board[6][6];	
	board[0][1]="1";
	board[0][3]="2";
	board[0][5]="3";
	board[1][0]="A ";
	board[3][0]="B ";
	board[5][0]="C ";
	for (int i=0; i<6; i++)
	{
		board[2][i]="-";
		board[4][i]="-";
		if(i==0)
		{
			board[2][i]="  ";
			board[4][i]="  ";
			board[0][i]="  ";

		}
		else if(i==2 || i==4)
		{
			board[1][i]="|";
			board[3][i]="|";
			board[5][i]="|";
			board[0][i]=" ";
		}
		else if(i==1|| i== 3 || i==5)
		{
			board[1][i]=" ";
			board[3][i]=" ";
			board[5][i]=" ";
		}	
	}
	while (done==false)
	{
		printboard(board);
		r++;
		c=0;
		mvprintw(r,0,"please enter a letter: ...");
		refresh();
		letter=getch();
		//mvprintw(r,1, letter);

		r++;
		mvprintw(r,0,"please enter a number: ...");
		refresh();
		num=getch();
		//mvprintw(r,1, num);


		clear= isEmpty(board, num, letter);
		if(clear==true)
		{
			mvprintw(row, column, "o");
			board [row][column]="o";
			//printboard(board);
		}
		else 
		{
			mvprintw(row, column, "false\n");
		}
		done=isDone(board, "o", row, column);
		int randNum1= rand();
		randNum1= randNum1%3;
		int randNum2=rand();
		randNum2=randNum2%3;
		bool compTurn=false;
		while(compTurn==false)
		{
			clear=computerTurn(board, randNum1, randNum2);
			if(clear==true)
			{
				mvprintw(row, column, "x");
				board[randNum1][randNum2]="x";
				//printboard(board);
				compTurn=true;
			}
			else
			{
				mvprintw(row, column, "false");
				if(randNum1<3)
				{
					randNum1++;
				}
				else
				{
					randNum2++;
				}
			}
		}
		//done=isDone(board, "x", randNum1, randNum2);
	}
	endwin();
}
