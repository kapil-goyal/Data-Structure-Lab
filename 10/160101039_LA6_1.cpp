#include <bits/stdc++.h>
using namespace std;
void initialize(int Linhash[], int Quadhash[], int Doubhash[],int m)
{
	for (int i = 0; i < m; ++i)
	{
		Linhash[i] = 0;
		Quadhash[i] = 0;
		Doubhash[i] = 0;
	}
};

void insert(int Linhash[], int Quadhash[], int Doubhash[], int &lincol, int &quadcol, int &doubcol, int m, int x, int& i1, int& i2, int& i3) 
{
	int i=0;
	int hash1 = x%m + i;
	while(Linhash[hash1] != 0 && Linhash[hash1] != -1 )
	{
		i++;
		hash1 = (x%m + i)%m;
		lincol++; 
	}
	if(i<m)
	{
		Linhash[hash1] = x;
		i1++;
		cout << x <<" INSERTED AT INDEX "<<hash1<<" IN LINEAR PROBING\n";
	}
	else
	{
		cout << x << " CANNOT BE INSERTED IN LINEAR PROBING\n";
	}

	int j=0;
	hash1 = x%m + j+ 3*j*j;
	while(Quadhash[hash1] != 0 && Quadhash[hash1] != -1 )
	{
		j++;
		hash1 = (x%m + j+ 3*j*j)%m;
		quadcol++; 
	}
	if(j<m)
	{
		Quadhash[hash1] = x;
		i2++;
		cout << x <<" INSERTED AT INDEX "<<hash1<<" IN QUADRATIC PROBING\n";
	}
	else
	{
		cout << x << " CANNOT BE INSERTED IN QUADRATIC PROBING\n";
	}

	int k=0;
	hash1 = x%m;
	int hash2 = 1 + x%(m-1);
	int hash = hash1 + k*hash2;
	while(Doubhash[hash] != -0 && Doubhash[hash] != -1 )
	{
		k++;
		hash = (hash1 + k*hash2)%m;
		doubcol++; 
	}
	if(k<m)
	{
		Doubhash[hash] = x;
		i3++;
		cout << x <<" INSERTED AT INDEX "<<hash<<" IN DOUBLE HASHING\n";
	}
	else
	{
		cout << x << " CANNOT BE INSERTED IN DOUBLE HASHING\n";
	}
}
void search(int Linhash[], int Quadhash[], int Doubhash[],int m, int x)
{
	int i=0;
	int hash1 = x%m + i;
	while(Linhash[hash1] != -0 && Linhash[hash1] != -1 && Linhash[hash1] != x)
	{
		i++;
		hash1 = (x%m + i)%m;
		// lincol++; 
	}
	if(Linhash[hash1] == x)
	{
		// Linhash[hash1] = x;
		cout << x <<" FOUND AT INDEX "<<hash1<<" IN LINEAR PROBING\n";
	}
	else
	{
		cout << x << " NOT PRESENT IN LINEAR PROBING\n";
	}

	int j=0;
	hash1 = x%m + j+ 3*j*j;
	while(Quadhash[hash1] != -0 && Quadhash[hash1] != -1 && Quadhash[hash1] != x )
	{
		j++;
		hash1 = (x%m + j+ 3*j*j)%m;
		// quadcol++; 
	}
	if(Quadhash[hash1] == x)
	{
		// Quadhash[hash1] = x;
		cout << x <<" FOUND AT INDEX "<<hash1<<" IN QUADRATIC PROBING\n";
	}
	else
	{
		cout << x << " NOT PRESENT IN QUADRATIC PROBING\n";
	}

	int k=0;
	hash1 = x%m;
	int hash2 = 1 + x%(m-1);
	int hash = hash1 + k*hash2;
	while(Doubhash[hash] != 0 && Doubhash[hash] != -1 && Doubhash[hash] != x )
	{
		k++;
		hash = (hash1 + k*hash2)%m;
		// doubcol++; 
	}
	if(Doubhash[hash] == x)
	{
		// Doubhash[hash] = x;
		cout << x <<" FOUND AT INDEX "<<hash<<" IN DOUBLE HASHING\n";
	}
	else
	{
		cout << x << " NOT PRESENT IN DOUBLE HASHING\n";
	}
}

void del(int Linhash[], int Quadhash[], int Doubhash[],int m, int x, int& i1, int& i2, int& i3)
{
	int i=0;
	int hash1 = x%m + i;
	while(Linhash[hash1] != 0 && Linhash[hash1] != -1 && Linhash[hash1] != x)
	{
		i++;
		hash1 = (x%m + i)%m;
		// lincol++; 
	}
	if(Linhash[hash1] == x)
	{
		// Linhash[hash1] = x;
		cout << x <<" DELETED FROM INDEX "<<hash1<<" IN LINEAR PROBING\n";
		// i1--;
		Linhash[hash1] = -1;
	}
	else
	{
		cout << x << " CANNOT BE DELETED IN LINEAR PROBING\n";
	}

	int j=0;
	hash1 = x%m + j+ 3*j*j;
	while(Quadhash[hash1] != -0 && Quadhash[hash1] != -1 && Quadhash[hash1] != x )
	{
		j++;
		hash1 = (x%m + j+ 3*j*j)%m;
		// quadcol++; 
	}
	if(Quadhash[hash1] == x)
	{
		Quadhash[hash1] = -1;
		// i2--;
		cout << x <<" DELETED FROM INDEX "<<hash1<<" IN QUADRATIC PROBING\n";
	}
	else
	{
		cout << x << " CANNOT BE DELETED IN QUADRATIC PROBING\n";
	}

	int k=0;
	hash1 = x%m;
	int hash2 = 1 + x%(m-1);
	int hash = hash1 + k*hash2;
	while(Doubhash[hash] != 0 && Doubhash[hash] != -1 && Doubhash[hash] != x )
	{
		k++;
		hash = (hash1 + k*hash2)%m;
		// doubcol++; 
	}
	if(Doubhash[hash] == x)
	{
		Doubhash[hash] = -1;
		// i3--;
		cout << x <<" DELETED FROM INDEX "<<hash<<" IN DOUBLE HASHING\n";
	}
	else
	{
		cout << x << " CANNOT BE DELETED IN DOUBLE HASHING\n";
	}
}

int main()
{
	int n,m;
	cin >> n >> m;

	int Linhash[m],lincol=0,i1=0;
	int Quadhash[m], quadcol=0,i2=0;
	int Doubhash[m], doubcol=0,i3=0;

	initialize(Linhash,Quadhash,Doubhash,m);

	string word;
	for (int i = 0; i < n; ++i)
	{
		cin >> word;
		if(word == "INSERT")
		{
			int x;
			cin >> x;
			insert(Linhash,Quadhash,Doubhash,lincol, quadcol, doubcol, m, x,i1,i2,i3);
		}
		else if(word == "SEARCH")
		{
			int x;
			cin >> x;
			search(Linhash,Quadhash,Doubhash, m, x);
		}
		else if(word == "DELETE")
		{
			int x;
			cin >> x;
			del(Linhash,Quadhash,Doubhash, m, x,i1,i2,i3);
		}
	}

	float f1,f2,f3;
	f1 = (float)lincol/(float)i1;
	f2 = (float)quadcol/(float)i2;
	f3 = (float)doubcol/(float)i3;

	cout << "TOTAL NUMBER OF COLLISIONS IN LINEAR PROBING " << lincol << "\n";
	cout << "TOTAL NUMBER OF COLLISIONS IN QUADRATIC PROBING " << quadcol << "\n";
	cout << "TOTAL NUMBER OF COLLISIONS IN DYNAMIC PROBING " << doubcol << "\n";
	printf("AVERAGE NUMBER OF REHASING REQUIRED IS %.2f IN LINEAR PROBING\n",f1 );
	printf("AVERAGE NUMBER OF REHASING REQUIRED IS %.2f IN QUADRATIC PROBING\n",f2 );
	printf("AVERAGE NUMBER OF REHASING REQUIRED IS %.2f IN DOUBLE HASHING\n",f3 );

}