#include <bits/stdc++.h>
using namespace std;

int main()
{
	srand(time(NULL));

	int N;
	cin >> N;

	cout << N << endl;

	for (int i = 0; i < N; ++i)
	{
		cout << rand()%100 << " ";
	}
	cout << endl;
	cout << rand()%100 << endl;
	cout << rand()%100 << endl;
}