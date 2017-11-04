#include <iostream>
using namespace std;

int hash_val(string str, int m, int n, int base, int prime) {
	m = m-1;
	n = n-1;
	int result=0;
	for (int i = 0; i <= n-m; ++i) {
		result= (base*result + str[m+i])%prime;
	}
	return result;
}

int hash_val_substr(int *hash_val_arr, int i, int j, int base, int prime) {

	i = i-1;
	if(i < 0)
		return hash_val_arr[j];
	int x = hash_val_arr[i],y = hash_val_arr[j];
	for (int _ = 0; _ < j-i; ++_) {
		x = (base*x);//%prime;
	}
	return (y-x%prime)%prime;
}

int main()
{
	string str;
	int N, base=26, prime=23;
	cin >> str >> N;
	int len = str.length();
	int *hash_val_arr = new int [len];
	for (int i = 0; i < len; ++i) {
		hash_val_arr[i] = hash_val(str,1,i+1,base,prime);
	}
	int ind_1s, ind_1e;
	int ind_2s, ind_2e;

	for (int _ = 0; _ < N; ++_)
	{
		cin >> ind_1s >> ind_1e >> ind_2s >> ind_2e;
		int hash_value1 = hash_val_substr(hash_val_arr,ind_1s-1,ind_1e-1,base,prime);
		int hash_value2 = hash_val_substr(hash_val_arr,ind_2s-1,ind_2e-1,base,prime);

		if(hash_value1 != hash_value2)
			cout << "NO\n";
		else
		{
			int i;
			for (i = 0; i < ind_2e - ind_2s; ++i)
			{
				if(str[i+ind_1s] != str[i+ind_2s])
				{
					cout << "NO\n";
					break;
				}
			}
			if(i == ind_2e - ind_2s)
				cout << "YES\n";
		} 	
	}
}