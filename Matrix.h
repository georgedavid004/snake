#ifndef  MATRIX_H
#define  MATRIX_H
const int ROW{10};
const int COL{10};

class Matrix
{
	public:
		bool m_state;//1/0 1 if snake/food/barrier is there
		int m_food;
		int m_head;
		int m_nextRow;
		int m_nextCol;
		Matrix(bool state=0,int food=0,int head=0)
		:m_state(state),m_food(food),m_head(head),m_nextRow(-1),m_nextCol(-1)//pointer is null by default
		{
		}
		
//		friend void operator<<(std::ostream &out,Matrix *matrix);
};
#endif
