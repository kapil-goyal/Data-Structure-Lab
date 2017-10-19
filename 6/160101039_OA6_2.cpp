#include <bits/stdc++.h>
using namespace std;
/*
	Algorithm:
	1. Sort persons acc. to their arrival time.
	2. Set current time to the arrival time of first person.
	3. Make a Minheap using key as cooktime of persons with arrival time <= current time.
	4. Extract minimum from minheap. i. e. person with minimum cook time.
	5. Increase current time with cook time of incoming person.
	6. Insert new customers acc. to above procedure again and repeat till all customers are done.

	P.S. Average time is calculated after every minimum extraction.
*/

//Struct for cutomers
struct person
{
	long ArrTime;
	long CookTime;
};

//Radix sort is used to sort acc. to arrival time
void radixsort(person *array, long N)
{
	static long j = 1;

	long c[10] = {0};

	for (long i = 0; i < N; ++i)
		c[(array[i].ArrTime/long (pow(10,j-1)))%10]++;

	bool chksort = true;

	for (long i = 1; i < 10; ++i)
		if(c[i] != 0)
			chksort = false;

	if(chksort == true)
		return;

	person b[N];

	for (long i = 1; i < 10; ++i)
		c[i] = c[i] + c[i-1];

	for (long i = N-1; i >= 0; --i)
	{
		b[c[(array[i].ArrTime/long (pow(10,j-1)))%10]-1] = array[i];
		c[(array[i].ArrTime/long (pow(10,j-1)))%10]--;
	}

	for (long i = 0; i < N; ++i)
	{
		array[i] = b[i];
	}
	j++;
	radixsort(array,N);
}

//Minheapify function
void Minheapify(person array[], long root, long& heapsize)
{
	long L = 2*root + 1;
	long R = 2*root + 2;

	if(L > heapsize)
		return;
	long k = array[L].CookTime < array[root].CookTime ? L : root;
	if(R <= heapsize)
		k = array[k].CookTime < array[R].CookTime ? k : R;
	if(k != root)
	{
		swap(array[k], array[root]);
		Minheapify(array,k,heapsize);
	}
}

//This function will build minheap
void BuildMinHeap(person array[], long& heapsize)
{
	for (long i = heapsize/2; i >= 0; --i)
	{
		Minheapify(array,i,heapsize);
	}
}

//Extract min function will return person with minimum cookTime
person extractMin(person array[], long& heapsize)
{
	person min = array[0];
	swap(array[0], array[heapsize]);
	heapsize--;
	Minheapify(array,0,heapsize);
	return min;
}

//it will insert a person in Minheap.
void insertMinHeap(person array[], long& heapsize, person x)
{
	long j = heapsize+1;
	array[j] = x;
	long parent = (j-1)/2;
	while(parent >= 0 && array[j].CookTime < array[parent].CookTime)
	{
		swap(array[j],array[parent]);
		j = (j-1)/2;
		parent = (j-1)/2;
	}
	heapsize++;
}
int main()
{	
	// N is the no. of cutomers. all other variables' names are self explanatory 
	long N, CurrTime=0, heapsize = -1, AvgWaitime = 0;

	cin >> N;

	person array[N];

	for (long i = 0; i < N; ++i)
	{
		cin >> array[i].ArrTime >> array[i].CookTime; //Input Taken
	}

	radixsort(array, N); // Sorting acc. to arrival time

	CurrTime = array[0].ArrTime; // Setting of current time

	long i;

	for (i = 0; i < N && CurrTime >= array[i].ArrTime ; ++i)
	{
		heapsize++;
	}

	BuildMinHeap(array, heapsize); //formation of heap acc to persons' arrival time

	while(1) // This while loop will run until all the customers are checked and their orders are done.
	{
		if(heapsize == -1 && i == N)
			break;

		while(heapsize+1)	//while heap is not empty
		{
			person k = extractMin(array, heapsize);	//extract minimum cooktime person
			CurrTime += k.CookTime;					//increase current time with cooktime of min person
			AvgWaitime += CurrTime - k.ArrTime;		//increase avg time varible accordingly

			while(i < N && CurrTime >= array[i].ArrTime )	//insert new customers in heap acc. to their arrival time
			{
				insertMinHeap(array, heapsize, array[i]);
				i++;
			}
		}

		if(i < N)			//if heap becomes empty but all customers are not done . i.e. cook remains free for some time.
		{
			CurrTime = array[i].ArrTime;	//set current time equal to the next customers time
			while(i < N && CurrTime >= array[i].ArrTime )	//insert new customers again
			{
				insertMinHeap(array, heapsize, array[i]);
				i++;
			}
		}
	}

	cout << AvgWaitime/N << endl; //Finally printing average value of wait time.
}