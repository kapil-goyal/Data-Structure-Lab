#include <bits/stdc++.h>
using namespace std;

struct node
{
	int index;
	int color;
	int rival;
	node* next;
};

node *createnode(int x)
{
	node *temp = new node;
	temp->index = x;
	temp->color = 0;
	temp->rival = 0;
	temp->next = NULL;
	return temp;
}

void insert_end(node* list[],int i , int x)
{
	if(list[i] == NULL)
	{
		list[i] = createnode(x);
		return;
	}

	node *temp = list[i];
	while(temp->next != NULL)
		temp = temp->next;

	temp->next = createnode(x);
	return;

}

void enqueue(int queue[], int& rear, int x)
{
	queue[rear++] = x;
}

int dequeue(int queue[], int& front)
{
	front++;
	return queue[front];
}

int BFS(node *list[], int size)
{
	int i;
	for (i = 1; i <= size; ++i)
		if(list[i] != NULL)
			break;

	list[i]->rival = 1;
	list[i]->color = 1;

	int queue[100];
	int front = -1, rear = 0;
	enqueue(queue,rear, i);

	while(rear- front != 1)
	{
		int index = dequeue(queue,front);
		node *temp = list[index]->next;
		while(temp != NULL)
		{
			if(list[temp->index]->color == 0)
			{
				list[temp->index]->color = 1;				
				enqueue(queue, rear, temp->index);
			}
			if(list[temp->index]->rival == 0)
			{
				temp->rival = list[index]->rival < 2 ? 2 : 1;
				list[temp->index]->rival = temp->rival;
			}
			else
			{
				if(list[temp->index]->rival == list[index]->rival )
					return -1;
			}
			temp = temp->next;
		}
		list[index]->color = 2;
	}
	return 0;
}

int main()
{
	int N, r;
	int a,b;

	cin >> N >> r;

	node* list[N+1] = {NULL};

	for (int i = 0; i < r; ++i)
	{
		cin >> a >> b;
		if(list[a] == NULL)
			insert_end(list,a,a);
		if(list[b] == NULL)
			insert_end(list,b,b);
		insert_end(list,a,b);
		insert_end(list,b,a);
	}

	int chk = BFS(list, N);

	if(chk == 0)
	{
		cout << "Good Guys : ";
	
		for (int i = 1; i <= N; ++i)
		{
			if(list[i] != NULL && list[i]->rival == 1)
				cout << list[i]->index << " ";
		}
		cout << endl;
	
		cout << "Bad Guys : ";
	
		for (int i = 1; i <= N; ++i)
		{
			if(list[i] != NULL && list[i]->rival == 2)
				cout << list[i]->index << " ";
		}
		cout << endl;
	}
	else
	{
		cout << "Not Possible!!\n";
	}

}