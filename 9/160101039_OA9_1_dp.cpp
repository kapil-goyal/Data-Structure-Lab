#include <bits/stdc++.h>
using namespace std;
struct node
{
	int a;
	int b;
	node* next;
};

class my_list
{
private:
	node* head = NULL;

public:
	node* start() {
		return head;
	}
	void ins_start(node* temp) {
		temp->next = head;
		head = temp;
	}
	void print() {
		node* temp = head;
		cout << endl;
		while(temp != NULL) {
			cout << temp->a+1 << " ";
			switch(temp->b) {
				case 0: cout << "front";break;
				case 1: cout << "back";break;
				case 2: cout << "left";break;
				case 3: cout << "right";break;
				case 4: cout << "top";break;
				case 5: cout << "bottom";break;
			}
			cout <<endl;
			temp = temp->next;
		}
	}
};
node *createnode(int a,int b) {
	node* temp = new node;
	temp->a = a;
	temp->b = b;
	temp->next = NULL;
	return temp;
}
int main()
{
	int x=1;
	while(1) {
		int N;
		cin >> N;
		if(N <= 0)
			return 0;
		int array[N][6];
		int Lis[N][6];

		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < 6; ++j) {
				cin >> array[i][j];
				Lis[i][j] = 1;
			}
		}
		int max = Lis[0][0];
		int s=0,q=0;

		for (int i = 1; i < N; ++i){
			for(int l = 0; l<6; l++) {
				int n = l%2 == 1 ? l-1 : l+1;
				 for (int j = i-1; j >= 0; --j) {
					for (int k=0; k < 6; k++) {
						if(array[j][k] == array[i][l]) {
							if(Lis[i][n] <= Lis[j][k]) {
								Lis[i][n] = Lis[j][k]+1;
								if(max < Lis[i][n]) {
									s = i;
									q = n;
									max = Lis[i][n];
								}
							}
						}
					}
				}
			}
		}
		cout << "Case #" << x << endl << max;

		my_list stk;
		q = q%2 == 1 ? q-1 : q + 1;
		int para = array[s][q];
		stk.ins_start(createnode(s,q));
		
		for (int i = s-1; i >= 0; --i)
		{
			for (int j = 0; j < 6; ++j)
			{
				if(Lis[i][j] == max-1 && para == array[i][j]  ) {
					q = j%2 == 1 ? j -1 : j+1;
					if(Lis[i][j] >= Lis[i][q]) {
					stk.ins_start(createnode(i,q));
					max -= 1;
					para = j%2 == 1 ? array[i][j-1] : array[i][j+1];
					break;
					}
				}
			}
		}
		stk.print();
		cout << endl;
		x++;
	}
}