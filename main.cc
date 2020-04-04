#include <iostream>
#include <unistd.h>
#include "Matrix.h"
#include "fwrdDecl.h"
int food_x{0},food_y{0};
bool setFood(Matrix *matrix)//sets random food
{
	while(true)
	{
		food_x=std::rand()%ROW;
		food_y=std::rand()%COL;
		if(((Matrix(*)[COL])matrix)[food_x][food_y].m_head)
		{
			//do nothing	
		}
		else if(((Matrix(*)[COL])matrix)[food_x][food_y].m_state)
		{
			//do nothing
		}
		else if(((Matrix(*)[COL])matrix)[food_x][food_y].m_food)
		{
			//do nothing
		}
		else 
		{
			((Matrix(*)[COL])matrix)[food_x][food_y].m_food=1;
			return 1; //after setting food return
		}
	}
}
char inputDir()
{
	
	char character{0};
	std::cout<<"enter dir ('a','s','d','f') :";
	std::cin>>character;
	return character;
}
void gameOver()
{
		std::cout<<"\t\tGAME OVER!!!\n";
		exit(0);
}
void shiftMatrix(Matrix *matrix,int h_row,int h_col,int n_row,int n_col)//n_col is next col 
{
		Matrix nextMatrix[ROW][COL];
		while(true)
		{
			//shifting cells according to move
			if(((Matrix (*)[COL])matrix)[h_row][h_col].m_nextRow<0||((Matrix (*)[COL])matrix)[h_row][h_col].m_nextRow<0)
			{
				if(((Matrix (*)[COL])matrix)[h_row][h_col].m_head==1)
				{
					nextMatrix[n_row][n_col].m_head=1;
				}
				nextMatrix[n_row][n_col].m_state=1;
				nextMatrix[n_row][n_col].m_nextCol=-1;
				nextMatrix[n_row][n_col].m_nextRow=-1;
				nextMatrix[food_x][food_y].m_food=1;
				break;
			}
			else
			{//h_row dosn't mean head's coordinate here, Abuse of variable name
				nextMatrix[food_x][food_y].m_food=1;
				nextMatrix[n_row][n_col].m_nextRow=h_row;
				nextMatrix[n_row][n_col].m_nextCol=h_col;
				nextMatrix[n_row][n_col].m_food=((Matrix (*)[COL])matrix)[h_row][h_col].m_food;
				nextMatrix[n_row][n_col].m_state=((Matrix (*)[COL])matrix)[h_row][h_col].m_state;		
				nextMatrix[n_row][n_col].m_head=((Matrix (*)[COL])matrix)[h_row][h_col].m_head;
				n_row=h_row;
				n_col=h_col;
				int temp=h_row;
				h_row=((Matrix (*)[COL])matrix)[temp][h_col].m_nextRow;
				h_col=((Matrix (*)[COL])matrix)[temp][h_col].m_nextCol;
				
			}
			
		}
		//update matrix
		for(int row(0);row<ROW;++row)
		{
			for(int col(0);col<COL;++col)
			{
				((Matrix (*)[COL])matrix)[row][col].m_food=nextMatrix[row][col].m_food;
				((Matrix (*)[COL])matrix)[row][col].m_head=nextMatrix[row][col].m_head;
				((Matrix (*)[COL])matrix)[row][col].m_nextCol=nextMatrix[row][col].m_nextCol;
				((Matrix (*)[COL])matrix)[row][col].m_nextRow=nextMatrix[row][col].m_nextRow;
				((Matrix (*)[COL])matrix)[row][col].m_state=nextMatrix[row][col].m_state;
			}
		}
}
char checkMove(Matrix *matrix,int &h_row,int &h_col,int n_row,int n_col,int &points)
{
	if(n_row>=0&&n_row<ROW&&n_col>=0&&n_col<COL)
	{
		if(((Matrix (*)[COL])matrix)[n_row][n_col].m_state||((Matrix (*)[COL])matrix)[n_row][n_col].m_head)
		{
			gameOver();
		}
		else if(((Matrix (*)[COL])matrix)[n_row][n_col].m_food)
		{
			points=points+1;
			//got food now join a cell and move
			((Matrix (*)[COL])matrix)[h_row][h_col].m_head=0;
			((Matrix (*)[COL])matrix)[h_row][h_col].m_state=1;
			((Matrix (*)[COL])matrix)[n_row][n_col].m_head=1;
			//joining next
			((Matrix (*)[COL])matrix)[n_row][n_col].m_nextRow=h_row;
			((Matrix (*)[COL])matrix)[n_row][n_col].m_nextCol=h_col;
			h_row=n_row;
			h_col=n_col;

			setFood(matrix);
		}
		else
		{
			//move 

			shiftMatrix(matrix,h_row,h_col,n_row,n_col);
			h_row=n_row;
			h_col=n_col;
		}
	}
	else
	{
		gameOver();
	}
}

//this function joins blocks to snakes tails
bool move(Matrix *matrix,int &h_row,int &h_col)
{
	int points{0};
	while (true)
	{
		printMatrix(matrix,points);

		switch (inputDir())
		{
		case 'w':
			//moAve up
			checkMove(matrix,h_row,h_col,h_row-1,h_col,points);
			break;
		case 'a':
			checkMove(matrix,h_row,h_col,h_row,h_col-1,points);
			//move left	
			break;
		case 's':
			//if tail is there move not allowed
			checkMove(matrix,h_row,h_col,h_row+1,h_col,points);
		//move down
			break;
		case 'd':
			checkMove(matrix,h_row,h_col,h_row,h_col+1,points);
		//move right
			break;
		default:
			break;
		}
	
	}
}
void game()
{
	Matrix matrix[ROW][COL];
	//setting head
//	int row(std::rand()%ROW),col(std::rand()%COL);
	int row{1},col{1};
	matrix[row][col].m_head=1;
/*	matrix[row][col].m_nextRow=row;
	matrix[row][col].m_nextCol=col+1;
	matrix[row][col+1].m_state=1;

	matrix[row][col+2].m_state=1;
	matrix[row][col+1].m_nextCol=col+2;
	matrix[row][col+1].m_nextRow=row;
	*/
	setFood((Matrix *)matrix);
	//matrix[1][0].m_food=1;

	move((Matrix*)matrix,row,col);
	//setFood((Matrix *)matrix);
//	printMatrix((Matrix *)matrix);

	return ;
}
int main()
{
	std::srand(time(0));
	game();
	return 0;
}
