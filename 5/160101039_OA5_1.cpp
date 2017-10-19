#include <bits/stdc++.h>
using namespace std;
/*
Approach:
First Binary search will find the postition where no. should be inserted.
Then we will shift the elements upto that position in Insertion sort.
Finally sorted array will be there.
*/

//BinarySearch will return the position of element to be inserted.
//lb is the lower limit.
//ub is the upper limit.
//ele is the element whose postion needs to be found.
//comparisons is the no. of comparisons.
int BinarySearch(int *array, int lb, int ub, int ele, int& comparisons)
{
	if(ub < lb)		//If lower limit is greater than upper limit, then return lower limit.
		return lb;
	
	int pivot = (lb + ub)/2; 	//pivot will be middle of lower limit and upper limit.

	comparisons++;		//comparisons is incremented because a comparison is made in if statement.

	if(array[pivot] <= ele)		//if pivot element is less than or equal to the no. to be inserted then,
		return BinarySearch(array,pivot+1,ub,ele,comparisons); // check in right array of pivot 

	return	BinarySearch(array, lb, pivot-1,ele,comparisons);	//otherwise in left.

}

//insertsort will apply Insertion Sort and will return the total no. of comparisons made.
//N is the upper limit of array.
int insertsort(int *array , int N)
{
	int n = N+1, comparisons = 0;	//initialisation of variables.
	for (int i = 1; i < n; ++i)
	{
		int position = BinarySearch(array,0,i-1,array[i],comparisons);	//postion finding.

		for (int j = i; j > position; --j)
			swap(array[j],array[j-1]);			//Shifting of elements acc. to the postion found.
	}
	return comparisons;	//Finally total no. of comparisons made is returned.
}

int main()
{
	int N;		//N is the no. of array elements
	cout << "Input no. of elements in the sequence and then sequence:\n";
	cin >> N;	//Input for N.

	if(N == 0)
	{
		cout << "\nOutput:\nEmpty Sequence!\n";
		return 0;
	}

	int array[N];	//Declaration of array.

	for (int i = 0; i < N; ++i)
	{
		cin >> array[i];	//Input for array.
	}
	int comp = insertsort(array,N-1);	//Application of insertion sort on the array and "comp" will store the no. of comparisons made.

	cout << "\nOutput:\nComparisons: " << comp << endl << "Sorted Sequence: ";		//Printing the output.
	for (int i = 0; i < N; ++i)
	{
		cout << array[i] << " ";
	}
	cout << endl;

	return 0;
}