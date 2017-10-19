#include <bits/stdc++.h>
using namespace std;

void Maxheapify(int array[], int root, int n)
{
	int L = 2*root + 1;
	int R = 2*root + 2;

	if(L > n)
		return;
	int k = array[L] > array[root] ? L : root;
	if(R <= n)
		k = array[k] > array[R] ? k : R;
	if(k != root)
	{
		swap(array[k], array[root]);
		Maxheapify(array,k,n);
	}
}
void BuildMaxHeap(int array[], int N)
{
	for (int i = N/2; i >= 0; --i)
	{
		Maxheapify(array,i,N);
	}
}

void heapsort(int array[], int N)
{
	BuildMaxHeap(array, N);
	for (int i = N; i >= 0; )
	{
		swap(array[0],array[i]);
		i--;
		Maxheapify(array,0,i);	
	}
}
int main()
{
	int N;
	cin >> N;
	int array[N];
	for (int i = 0; i < N; ++i)
	{
		cin >> array[i];
	}
	heapsort(array,N-1);
	int k;
	cin >> k;
	for (int i = 0; i < k; ++i)
	{
		cout << array[i] << "\t" ;
	}
	cout << endl;

}