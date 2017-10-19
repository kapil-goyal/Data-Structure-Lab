#include <bits/stdc++.h>
using namespace std;
/*
	Caution:
	City inputs are case sensitive. i.e. Delhi and delhi are considered to be different cities.
	Road Info, Fare info and no. of cities are assumed to be correct and as per the value of N, R, F.
*/

//Search string in the array of strings of cities.
//It returns the index of city to be searched. 
int searchstr(string mystr[],string str ,int sindex)
{
	for (int i = 0; i < sindex ; ++i)
	{
		if(str == mystr[i])
			return i;
	}
	return sindex;
}

//Struct for array type sparse matrix.
struct Roadinfo
{
	int row,col,data;
};

//Struct for Linked list type sparse matrix.
struct Fareinfo
{
	int row,col,data;
	Fareinfo *down, *right;
};

//Class which will store heads, no. of cities N, insertcell function to insert a node, printmax function to print maximum total fare.
class SparsematrixLL
{

private:
	int N;	//N is the no. of cities to be stored.
	Fareinfo **heads; //heads will point to head for each city.

public:
	//Constructor
	SparsematrixLL(Fareinfo **head, int n)
	{
		heads = head;
		N = n;
	}

	//Inserts a node in the matrix with indices (r,c) and data d
	void insertcell(int r, int c, int d );

	void print();	//Print func prints array columnwise. (Just for Checking)

	//printmax function will print maximum total fare and corresponding cities.
	void printmax(Roadinfo matrix[], string str[],int R);
};

//Inserts a node in the matrix with indices (r,c) and data d
void SparsematrixLL::insertcell(int r, int c, int d)
{
	//First insertion in column is carried out.
	Fareinfo *prevcell = heads[c];
	Fareinfo *curcell = heads[c]->down;

	while(curcell != heads[c] && curcell->row < r)
	{
		prevcell = curcell;
		curcell = curcell->down;
	}
	//new node will be inserted between prevcell and curcell.


	//Now insertion in row is carried out.
	Fareinfo *prevcell2 = heads[r];
	Fareinfo *curcell2 = heads[r]->right;

	while(curcell2 != heads[r] && curcell2->col < c)
	{
		prevcell2 = curcell2;
		curcell2 = curcell2->right;
	}
	//new node will be inserted between prevcell2 and curcell2.

	//Creation of new node.
	Fareinfo *temp = new Fareinfo;
	temp->row = r;
	temp->col = c;
	temp->data = d;

	//Finally insertion in row and column.
	prevcell->down = temp;
	temp->down = curcell;
	prevcell2->right = temp;
	temp->right = curcell2;
}

//Print func prints array columnwise. (Just for Checking)
void SparsematrixLL::print()
{	
	for (int i = 1; i < N; ++i)
	{
		Fareinfo *temp = heads[i]->down;
		while(temp != heads[i])
		{
			cout << temp->row << "|" << temp->col << "|" << temp->data << endl;
			temp = temp->down;
		}
		cout << endl;
	}
}

//printmax function will print maximum total fare and corresponding cities.
void SparsematrixLL::printmax(Roadinfo matrix[], string str[],int R)
{
	//rindex and cindex are indices of max fare city obtained and max is the value of maximum fare.
	int rindex, cindex;
	int max =0;

	//This for loop will match the road info and fare info and then find the max.
	for (int i = 0; i < R; ++i)
	{
		int r = matrix[i].row;
		
		Fareinfo *temp = heads[r]->right;
		while(temp != heads[r])
		{
			if(matrix[i].col == temp->col && max < (matrix[i].data)*(temp->data))
			{
				max = (matrix[i].data)*(temp->data);
				rindex = r-1;
				cindex = matrix[i].col-1;
			}
			temp = temp->right;
		}
	}
	//This for loop does the same thing except it checks for tranpose of road info. 
	for (int i = 0; i < R; ++i)
	{
		int r = matrix[i].col;
		
		Fareinfo *temp = heads[r]->right;
		while(temp != heads[r])
		{
			if(matrix[i].row == temp->col && max < (matrix[i].data)*(temp->data))
			{
				max = (matrix[i].data)*(temp->data);
				rindex = r-1;
				cindex = matrix[i].row-1;
			}
			temp = temp->right;
		}
	}
	//finally max value and corresponding indices are obtained.
	if(max == 0) //if max is zero means no road info and fare info matches.
	{
		cout << "Error : Insufficient Information!\n";
		exit(0);
	}

	//finally printing is done.
	cout << str[rindex] << " " << str[cindex] << " "<< max << endl;
}

//This function will initialize heads. 
void initialize(Fareinfo **heads, int N)
{
	for (int i = 0; i < N+1; ++i)
	{
		heads[i] = new Fareinfo;
		heads[i]->row = 0;
		heads[i]->col = 0;
		heads[i]->data = 0;
		heads[i]->down = heads[i];
		heads[i]->right = heads[i];
	}
}

int main()
{
	int N, R, F, sindex = 0;
	cout << "Input:\n";
	cin >> N >> R >> F; //N, R, F are taken as inputs.
	if(N == 0 || N == 1)
	{
		cout << "Wrong Input: No city to compare with!\n";
		return 0;
	}

	string citstr[N];	//This will store different cities in an array. 
	Roadinfo matrix1[R]; //Now Sparse matrix array for road info is made.

	Fareinfo **heads;				//Declaration of heads for Sparse matrix using linked list
	heads = new Fareinfo*[N+1];
	initialize(heads, N);			//Initialization of heads.
	SparsematrixLL matrix2(heads,N+1); 	//Declaration of object matrix2(Sparse matrix using linked list)

	for (int i = 0; i < R; ++i)		//for loop initialization for Road info
	{
		int r;
		string str1,str2;
		cin >> str1 >> str2 >> r;	//Inputs are taken and cities are checked if they are already present or not.

		int rindex = searchstr(citstr,str1,sindex);	

		if(rindex == sindex)
		{
			citstr[sindex] = str1;
			sindex++;
		}

		int cindex = searchstr(citstr,str2,sindex);

		if(cindex == sindex)
		{
			citstr[sindex] = str2;
			sindex++;
		}

		//Finally road info is stored.
		matrix1[i].row = rindex+1;
		matrix1[i].col = cindex+1;
		matrix1[i].data = r;

	}

	for (int i = 0; i < F; ++i) //For loop initialization for Fare info.
	{
		int r;
		string str1,str2;
		cin >> str1 >> str2 >> r;	//Inputs are taken and cities are checked if they are already present or not.

		int rindex = searchstr(citstr,str1,sindex);

		if(rindex == sindex)
		{
			citstr[sindex] = str1;
			sindex++;
		}

		int cindex = searchstr(citstr,str2,sindex);

		if(cindex == sindex)
		{
			citstr[sindex] = str2;
			sindex++;
		}

		//Finally fare info is stored.
		matrix2.insertcell(rindex+1,cindex+1,r);
	}
	//Final printing of output.
	cout << "\nOutput:\n";
	matrix2.printmax(matrix1,citstr,R);
}