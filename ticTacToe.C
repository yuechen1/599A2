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
bool isDone_o(const char *a[][6], int b)
{
	if(a[b][1]==a[b][3] && a[b][3]==a[b][5])
	{
		return true;
	}
	else if (a[1][b]==a[3][b]&&a[3][b]==a[5][b])
	{
		return true;
	}
	if((strcmp(a[1][1],"o")==0)&&(strcmp(a[3][3],"o")==0)&&(strcmp(a[5][5],"o")==0))
	{
		return true;
	}
	else if((strcmp(a[5][1],"o")==0)&&(strcmp(a[3][3],"o")==0)&&(strcmp(a[1][5],"o")==0))
	{
		return true;
	}
	else 
	{
		return false;
	}
}
bool isDone_x(const char *a[][6], int b)
{	
	if(a[b][1]==a[b][3] && a[b][3]==a[b][5])
	{
		return true;
	}
	else if (a[1][b]==a[3][b]&&a[3][b]==a[5][b])
	{
		return true;
	}
	if((strcmp(a[1][1],"x")==0)&&(strcmp(a[3][3],"x")==0)&&(strcmp(a[5][5],"x")==0))
	{
		return true;
	}
	else if((strcmp(a[5][1],"x")==0)&&(strcmp(a[3][3],"x")==0)&&(strcmp(a[1][5],"x")==0))
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

	wnd = initscr(); 												// curses call to initialize window
	cbreak(); 														// curses call to set no waiting for Enter key
	noecho(); 														// curses call to set no echoing
	getmaxyx(wnd,nrows,ncols);										//r and c cannot go above these numbers
	curs_set(FALSE);
	bool clear;														//is the space chosen clear?
	bool done = false;												//is the game over?
	int letter;														//letter chosen
	int num;														//number chosen
	const char *board[6][6];										//initalize the playing board
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
		else if(i==1|| i== 3 || i==5)								//these are the spaces for the xs and ox to go
		{
			board[1][i]=" ";
			board[3][i]=" ";
			board[5][i]=" ";
		}	
	}

	while (done==false)
	{
		printboard(board);											//print new board

		mvprintw(r,0,"please enter a letter: ...");					//get letter input
		refresh();
		letter=getch();

		r++;
		mvprintw(r,0,"please enter a number: ...");					//get number input
		refresh();
		num=getch();

		clear= isEmpty(board, num, letter);							//check if space chosen is free
		if(clear==true)												//if so print "o" in the space chosen and update the board.
		{
			mvprintw(row, column, "o");
			board [row][column]="o";
		}
		else 														//if not prompt user to input new letter and number combo
		{	
			while(clear==false)										//do not go to computer turn until user has chosen valid input.
			{
				mvprintw(r, 0, "input is invalde, try again\n");
				r=r-2;
				mvprintw(r,0,"please enter a letter: ...");
				refresh();
				letter=getch();
				r++;
				mvprintw(r,0,"please enter a number: ...");
				refresh();
				num=getch();
				clear= isEmpty(board, num, letter);
			}
			if(clear==true)											// print "o" in the space chosen and update the board.
			{
				mvprintw(row, column, "o");
				board [row][column]="o";
			}
		}
		//done=isDone_o(board, row);										// check if game is over
		
		int randNum1= rand();										//select 2 random numbers between 1 and 3.
		randNum1= randNum1%3;
		int randNum2=rand();
		randNum2=randNum2%3;
		bool compTurn=false;
		while(compTurn==false)										// do not move on until the computer is done it's turn
		{
			clear=computerTurn(board, randNum1, randNum2);			//check if space chosen is free
			if(clear==true)											//if so print "o" in the space chosen and update the board.
			{
				mvprintw(row, column, "x");
				board[randNum1][randNum2]="x";
				compTurn=true;
			}
			else													//if not change chosen number
			{
				if(randNum1<3)										//if y value can be increased increase it.
				{
					randNum1++;
				}
				else												//if not increase x value
				{
					randNum2++;
				}
			}
		}
		//done=isDone_x(board, randNum1);
	}
	bool Owins=isDone_o(board, row);									//check if player has won the game
	if(Owins==true)												//if so tell them the won
	{
		while(1)
		{
			mvprintw(r, 0, "YOU WIN!!");
		}
	}
	else														//if not tell them computer won.
	{
		while(1)
		{
			mvprintw(r, 0, "COMPUTER WINS!!");
		}
	}
	endwin();
}
