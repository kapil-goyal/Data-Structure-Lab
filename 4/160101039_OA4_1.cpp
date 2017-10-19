#include <bits/stdc++.h>
using namespace std;

//This function will change the array elements with diffence between array element and its next neighbour.
void reduce(int array[], int N)
{
	for (int i = 0; i < N-1; ++i)
	{
		array[i] = array[i+1] - array[i];
	}
};

//Bubble sort with improvement.
void bsort(int array[], int n)
{
	for(int i = 0; i < n - 1 ; i++)
	{
		bool sortchk = true;
		for (int j = 0; j < n - 1 - i; ++j)
		{
			if(array[j] > array[j+1])
			{
				swap(array[j],array[j+1]);
				sortchk = false;
			}
		}
		if(sortchk == true)
		{
			return;
		}
	}
}

int main()
{
	int N;
	cout << "Enter no. of elements: ";
	cin >> N;
	if(N == 0)
	{
		cout << "Empty array!\n";
		return 0;
	}
	cout << "Enter elements:\n";

	int array[N];

	for (int i = 0; i < N; ++i) //Storing of array elements
	{
		cin >> array[i];
	}
	while(N > 1)				//Application of sorting and reduce while no. of elements are greater than 1
	{
		bsort(array, N);
		reduce(array, N);
		N--;
	}

	//Finally printing of output.
	cout << endl <<"Output:\n" <<  array[0] << endl;

}