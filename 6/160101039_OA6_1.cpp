#include <bits/stdc++.h>
using namespace std;
/*
	Algorithm:
	1. Make 26 x 26 array.
	2. If alphabets[i][j] == 1, this means that ith alphabet is smaller than jth alphabet.
	3. Set the value of alphabets array initally to 0 and then acc. to input.
	4. After setting acc. to the input, Now check if alphabets[i][j] == 1 and alphabets[j][k] == 1, then set alphabets[i][k] = 1
	   This is done because if a < b and b < c then a < c.
	5. Now check if alphabets[i][i] == 1 , if it is true this means that violation of sequence has occured somewhere.
	   That's all.
*/

//Check if sequence is wrong or not. Step 5. of Algorithm.
bool alphaCheck(int alphabets[26][26])
{
	for (int i = 0; i < 26; ++i)
	{
		if(alphabets[i][i] == 1)
			return false;
	}
	return true;
}

//This function does step no. 4 of our algorithm.
void realocate(int alphabets[26][26])
{
	for (int i = 0; i < 26; ++i)
	{
		for (int j = 0; j < 26; ++j)
		{
			if(i != j  && alphabets[i][j] == 1)
			{
				for (int k = 0; k < 26; ++k)
				{
					if(alphabets[j][k] == 1)
						alphabets[i][k] = 1;
				}
			}
		}
	}
}

int main()
{
	int alphabets[26][26] = {0}; //step no. 1 of Algo

	int N; //N is the no. of words.
	cin >> N;

	string word[N];

	for (int i = 0; i < N; ++i)
	{
		cin >> word[i];		//Input taken
	}

	for (int i = 0; i < N; ++i) //Step No. 3 of algo
	{
		for (int j = 0; word[i][j] != '\0' ; ++j)
		{
			for (int k = j+1; word[i][k] != '\0' ; ++k)
			{
				if(word[i][j] != word[i][k])
					alphabets[word[i][j] - 'a'][word[i][k] - 'a'] = 1;
			}
		}
	}

	//Step no. 4
	realocate(alphabets);

	if(alphaCheck(alphabets))	//Step No. 5
		cout << "Possible\n";
	else
		cout << "Impossible\n";

	return 0;
}