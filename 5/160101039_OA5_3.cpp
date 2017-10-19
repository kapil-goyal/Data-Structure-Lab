#include <bits/stdc++.h>
using namespace std;

/*
Approach:
N is the no. of towns.
array[N+1][7] is a 2-d array where array[i][j] will store the no. of j seated cars in town i.
	e.g. if input is 4 3 then array[4][3] = 3
					 4 3
					 4 3
	array[i][0] will store the no. of passengers in town i.
cars[N+1] will store the no. of cars travelling from each town.

Now simply for each town(except the destination town), minimum no. of cars are counted and stored in array cars[].
*/

int main()
{
	//N is the no. of towns
	//T is the destination town.
	//E is the no. of employees.
	int N, T, E; 

	cout << "Input:\n";
	cin >> N ;
	if(N == 0)
	{
		cout << "\nError: No town\n";
		return 0;
	}
	cin >> T ;
	if(T > N)
	{
		cout << "\nError: T should lie between N\n";
		return 0;
	}
	cin >> E ;


	int array[N+1][7];	//Declation of array.
	int cars[N+1] = {0};	//Declaration and initialisation of cars[] with 0.

	for (int i = 0; i < N+1; ++i)	//Initialisation of all array[][] elements with 0 .
		for (int j = 0; j < 7; ++j)
			array[i][j] = 0;

	int e , p; //e will store town no. for each employee and p is the no. of passengers he can accomodate in his car.

	//Employee information is taken.
	for (int i = 0; i < E; ++i)	//Loop will run E (no. of employees) times.
	{
		cin >> e >> p;	

		if(e == T)	// Obviously if person belongs to the destination town, then he does not need to travel.
			continue;

		array[e][p]++;	//there is a passenger having p seated car in town e.

		if(p != 0)		
			array[e][0]++;	//counting of passengers.
	}

	//Now checking for each town is going to be done.
	for (int i = 1; i < N+1; ++i)
	{
		if(array[i][0] == 0)	//if there is no passengers in town i, then continue.
			continue;

		//if there are passengers in town i.
		for (int j = 6; j > 0; --j)	//For minimizing no. of cars we will go from maximum seated car to minimum.(i.e. 6 to 1) 
		{
			array[i][0] -= j*array[i][j]; //new frequency of passengers = prev freq - (no. of j seated cars)*(j)
			cars[i] += array[i][j];			//cars from town = cars from town + no. of j seated cars.

			if(array[i][0] <= 0)	//if frequency of passengers is 0 or less(i.e. some seats are empty) , then break.
				break;
		}

		//if frequency of passengers in town i is positive even after car accomodation,
		// then function will return printing impossible.
		if(array[i][0] > 0)		
		{
			cout << "\nOutput:\nIMPOSSIBLE!\n";
			return 0;
		}
	}

	//Finally output is printed.
	cout << "\nOutput: \n";
	for (int i = 1; i < N+1; ++i)
	{
		cout << cars[i] << " ";
	}
	cout << endl;

	return 1;
}