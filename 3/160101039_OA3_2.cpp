#include <bits/stdc++.h>
using namespace std;

//four functions to traverse up, down, left, right.
void down(int *matrix, int i , int j, int m1 , int n1, int m, int n, int& waycount);
void up(int *matrix, int i , int j, int m1 , int n1, int m, int n, int& waycount);
void left(int *matrix, int i , int j, int m1 , int n1, int m, int n, int& waycount);
void right(int *matrix, int i , int j, int m1 , int n1, int m, int n, int& waycount);

//function to traverse down.
void down(int *matrix, int i , int j, int m1 , int n1, int m, int n, int& waycount)
{
	if(waycount >= 2) 
	//if boundary point is reached twice or more then function will return
		return;
	if(i < m-1 && matrix[n*(i+1) + j] == 1)	
	//checks if down traversal is possible or not
	{
		i = i+1;
		if((i == 0 || j == 0 || i == m-1 || j == n-1) && (i != m1 || j != n1)) 
		//Checks if exit point has been reached and increases waycounter by 1
		{
			waycount++;
		}
		else							
		//if it is not an exit point, then traverse all possible direction except reverse.
		{
			left(matrix,i,j,m1,n1,m,n, waycount);
			down(matrix,i,j,m1,n1,m,n, waycount);
			right(matrix,i,j,m1,n1,m,n, waycount);	
		}
	}
}

//function to traverse up.
void up(int *matrix, int i , int j, int m1 , int n1, int m, int n, int& waycount)
{
	if(waycount >= 2)	
	//if boundary point is reached twice or more then function will return
		return;
	if(i > 0 && matrix[n*(i-1) + j] == 1)	
	//checks if up traversal is possible or not
	{
		i = i-1;
		if((i == 0 || j == 0 || i == m-1 || j == n-1) && (i != m1 || j != n1))	
		//Checks if exit point has been reached and increases waycounter by 1
		{
			waycount++;
		}
		else							
		//if it is not an exit point, then traverse all possible direction except reverse.
		{
			right(matrix,i,j,m1,n1,m,n, waycount);
			up(matrix,i,j,m1,n1,m,n, waycount);
			left(matrix,i,j,m1,n1,m,n, waycount);
		}
	}
}
//function to traverse left.
void left(int *matrix, int i , int j, int m1 , int n1, int m, int n, int& waycount)
{
	if(waycount >= 2)
	//if boundary point is reached twice or more then function will return
		return;
	if(j > 0 && matrix[n*(i) + j-1] == 1)	
	//checks if left traversal is possible or not
	{
		j = j-1;
		if((i == 0 || j == 0 || i == m-1 || j == n-1) && (i != m1 || j != n1))	
		//Checks if exit point has been reached and increases waycounter by 1
		{
			waycount++;
		}
		else							
		//if it is not an exit point, then traverse all possible direction except reverse.
		{
			up(matrix,i,j,m1,n1,m,n, waycount);
			left(matrix,i,j,m1,n1,m,n, waycount);
			down(matrix,i,j,m1,n1,m,n, waycount);	
		}
	}
}
//function to traverse right.
void right(int *matrix, int i , int j, int m1 , int n1, int m, int n, int& waycount)
{
	if(waycount >= 2)	
	//if boundary point is reached twice or more then function will return
		return;
	if(j < n-1 && matrix[n*(i) + j+1] == 1)	
	//checks if right traversal is possible or not
	{
		j = j+1;
		if((i == 0 || j == 0 || i == m-1 || j == n-1) && (i != m1 || j != n1))	
		//Checks if exit point has been reached and increases waycounter by 1
		{
			waycount++;
		}
		else							
		//if it is not an exit point, then traverse all possible direction except reverse.
		{
			down(matrix,i,j,m1,n1,m,n, waycount);	
			right(matrix,i,j,m1,n1,m,n, waycount);
			up(matrix,i,j,m1,n1,m,n, waycount);
		}
	}
}

int main()
{	
	while(1)
	{
		int m,n,count = 0,m1,n1,i,j; 
		char t;
		//m is no. of rows, n is no. of columns, count is counter for boundary 'L'.
		// i and j are index variables, m1 and n1 will store coordinates of one boundary point
		// t will store the input character i.e. T or L.
		cout << "Enter no. of rows: ";		
		cin >> m;
		cout << "Enter no. of columns: ";		
		cin >> n;
		//if row no. is 0 && column no. is 0 then program will terminate.
		if(m == 0 && n == 0)
		{
			return 0;
		}

		if(m <= 0 || n <= 0)
		{
			cout << "Incorrect Input! Please try again\n";
			continue;
		}
		
		int matrix[m*n]; 
		//matrix will store 0 if char is 'T' and 1 if char is 'L'
		
		cout << "Enter Map: (No character other than T and L should be there)\n";
		for(i = 0; i < m; i++) 
		//this loop will store elements of matrix and will count no. of boundary 'L' and store coordinates of one boundary 'L'
		{
			for(j = 0; j < n; j++)
			{	
				scanf(" %c",&t);
				if(t == 'T' )
					matrix[n*i + j] = 0;
				else if(t == 'L')
					matrix[n*i + j] = 1;
				if((i == 0 || j == 0 || i == m-1 || j == n-1) && matrix[n*i + j] == 1)
				{
					m1 = i;
					n1 = j;
					count++;
				}
			}
		}

		if(count != 2) 
		//if no. of boundary 'L' is not exactly 2, then program will terminate printing badluck
		{
			cout << "Bad Luck!" << endl;
			continue;
		}

		//Initialisation of waycounter
		int waycount = 0;

		//Traversal in all possible directions
		left(matrix,m1,n1,m1,n1,m,n, waycount);
		right(matrix,m1,n1,m1,n1,m,n, waycount);
		up(matrix,m1,n1,m1,n1,m,n, waycount);
		down(matrix,m1,n1,m1,n1,m,n, waycount);

		//If no. of times boundary reached is exactly 1 then print Submitted else print Bad luck
		if( waycount == 1)
			printf("Submitted!\n");
		else
			printf("Bad Luck!\n");
	}
}