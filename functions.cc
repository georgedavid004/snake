#include <iostream>
#include <unistd.h>
#include "Matrix.h"

//this function prints game on screen
void printMatrix(Matrix *matrix,int points) 
{
	//clear screen
	std::cout<<"\033[H\033[J\n\n";
	std::cout<<"POINTS: "<<points<<"\n";
	for(int row{0};row<ROW;++row)
	{
			if(row==0)//one may remove this condition for better perfomance
			{
				std::cout<<"+";
				for(int var(0);var<COL;++var)
				{
					std::cout<<"--";
				}
				std::cout<<"+"<<"\n";
			}
		std::cout<<"|";
		for(int col{0};col<COL;++col)
		{

			if(((Matrix (*)[COL])matrix)[row][col].m_head)
			{
				std::cout<<"\033[44m  \033[m";
			}
			else if(((Matrix (*)[COL])matrix)[row][col].m_state)
			{
				std::cout<<"\033[07m  \033[m";
			}
			else if(((Matrix (*)[COL])matrix)[row][col].m_food)
			{
				std::cout<<"\033[41m  \033[m";
			}
			else
			{
				std::cout<<"  ";
			}
		}
		std::cout<<"|\n";
		if(row==ROW-1)
		{
			std::cout<<"+";
			for(int var(0);var<COL;++var)
			{
				std::cout<<"--";
			}
			std::cout<<"+"<<'\n';
		}
	}
	usleep(10000);
}

//this function sets food on random position
