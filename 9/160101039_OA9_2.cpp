#include <bits/stdc++.h>
using namespace std;

/*
	Algo: 
	1.) I made an array of size 10000*8 which will store each config in each row and paths possible from that config in each column.
	2.) Now we know the start config and ending config and forbidden states.
	3.) End config color is made 4 (say red) and forbidden configs are colored black.
	4.) Now from start config apply BFS till the end config is reached. If end config is reached BFS will return its distance from start config else -1.
	 That's all.
*/

//This function will take 4 digits of a no. as input return the no.
int gen_num(int a, int b, int c, int d) {
	return a*1000+b*100+c*10+d;
}

//This function will change the digit of a given no. at a given place one forward or backward depending on del.
int make_num(int num, int place, int del) {
	int res = (num/int(pow(10,place)))%10;
	res = (res+del)%10;
	int a = num/1000;
	int b = (num/100)%10;
	int c = (num/10)%10;
	int d = (num)%10;

	switch(place)
	{
		case 0: return a*1000 + b*100 + c*10 + res;
		case 1: return a*1000 + b*100 + res*10 + d;
		case 2: return a*1000 + res*100 + c*10 + d;
		case 3: return res*1000 + b*100 + c*10 + d;
	}
	return 0;
}

//Enqueue function for queue made in BFS
void enqueue(int queue[], int& rear, int x)
{
	queue[rear++] = x;
}

//Dequeue function for queue made in BFS
int dequeue(int queue[], int& front)
{
	front++;
	return queue[front];
}

//BFS function will return distance from start to end state if found otherwise -1
int BFS(int array[][8], int *color, int start) {

	int d[10000];
	for (int i = 0; i < 10000; ++i) {
		d[i] = INT_MAX;
	}

	int queue[10000];
	int rear=0;
	int front=-1;
	d[start] = 0;
	color[start] = 1;
	enqueue(queue, rear, start);

	while(rear-front != 1) {
		int index = dequeue(queue,front);
		for (int i = 0; i < 8; ++i)
		{
			if(color[array[index][i]] == 4) {
				return  d[index] + 1;
			}
			if(color[array[index][i]] == 0) {
				color[array[index][i]] = 1;
				d[array[index][i]] = d[index] + 1;
				enqueue(queue, rear, array[index][i]);
			}
		}
		color[index]=2;
	}
	return -1;
}

int main()
{
	int array[10000][8];	//adjacent matix declaration
	
	for (int i = 0; i < 10000; ++i) {
		for (int j = 0; j < 8; ++j) { 	//adjacent matrix initialization
			array[i][j] = make_num(i,j%4, j < 4 ? 1 : 9);
		}
	}
	
	int t;
	cin >> t;	//no. of test cases

	for (int k = 0; k < t; ++k)
	{
		int color[10000]={0};	//color matrix needed for BFS.
		int a,b,c,d;
		cin >> a >> b >> c >> d;;
		int start = gen_num(a,b,c,d);	//start config
		cin >> a >> b >> c >> d;
		int end = gen_num(a,b,c,d);		//end config
		color[end] = 4;					//color of end config is changed to red.

		int N;							//input no. of forbidden states		
		cin >> N;

		for (int i = 0; i < N; ++i)   
		{
			cin >> a >> b >> c >> d;
			color[gen_num(a,b,c,d)] = 2; //Change color of forbidden states black
		}
		if(start != end)
			cout << BFS(array,color,start) << endl;	//apply BFS if start is not same as end print the outcome of BFS
		else
			cout << "0" << endl;	//print 0 if start and end is same.
	}
}
