#include <bits/stdc++.h>
using namespace std;
void binsertort(int *array, int lb, int ub, int &comp2);
int binarysearch(int *array, int lb, int ub, int x, int &comp2);

void randarray(int *array, int N)
{
	for (int i = 0; i < N; ++i)
	{
		int d = rand()%1000;
		array[i] = d;
	}
}
void merge(int *array, int lb, int mid, int ub, int &comp)
{
	int n1 = mid - lb + 1;
	int n2 = ub - mid;

	int a1[n1+1];
	int a2[n2+1];

	for (int i = lb; i < n1 + lb ; ++i)
	{
		a1[i-lb] = array[i];
	}
	a1[n1] = INT_MAX;

	for (int i = mid+1; i < n2 + mid+1 ; ++i)
	{
		a2[i-mid-1] = array[i];
	}
	a2[n2] = INT_MAX;

	int j = 0, i = 0, k = lb;

	while(a1[j] != INT_MAX || a2[i] != INT_MAX)
	{
		comp++;
		if(a1[j] <= a2[i])
		{
			array[k] = a1[j];
			j++;
			k++;
		}
		else
		{
			array[k] = a2[i];
			i++;
			k++;
		}
	}
}
void modmergesort(int *array, int lb, int ub, int &comp)
{
	if(ub - lb > 55)
	{
		int mid = (ub + lb)/2;

		modmergesort(array,lb,mid, comp);
		modmergesort(array,mid+1,ub, comp);
		merge(array,lb,mid,ub,comp);
	}
	else
	{
		binsertort(array,lb, ub, comp);
	}
}

int binarysearch(int *array, int lb, int ub, int x, int &comp2)
{
	if(lb > ub)
		return lb;

	int pivot = (lb + ub)/2;

	comp2++;
	if(array[pivot] <= x)
		return binarysearch(array,pivot+1,ub,x,comp2);

	return binarysearch(array,lb,pivot-1,x,comp2);
}
void binsertort(int *array, int lb, int ub, int &comp2)
{
	for (int i = lb + 1; i <= ub; ++i)
	{
		int position = binarysearch(array,lb,i-1,array[i],comp2);
		int j = i-1;
		int key = array[i];
		while(j >= position)
		{
			array[j+1] = array[j];
			j--;
		}
		array[position] = key;
	}
}
int main()
{
	int N, comp = 0;
	cin >> N;
	srand(time(NULL));

	int array[N];

	randarray(array,N);
	modmergesort(array,0,N-1,comp);

	cout << "Comparisons: " << comp << " " << endl;

	cout << "Sequence: ";
	for (int i = 0; i < N; ++i)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}