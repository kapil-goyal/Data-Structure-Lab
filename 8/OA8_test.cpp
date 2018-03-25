#include <bits/stdc++.h>
using namespace std;

struct adj_list_node {
	int data;
	adj_list_node* next;
};

class adj_list {

private:
	adj_list_node* head = NULL;

public:

	adj_list_node* start() {
		return head;
	}

	void insert(int x) {
		if(head == NULL) {
			adj_list_node* temp = new adj_list_node;
			temp->data = x;
			temp->next = NULL;
			head = temp;
			return;
		}
		adj_list_node* temp = head;
		while( temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = new adj_list_node;
		temp->next->data = x;
		temp->next->next = NULL;
		return;
	}

	void print() {
		adj_list_node* temp = head;
		while(temp != NULL) {
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl;
	}
};

struct cyclic_pair {
	int a,b;
	cyclic_pair* next;
};

class cyclic {

private:
	cyclic_pair* head = NULL;

public:
	cyclic_pair* start() {
		return head;
	}
	void insert(int a, int b) {

		if(head == NULL) {
			head = new cyclic_pair;
			head->a = a;
			head->b = b;
			head->next = NULL;
			return;
		}
		cyclic_pair* temp = head;
		while(temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = new cyclic_pair;
		temp->next->a = a;
		temp->next->b = b;
		temp->next->next = NULL;
		return;
	}	
};

struct node {
	int index;
	int colour;
	int component;
	int dfs_parent;
	int bfs_parent;
	adj_list list;
};

node *createnode(int d) {
	node* temp = new node;
	temp->index = d;
	temp->colour = 0;
	temp->component = 0;
	temp->dfs_parent = 0;
	temp->bfs_parent = 0;
	return temp;
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

void BFS(node *list[], int size, int i,int k)
{
	for (int j = 1; j <= size; ++j)	{
		list[j]->bfs_parent = 0;
		list[j]->colour = 0;
	}		

	list[i]->colour = 1;
	//list[k]->colour = 1;

	int queue[size];
	int front = -1, rear = 0;
	enqueue(queue,rear, i);

	while(rear- front != 1)
	{
		int index = dequeue(queue,front);
		adj_list_node *temp = list[index]->list.start();
		while(temp != NULL)
		{
			if(list[temp->data]->colour == 0 && (index != i || temp->data != k))
			{
				list[temp->data]->colour = 1;				
				enqueue(queue, rear, temp->data);
				list[temp->data]->bfs_parent = index;
			}			
			temp = temp->next;
		}
		list[index]->colour = 2;
	}
	return;
}
void DFS_visit(node* root_list[],cyclic& cyc_pair, node* root) {

	root->colour = 1;
	adj_list_node* temp = root->list.start();
	while(temp != NULL) {
		if(root_list[temp->data]->colour == 0) {
			root_list[temp->data]->component = root->component;
			root_list[temp->data]->dfs_parent = root->index;
			DFS_visit(root_list,cyc_pair,root_list[temp->data]);
		}
		else if(root_list[temp->data]->colour == 2) {
			cyc_pair.insert(root->index,temp->data);
		}
		temp = temp->next;	
	}
	root->colour = 2;
}

int DFS(node* root_list[],cyclic& cyc_pair, int N) {
	for (int i = 1; i <= N; ++i) {
		root_list[i]->colour = 0;
		root_list[i]->dfs_parent = 0;
	}
	int component=0;
	for (int i = 1; i <= N; ++i) {
		if(root_list[i]->colour == 0) {
			component++;
			root_list[i]->component = component;
			DFS_visit(root_list,cyc_pair,root_list[i]);			
		}
	}
	return component;
}
void print_path_bfs(node* root_list[], int a, int b)
{
	if(a == b)
		cout << a << " ";
	else {
		print_path_bfs(root_list,a,root_list[b]->bfs_parent);
		cout << b << " ";
	}
}
void print_path(node* root_list[], int a, int b)
{
	if(a == b)
		cout << a << " ";
	else {
		print_path_bfs(root_list,a,root_list[b]->dfs_parent);
		cout << b << " ";
	}
}

int main() {

	int N, E;
	cin >> N >> E;

	node *root_list[N+1] = {NULL};

	for (int i = 1; i < N+1; ++i) {
		root_list[i] = createnode(i);
	}

	for (int i = 0; i < E; ++i) {
		int a,b;
		cin >> a >> b;
		root_list[a]->list.insert(b);
		root_list[b]->list.insert(a); 
	}

	cyclic cyc_pair;

	cout << endl;

	for (int i = 1; i <= N; ++i) {
		if(root_list[i] != NULL) {
			cout << root_list[i]->index << " ";
			root_list[i]->list.print();
		}
	}
	cout << endl;

	// BFS(root_list,N);

	cout << "No. of connected components: " << DFS(root_list, cyc_pair, N) << endl << endl;

	for (int i = 1; i <= N; ++i) {
			cout << root_list[i]->index << " " << root_list[i]->component << " "<< root_list[i]->colour << " "<< root_list[i]->dfs_parent << " ";
			cout << endl;
	}

	cout << endl;

	cyclic_pair* head = cyc_pair.start();
	while(head != NULL) {
		BFS(root_list,N,head->a,head->b);
		print_path_bfs(root_list,head->a,head->b);
		cout << head->a << " ";
		cout << endl;
		head = head->next;
	}	
}