/* Assignment 2
* Laura Berry (10111166)
*
*/

#include<stdio.h>




void printboard(const char *a[][6])
{
		for (int k=0; k<6;k++)
	{
		for (int m=0; m<6; m++)
		{
			printf(a[k][m]);
		}
		printf("\n");
	}
}

main()
{
	char b;
	int a;
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
	
	printboard(board);
	printf("please enter a letter: ...");
	scanf("%c", &b);
	printf("please enter a number: ...");
	scanf("%d", &a);

	
	

}
