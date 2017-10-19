#include <bits/stdc++.h>
using namespace std;

//This will print the heap.
void print_heap(int array[], int n)
{
	for (int i = 0; i < n; ++i)
	{
		cout << array[i];
		if(i != n-1)
			cout << " ";
	}
	cout << endl;
}

//This will min heapify the heap
void min_heapify(int array[],int root, int size)
{
	int L = 3*root + 1;
	int M = 3*root + 2;
	int R = 3*root + 3;

	if(L >= size)
		return;

	int smi = root;
	smi = array[smi] <= array[L] ? smi : L;

	if(M < size)
		smi = array[smi] <= array[M] ? smi : M;

	if(R < size)
		smi = array[smi] <= array[R] ? smi : R;

	if(smi != root)
	{
		swap(array[root],array[smi]);
		min_heapify(array, smi, size);
	}
}

//Insertion in min heap
void insert_heap(int array[], int& size, int x)
{
	if(size == 100)
	{
		cout << "Insertion cannot possible! heap size is full\n";
		return;
	}

	array[size] = x;
	int j = size;
	int parent = (size - 1)/3;
	while(parent >= 0 && array[parent] > array[j])
	{
		swap(array[parent], array[j]);
		j = (j-1)/3;
		parent = (j-1)/3;
	}
	size++;
}

//convert a normal array into minheap using minheapify
void Build_heap(int array[], int size)
{
	for (int i = size/3; i >= 0; --i)
	{
		min_heapify(array,i,size);
	}
}

//removal of min 
int del_min(int array[], int& size)
{
	if(size == 0)
	{
		cout << "Empty heap!\n";
		return INT_MAX;
	}
	int min = array[0];

	swap(array[0],array[size-1]);
	size--;
	min_heapify(array,0,size);

	return min;
}

int main()
{
	int hsize;	//heap size
	cin >> hsize;

	int array[100] = {0};

	for (int i = 0; i < hsize; ++i)
	{
		cin >> array[i];	//input taken
	}

	Build_heap(array,hsize);	//building of min heap
	print_heap(array, hsize);	//printing of min heap

	string word;				//word will store commands

	while(cin >> word)
	{
		if(word == "i")			//insert command
		{
			int d;
			cin >> d;
			insert_heap(array, hsize,d);
			cout << endl << d << " is inserted\n";
			print_heap(array, hsize);
		}
		else if(word == "d")	//delete command
		{
			int min = del_min(array,hsize);
			if(min != INT_MAX)
				cout << endl << min << " is deleted\n";
			print_heap(array, hsize);
		}
		else if(word == "exit")	//function will exit
		{
			break;
		}
		else
		{
			cout << "\nInvalid command!\n";
		}
	}

}