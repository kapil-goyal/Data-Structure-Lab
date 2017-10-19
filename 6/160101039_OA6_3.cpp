#include <bits/stdc++.h>
using namespace std;
/*
	Algorithm:
	1. Observations:
		i) Whenever insert operation is there, it does not need any error checking
	   ii) Whenever removeMin option is there, if remove min can not happen(because heap is empty), then 1 extra insert operation is needed.
	  iii) Whenever getMin operation is there, some remove min operations are needed and if no. is not in heap 1 extra insert operation is needed.
	2. So acc. to our operations we will make counter for removeMin operations and getMin operations.
	3. Since getMin operations need two error correcting operations we will make a struct for getmin.
	4. We will maintain a heap which will check validity of each operation during input and set the counters accordingly.
	5. Now we will print acc. to the valid or invalid operations and their counters. 
*/

//Insert an element in heap.
void insertMinHeap(int array[], int& heapsize, int x)
{
	int j = heapsize+1;
	array[j] = x;
	int parent = (j-1)/2;
	while(parent >= 0 && array[j] < array[parent])
	{
		swap(array[j],array[parent]);
		j = (j-1)/2;
		parent = (j-1)/2;
	}
	heapsize++;
}

//Min heapify function
void Minheapify(int array[], int root, int& heapsize)
{
	int L = 2*root + 1;
	int R = 2*root + 2;

	if(L > heapsize)
		return;
	int k = array[L] < array[root] ? L : root;
	if(R <= heapsize)
		k = array[k] < array[R] ? k : R;
	if(k != root)
	{
		swap(array[k], array[root]);
		Minheapify(array,k,heapsize);
	}
}

//Extract min will return minimum value in heap.
int extractMin(int array[], int& heapsize)
{
	if(heapsize == -1)
		return INT_MAX;
	int min = array[0];
	swap(array[0], array[heapsize]);
	heapsize--;
	Minheapify(array,0,heapsize);

	return min;
}

//Struct for getMin operations
struct getMin
{
	int remoMin;
	int insert;	
};

//Initialization of getmin operations array
void initializeGMin(getMin GMin[],int N)
{
	for (int i = 0; i < N; ++i)
	{
		GMin[i].remoMin = 0;
		GMin[i].insert = 0;
	}
}

int main()
{
	int N, heapsize=-1, array[100000], minOper = 0; //N is the no. of input operations and minOper are extra operations needed.
	cout << "Input: \n";
	cin >> N;

	string inputOper[N];	//it will store input operations
	int inpNo[N] = {0};		//it will store input no. corr to input operations

	int rem[N] = {0};		//counter for remove min operations
	getMin GMin[N];			//counter for get min operations
	initializeGMin(GMin, N);	

	for (int i = 0; i < N; ++i)
	{
		cin >> inputOper[i];

		if(inputOper[i] == "removeMin") //if input is remove min
		{
			if(extractMin(array, heapsize) == INT_MAX)	//if remove min is not possible
			{
				rem[i] = 1;			//increase remove min counter
				minOper += 1;		//increase minOper counter
			}
			continue;
		}
		if(inputOper[i] == "insert")	//if input is insert
		{
			cin >> inpNo[i];
			insertMinHeap(array, heapsize, inpNo[i]);	//insert the given no.
		}

		if(inputOper[i] == "getMin")	//if input is getMin
		{
			cin >> inpNo[i];	//get the input no.
			while(heapsize != -1 && array[0] < inpNo[i]) //check if input no. is present in heap and cal remove min operations 
			{
				extractMin(array, heapsize);
				GMin[i].remoMin += 1;
				minOper += 1;
			}
			if((heapsize != -1 && array[0] != inpNo[i]) || heapsize == -1) // if input no. is not present then increase counter for getmin operation
			{
				GMin[i].insert = 1;
				insertMinHeap(array, heapsize, inpNo[i]);
				minOper += 1;
			}

		}

	}

	cout << "\nOutput: \n"<< minOper + N << endl; //print final total no. of corrected operations

	for (int i = 0; i < N; ++i) //finally printing of input operations alongwith their corrections.
	{
		if(inputOper[i] == "insert") 
		{
			cout << inputOper[i] << " " << inpNo[i] << endl;
		}

		if(inputOper[i] == "removeMin")
		{
			if(rem[i])
				cout << "insert 0\n";

			cout << inputOper[i] << endl;
		}

		if(inputOper[i] == "getMin")
		{
			for (int j = 0; j < GMin[i].remoMin; ++j)
			{
				cout << "removeMin\n";
			}
			if(GMin[i].insert)
				cout << "insert " << inpNo[i] << endl;

			cout << inputOper[i] << " " << inpNo[i] << endl;
		}
	}

	return 0;
}