#include <bits/stdc++.h>
using namespace std;

int bubble1(int array[], int n)
{
	int count1 = 0;
	for(int i = 0; i < n - 1 ; i++)
	{
		for (int j = 0; j < n - 1 - i; ++j)
		{
			if(array[j] > array[j+1])
				swap(array[j],array[j+1]);
		}
		count1++;
	}
	return count1;
}
int bubble2(int array2[], int n)
{
	
	for(int i = 0; i < n - 1 ; i++)
	{
		bool sortchk = true;
		for (int j = 0; j < n - 1 - i; ++j)
		{
			if(array2[j] > array2[j+1])
			{
				swap(array2[j],array2[j+1]);
				sortchk = false;
			}

		}
		if(sortchk == true)
		{
			return (i);
		}
	}

}
int bubble3(int array3[], int n)
{
	for(int i = 0; i < n - 1 ; i++)
	{
		
		bool sortchk = true;
		if(i%2 == 0)
		for (int j = i/2; j < n - 1 - i/2; ++j)
		{
			if(array3[j] > array3[j+1])
			{
				swap(array3[j],array3[j+1]);
				sortchk = false;
			}
		}
		else
		for (int j = n-2-i/2; j >= i/2; --j)
		{
			if(array3[j+1] < array3[j])
			{
				swap(array3[j+1],array3[j]);
				sortchk = false;
			}
		}
		if(sortchk == true)
		{
			return (i);
		}
	}
}
int main()
{
	// int n;
	// cin >> n;

	// if(n == 0)
	// {
	// 	cout << "Empty array!" << endl;
	// 	return 0;
	// }


	// int array[n];
	// int array2[n];
	// int array3[n];



	// for(int i = 0; i< n ; i++)
	// {
	// 	cin >> array[i];
	// 	array3[i] = array2[i] = array[i];
	// }

	// if(n == 1)
	// {
	// 	cout << endl;
	// 	for (int i = 0; i < 3; ++i)
	// 	{
	// 		cout << "0" << endl << array[0] << endl;
	// 	}
	// 	return 0;
	// }

	// cout << endl;

	// int count1 = bubble1(array,n);

	// cout << count1 << endl;

	// for (int i = 0; i < n; ++i)
	// {
	// 	cout << array[i] << " ";
	// }

	// cout << endl;

	// int count2 = -bubble2(array2,n)-1+count1;

	// cout << count2 << endl;

	// for (int i = 0; i < n; ++i)
	// {
	// 	cout << array2[i] << " ";
	// }

	// cout << endl;

	// int count3 = -bubble3(array3,n) + count1 - 1;

	// cout << count3 << endl;

	// for (int i = 0; i < n; ++i)
	// {
	// 	cout << array3[i] << " ";
	// }

	// cout << endl;
	int a[] = {1,2,3,4,5,1};
	cout << bubble3(a,6);
}