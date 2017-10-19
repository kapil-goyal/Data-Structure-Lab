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
	int min = array[0];

	swap(array[0],array[size-1]);
	size--;
	min_heapify(array,0,size);

	return min;
}

//struct for heap of ksmall elements
struct ksm
{
	int key;
	int index;
};

//insertion in ksmall heap
void insert_ksm(ksm array[], int& size, int x, int i)
{
	array[size].key = x;
	array[size].index = i;
	int j = size;
	int parent = (size - 1)/3;
	while(parent >= 0 && array[parent].key > array[j].key)
	{
		swap(array[parent], array[j]);
		j = (j-1)/3;
		parent = (j-1)/3;
	}
	size++;
}
//min heapify for ksm heap
void min_heapify_ksm(ksm array[],int root, int size)
{
	int L = 3*root + 1;
	int M = 3*root + 2;
	int R = 3*root + 3;

	if(L >= size)
		return;

	int smi = root;
	smi = array[smi].key <= array[L].key ? smi : L;

	if(M < size)
		smi = array[smi].key <= array[M].key ? smi : M;

	if(R < size)
		smi = array[smi].key <= array[R].key ? smi : R;

	if(smi != root)
	{
		swap(array[root],array[smi]);
		min_heapify_ksm(array, smi, size);
	}
}
//extraction of k small heap
ksm del_min_ksm(ksm array[], int& size)
{
	ksm min = array[0];

	swap(array[0],array[size-1]);
	size--;
	min_heapify_ksm(array,0,size);

	return min;
}
//ksmallest function
void ksmallest(int array[], int size, int k)
{
	if(size == 0)
		return;

	if(k > size)
	{
		cout << "k cannot be greater than " << size << endl;
		cout << "printing " << size << " smallest elements.\n\n";
		k = size;
	}

	ksm ksmall_heap[size];
	int ksize = 0;

	insert_ksm(ksmall_heap, ksize, array[0], 0);
	ksm min = del_min_ksm(ksmall_heap, ksize);
	cout << min.key;

	for(int i = 1; i < k; i++)
	{
		cout << " ";

		if(3*min.index+1 < size)
			insert_ksm(ksmall_heap, ksize, array[3*min.index+1], 3*min.index+1);
		if(3*min.index+2 < size)
			insert_ksm(ksmall_heap, ksize, array[3*min.index+2], 3*min.index+2);
		if(3*min.index+3 < size)
			insert_ksm(ksmall_heap, ksize, array[3*min.index+3], 3*min.index+3);

		min = del_min_ksm(ksmall_heap, ksize);
		cout << min.key;
	}
	cout << endl;
}

//recursive function for printing elements less than a
void recur_print_small(int array[], int i, int size, int a)
{
	if(i >= size)
		return;

	if(array[i] <= a)
	{	
		cout << array[i] << " ";
		recur_print_small(array,3*i+1,size,a);
		recur_print_small(array,3*i+2,size,a);
		recur_print_small(array,3*i+3,size,a);
	}
}

//printing of a small elements
void printsmall(int array[], int size, int a)
{
	if(size == 0)
		return;

	recur_print_small(array,0,size,a);
	cout << endl;
}


int main()
{
	int hsize;	//heap size
	cout << "Input: \n";
	cin >> hsize;

	int array[hsize];

	for (int i = 0; i < hsize; ++i)
	{
		cin >> array[i];	//input taken
	}
	int k,a;
	cin >> k >> a;

	Build_heap(array,hsize);	//building of min heap

	cout << "\nOutput: \n";

	cout << endl;
	print_heap(array, hsize);	//printing of min heap

	cout << endl;
	ksmallest(array, hsize, k);	//printing of k small elements

	cout << endl;
	print_heap(array, hsize);	//printing of min heap

	cout << endl;
	printsmall(array,hsize, a);	//printing of elements smaller than a

	cout << endl;
	print_heap(array, hsize);	//printing of min heap
}