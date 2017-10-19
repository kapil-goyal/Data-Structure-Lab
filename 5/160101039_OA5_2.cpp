#include <bits/stdc++.h>
using namespace std;

/*
Approach:
Merge function will merge two sorted arrays and will count the no. of inversions w.r.t one array to the other.
mergesort will apply merge sort and whenever a sub array is sorted, its no. of inversions are counted.
Finally we will have no. of inversion in the array and sorted array.
*/


/*
Merge function will merge two sorted arrays and will count the no. of inversions w.r.t one array to the other.
lb is lower limit
mid is the separting index
ub is upper limit
Inversions will count no. of inversions.
*/
void Merge (int *array, int lb, int mid, int ub, int& Inversions)
{
	if(lb >= ub)
		return;
	int n1 = mid-lb+1;	//no. of elements in left array.
	int n2 = ub - mid;	//no. of elements in right array.

	int array1[n1+1], array2[n2+1];	//Declaration of arrays.

	for (int i = lb; i < lb+n1; ++i)
	{
		array1[i-lb] = array[i];	//copying of left array.
	}
	array1[n1] = INT_MAX;

	for (int i = mid+1; i < mid+1+n2; ++i)
	{
		array2[i-mid-1] = array[i];	//copying of right array.
	}
	array2[n2] = INT_MAX;

	//Finally merging and counting of inversions is done.
	int i=0, j = 0, k = 0;
	while(array1[i] != INT_MAX || array2[j] != INT_MAX)
	{
		if(array1[i] <= array2[j])
		{
			array[k+lb] = array1[i];
			i++;k++;
		}
		else
		{
			array[k+lb] = array2[j];
			j++;k++;
			Inversions += n1 - i;	//Counting of inversions.
		}
	}
}

/*
mergesort will apply merge sort and whenever a sub array is sorted, its no. of inversions are counted.
lb is lower limit.
ub is upper limit.
Inversions will count inversions.
*/
void mergesort(int *array, int lb, int ub, int &Inversions)
{
	if(lb >= ub)	//Base case.
		return;
	int mid = (lb+ub)/2;	//Separting index.
	mergesort(array,lb,mid, Inversions);	//Recursive call for sorting left sub array.
	mergesort(array,mid+1,ub, Inversions);	//Recursive call for sorting right sub array.
	Merge(array,lb,mid,ub, Inversions);		//merging of two arrays.
}

int main()
{
	//N is the no. of elements in the array.
	int N, Inversions = 0;	//Declaration of variables

	cout << "Input no. of elements in sequence and the sequence:\n";
	cin >> N;	//Input for N.

	if(N == 0)
	{
		cout << "\nOutput:\nEmpty Sequence!\n";
		return 0;
	}

	int array[N];	//Declaration of array.
	
	for (int i = 0; i < N; ++i)
	{
		cin >> array[i];	//Input for array elements.
	}
	mergesort(array,0,N-1,Inversions);	//Application of mergesort.

	//Finally printing of output.
	cout << "\nOutput:\nNo. of Inversions: "<<Inversions << endl;
}