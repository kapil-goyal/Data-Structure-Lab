#include <bits/stdc++.h>
using namespace std;
/*
	Algo:
	1.) take any surface of cube and store max depth it can achieve.
		This is done by recursively checking its opposite surface on cubes heavier to the surface's cube.
	2.) During application of the above check also store maximum depth any surace can have and its coordinates.
	3.) Now we have max depth surface and its coordinates. Now go to its opposite surface that has max depth one less than of the former.
		repeat the above steps till we reach the surface having max depth 1.(During this repetition printing is done.)
	That's all.   
*/

//print function is used to print position of top surface
void print(int a) {
	switch(a) {
		case 0: cout << "front";break;
		case 1: cout << "back";break;
		case 2: cout << "left";break;
		case 3: cout << "right";break;
		case 4: cout << "top";break;
		case 5: cout << "bottom";break;
	}
	cout <<endl;
}
//DFS visit function
void DFS_visit(int adj_matrix[][6], int max_depth[][6], int color[][6],int i, int j,int N, int& max_i, int& max_j, int& max) {

	int k = j%2 == 1 ? j-1:j+1;
	int para = adj_matrix[i][k];
	for (int m = i+1; m < N; ++m) {
		for (int n = 0; n < 6; ++n) {
			if(adj_matrix[m][n] == para) {
				if(color[m][n] == 0)
					DFS_visit(adj_matrix, max_depth, color, m, n, N, max_i, max_j, max);
				if(max_depth[i][j] < max_depth[m][n] + 1 ) {
					max_depth[i][j] = max_depth[m][n] + 1;
					if(max < max_depth[i][j]) {
						max_i = i;
						max_j = j;
						max = max_depth[i][j];
					}
				}
			}
		}
	}
	color[i][j] = 1;
}
//DFS function
void DFS(int adj_matrix[][6], int max_depth[][6], int color[][6], int& max_i, int& max_j, int N, int& max ) {
	for (int i = 0; i < N; ++i) 
		for (int j = 0; j < 6; ++j)
			if(color[i][j] == 0)
				DFS_visit(adj_matrix, max_depth, color, i, j, N, max_i, max_j, max);
}
int main()
{
	int x=1;	//x keeps track of case no.
	while(1) {
		int N;	
		cin >> N;	//no. of cubes
		if(N <= 0)
			return 0;
		int adj_matrix[500][6];	//adj matrix declaration
		int max_depth[500][6];	//max depth matrix will store maximum depth surface i,j can have
		int color[500][6];		//color matrix is used in DFS visit

		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < 6; ++j) {
				cin >> adj_matrix[i][j];	//initialization of max depth matrix , color matrix , and adj matrix
				max_depth[i][j] = 1;
				color[i][j] = 0;
			}
		}
		int max = max_depth[0][0];	//max will store maximum no. of depth any surface can have i.e. max no. of cubes
		int max_i=0,max_j=0;		// coordinates corresponding to max depth surface

		DFS(adj_matrix, max_depth, color, max_i, max_j,N, max);	//application of DFS storing max_i, max_j, and max
		cout << "Case #" << x << endl << max <<endl;	//printing begins from here.

		cout << max_i+1 << " " ;
		print(max_j);
		max_j = max_j%2 == 1 ? max_j-1 : max_j + 1;
		int para = adj_matrix[max_i][max_j];
		
		for (int i = max_i+1; i < N; ++i) {
			for (int j = 5; j >=0; --j) {
				if(max_depth[i][j] == max-1 && para == adj_matrix[i][j]  ) {
					max_j = j%2 == 1 ? j -1 : j+1;
					cout << i+1 << " " ;
					print(j);
					max -= 1;
					para = j%2 == 1 ? adj_matrix[i][j-1] : adj_matrix[i][j+1];
					break;
				}
			}
		}
		cout << endl;
		x++;
	}
}