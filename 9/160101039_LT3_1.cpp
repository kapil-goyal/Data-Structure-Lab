#include <bits/stdc++.h>
using namespace std;

struct node 
{
	char c;
	node* next;
};

class lst {
private:
	node* head = NULL;
public:
	node* start() {
		return head;
	}
	void insert(char a) {
		if(head == NULL) {
			node *temp = new node;
			temp->c = a;
			temp->next = NULL;
			head = temp;
			return;
		}
		if(head->next == NULL || head->c > a ) {
			node *temp = new node;
			temp->c = a;
			if(head->c < a)
			{
				temp->next = NULL;
				head->next = temp;
			}
			else {
				temp->next = head;
				head = temp;
			}
			return;
		}
		node* temp = head;
		while(temp->next != NULL && temp->next->c < a) {
			temp =temp->next;
		}
		node* temp3 = new node;
		temp3->c = a;
		temp3->next = temp->next;
		temp->next = temp3;
	}
	void print() {
		node* temp = head;
		while(temp != NULL)
		{
			cout << temp->c << " ";
			temp = temp->next;
		}
		cout << endl;
	}
};

struct grp_node
{
	char ind;
	char parent;
	int color;
	int d;
	int f;
	lst adj_list;
};

class stk
{
private:
	node* head = NULL;
public:
	node* top() {
		return head;
	}
	void push(char a) {
		node* temp = new node;
		temp->c = a;
		temp->next = head;
		head = temp;
	};
	char pop() {
		if(head == NULL)
		{
			cout << "Empty stack\n";
			return '\0';
		}
		node *temp = head;
		head = head->next;
		return temp->c;
	}
};

struct egd_lst_node
{
	char a;
	char b;
	char c;
	egd_lst_node* next;
};

class edge_list
{
private:
	egd_lst_node* head = NULL;
public:
	egd_lst_node* start(){
		egd_lst_node* temp2 = head;
		return temp2;
	}
	void insert(char m, char n, char o) {
		egd_lst_node* temp = new egd_lst_node;
		temp->a = m;
		temp->b = n;
		temp->c = o;
		temp->next = NULL;

		if(head == NULL)
			head = temp;
		else {
			egd_lst_node* temp2 = head;
			while(temp2->next != NULL)
				temp2 = temp2->next;
			temp2->next = temp;
		}
	}
	bool found(char a, char b) {
		egd_lst_node* temp2 = head;
		while(temp2 != NULL) {
			if((temp2->a == a && temp2->b == b) && (temp2->c == 'f' || temp2->c == 'b' || temp2->c == 't' || temp2->c == 'c' ))
				return true;
			temp2 = temp2->next;
		}
		return false;
	}
};

class graph
{
private:
	int V;
	grp_node* root_list;
	int time;
public:
	graph(int n)
	{
		V = n;
		root_list = new grp_node[26];
		for (int i = 0; i < 26; ++i)
		{
			root_list[i].ind = '\0';
			root_list[i].parent = '\0';
			root_list[i].color = 0;
			root_list[i].d = 0;
			root_list[i].f = 0;
		}
	};
	void insert(char a, char b) {
		root_list[a-'a'].ind = a;
		root_list[a-'a'].adj_list.insert(b);
	}
	void print() {
		for (int i = 0; i < 26; ++i)
		{
			if(root_list[i].ind != '\0')
			{
				cout << root_list[i].ind << " " << "(" << root_list[i].d << "," << root_list[i].f << ") " ;
				root_list[i].adj_list.print();
			}
		}
	}
	void DFS() {
		time = 0;
		for (int i = 0; i < 26; ++i)
		{
			root_list[i].parent = '\0';
			root_list[i].color = 0;
			root_list[i].d = 0;
			root_list[i].f = 0;
		}
		stk dfs;
		for (int i = 0; i < 26; ++i)
		{
			if(root_list[i].ind != '\0' && root_list[i].color == 0) {
				dfs.push(i+'a');
				root_list[i].color = 1;
				time++;
				root_list[i].d = time;
				while( dfs.top() != NULL) {
					node* temp = dfs.top();
					node* temp2 = root_list[temp->c-'a'].adj_list.start();
					while(temp2 != NULL && root_list[temp2->c-'a'].color != 0)
					{
						temp2 = temp2->next;
					}
					if(temp2 != NULL) {
						dfs.push(temp2->c);
						root_list[temp2->c-'a'].color = 1;
						root_list[temp2->c-'a'].parent = temp->c;
						time++;
						root_list[temp2->c-'a'].d = time;
						cout << "(" << temp->c << ", " << temp2->c << ") ";
					}
					else {
						dfs.pop();
						root_list[temp->c-'a'].color = 2;
						time++;
						root_list[temp->c-'a'].f = time;
					}
				}
			}
		}
		cout << endl;
	}
	void DFS_enh(edge_list& edge) {
		time = 0;
		for (int i = 0; i < 26; ++i)
		{
			root_list[i].parent = '\0';
			root_list[i].color = 0;
			root_list[i].d = INT_MAX;
			root_list[i].f = INT_MAX;
		}
		stk dfs;
		for (int i = 0; i < 26; ++i)
		{
			if(root_list[i].ind != '\0' && root_list[i].color == 0) {
				dfs.push(i+'a');
				root_list[i].color = 1;
				time++;
				root_list[i].d = time;
				while( dfs.top() != NULL) {
					node* temp = dfs.top();
					node* temp2 = root_list[temp->c-'a'].adj_list.start();
					while(temp2 != NULL && root_list[temp2->c-'a'].color != 0)
					{
						temp2 = temp2->next;
					}
					if(temp2 != NULL) {
						dfs.push(temp2->c);
						root_list[temp2->c-'a'].color = 1;
						root_list[temp2->c-'a'].parent = temp->c;
						time++;
						root_list[temp2->c-'a'].d = time;
							edge.insert(temp->c,temp2->c,'t');
					}
					else {
						temp2 = root_list[temp->c-'a'].adj_list.start();
						while(temp2 != NULL) {
							if(root_list[temp2->c-'a'].color == 1) {
									edge.insert(temp->c,temp2->c,'b');
							}
							else {
								if(root_list[temp2->c-'a'].d < root_list[temp->c-'a'].d) {
										edge.insert(temp->c,temp2->c,'c');
								}
								else {
									if(root_list[temp2->c-'a'].parent != temp->c)
										edge.insert(temp->c,temp2->c,'f');
								}
							}
							temp2 = temp2->next;
						}
						dfs.pop();
						root_list[temp->c-'a'].color = 2;
						time++;
						root_list[temp->c-'a'].f = time;
					}
				}
			}
		}
	}
};

int main() 
{
	int N, E;
	cin >> N >> E;
	graph g1(N);
	for (int i = 0; i < E; ++i)
	{
		char a, b;
		cin >> a >> b;
		g1.insert(a,b);
		// g1.print();
	}
	cout << endl;
	// g1.print();
	g1.DFS();
	edge_list edge;
	g1.DFS_enh(edge);
	egd_lst_node* head = edge.start();
	cout << "Tree edges: ";
	while(head != NULL)
	{
		if(head->c == 't')
			cout << "(" << head->a << " " << head->b   <<")";
		head = head->next;
	}
	cout << endl;
	head = edge.start();
	cout << "Forward edges: ";
	while(head != NULL)
	{
		if(head->c == 'f')
			cout << "(" << head->a << " " << head->b   <<")";
		head = head->next;
	}
	cout << endl;
	head = edge.start();
	cout << "Back edges: ";
	while(head != NULL)
	{
		if(head->c == 'b')
			cout << "(" << head->a << " " << head->b   <<")";
		head = head->next;
	}
	cout << endl;
	head = edge.start();
	cout << "Cross edges: ";
	while(head != NULL)
	{
		if(head->c == 'c')
			cout << "(" << head->a << " " << head->b  <<")";
		head = head->next;
	}
	cout << endl;
	// g1.print();
}