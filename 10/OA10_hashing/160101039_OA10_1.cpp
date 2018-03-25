#include <iostream>
using namespace std;

//This function will store hash value of each substring starting from 0 index and store it in a hash table
int hash_val(string str, int *hash_table, int m, int base, int prime) {
	m = m-1;
	if(m == 0)
		return str[0]%prime;
	return ((hash_table[m-1]*base)%prime+str[m]%prime)%prime;
}

//This function will extract hash value of a substring from ith index to jth index from hash table
int hash_val_substr(int *hash_table, int i, int j, int base, int prime) {

	i = i-1;
	if(i < 0)
		return hash_table[j];
	int x = hash_table[i],y = hash_table[j];
	for (int q = 0; q < j-i; ++q) {
		x = (base*x)%prime;
	}
	return (y-x+prime)%prime;
}

int main()
{
	string str; //Variable for storing input string.
	int N, base=11, prime=15487469;	//N is the no. of test cases
	cin >> str >> N;				//input of test cases and string 
	int len = str.length();			//length of the input string
	int *hash_table = new int [len];	//Hash table
	for (int i = 0; i < len; ++i) {		//storing in hash table
		hash_table[i] = hash_val(str,hash_table,i+1,base,prime);
	}
	int ind_1s, ind_1e;
	int ind_2s, ind_2e;

	for (int _ = 0; _ < N; ++_)
	{
		cin >> ind_1s >> ind_1e >> ind_2s >> ind_2e; //input for starting and ending indices
		int hash_value1 = hash_val_substr(hash_table,ind_1s-1,ind_1e-1,base,prime);	//calculating hash value of each subtring
		int hash_value2 = hash_val_substr(hash_table,ind_2s-1,ind_2e-1,base,prime);

		if(hash_value1 != hash_value2)	//if two substring do not have same hash value then print "NO"
			cout << "NO\n";
		else						//If they have same hash value then check for each character as there may be collision in hash values
		{
			if(str.compare(ind_1s-1,ind_1e - ind_1s + 1, str, ind_2s-1, ind_2e - ind_2s + 1 ) == 0) //if they are same then print "YES"
				cout << "YES\n";
			else
				cout << "NO\n";	//print "NO"
		} 	
	}
}