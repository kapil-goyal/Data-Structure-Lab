#include <bits/stdc++.h>
using namespace std;

/*
	caution: Graph is assumed to be simple.

	Algorithm:
	1. for finding no. of components, an int type "component" element is stored in graph node which stores the component no. it belongs to.
	   no. of components is same as no. of times DFS_visit is called by DFS.
	2. for finding cycles:
		i) during DFS_visit if colour of adj node is found black, then that adj node and node itself is a cyclic pair.
			(cyclic pair : start and end of a cycle.) From this we can find no. of cycles and cyclic pair.
		ii) Now each cyclic pair path is printed which prints the cyclic path.
	That's all.
*/

//This struct and class will store and maintain adjacency list.(Basically list of one int)
struct adj_list_node {
	int data;
	adj_list_node* next;
};

class adj_list {

private:
	adj_list_node* head = NULL;
	adj_list_node* tail = NULL;

public:
	adj_list_node* start() {
		return head;
	}
	void insert(int x) {
		adj_list_node* temp = new adj_list_node;
		temp->data = x;
		temp->next = NULL;
		if(head == NULL) {
			head = temp;
			tail = temp;
		}
		else {
			tail->next = temp;
			tail = temp;
		}
		return;
	}
};

//This struct and class will maintain list of cyclic elements pair. (Basically list of two ints)
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
		cyclic_pair* temp = new cyclic_pair;
		temp->a = a;
		temp->b = b;
		temp->next = head;
		head = temp;
		return;
	}	
};

//Struct for graph node
struct node {
	int index;	//Index will store node number.
	int colour;	//colour is used to track nodes. 0 means white, 1 means grey, 2 means black
	int component;	//this will store info about which node belongs to which component.
	int dfs_parent;	//parent acc. to DFS traversal
	adj_list list;	//adjacency list
};

//function to create a graph node
node *createnode(int d) {	
	node* temp = new node;
	temp->index = d;
	temp->colour = 0;
	temp->component = 0;
	temp->dfs_parent = 0;
	return temp;
}

//DFS visit function will is same as typical DFS_visit.It also stores cyclic pairs and no. of cycles
void DFS_visit(node* root_list[],cyclic& cyc_pair, node* root, int &cycles) {

	root->colour = 1;
	adj_list_node* temp = root->list.start();
	while(temp != NULL) {
		if(root_list[temp->data]->colour == 0) {
			root_list[temp->data]->component = root->component;
			root_list[temp->data]->dfs_parent = root->index;
			DFS_visit(root_list,cyc_pair,root_list[temp->data], cycles);
		}
		else if(temp->data != root->dfs_parent && root_list[temp->data]->colour == 1 ) {
			cycles++;
			cyc_pair.insert(root->index,temp->data);
		}
		temp = temp->next;	
	}
	root->colour = 2;
}

//DFS is used for DFS traversal . It will return no. of components present in nodes.
int DFS(node* root_list[],cyclic& cyc_pair, int N, int &cycles) {
	for (int i = 1; i <= N; ++i) {
		root_list[i]->colour = 0;
		root_list[i]->dfs_parent = 0;
	}
	int component=0;
	for (int i = 1; i <= N; ++i) {
		if(root_list[i]->colour == 0) {
			component++;
			root_list[i]->component = component;
			DFS_visit(root_list,cyc_pair,root_list[i],cycles);			
		}
	}
	return component;
}

//print path will print path between two nodes using DFS traversal
void print_path(node* root_list[], int a, int b)
{
	if(a == b)
		cout << a << " ";
	else {
		print_path(root_list,a,root_list[b]->dfs_parent);
		cout << b << " ";
	}
}

int main() {

	int N, E, components=0, cycles=0;	//N is no. of nodes; E = no. of edges; components = no. of components; cycles = no. of cycles;
	cyclic cyc_pair;					//list for cyclic pairs
	cout << "Input no. of nodes: ";
	cin >> N;							//input for N and E
	cout << "Input no. of edges: ";
	cin >> E;	

	cout << "Now for " << E <<" lines input numbers in the form 'a b', e.g. 5 3\n";

	node *root_list[N+1] = {NULL};		//Root list of graph nodes

	for (int i = 1; i < N+1; ++i) {		//Initialisation of root list
		root_list[i] = createnode(i);
	}

	for (int i = 0; i < E; ++i) {		//Input for root list
		int a,b;
		cin >> a >> b;
		if(a == b) {
			cycles++;
			cyc_pair.insert(a,a);
		}
		else {
			root_list[a]->list.insert(b);
			root_list[b]->list.insert(a); 
		}
	}

	components = DFS(root_list, cyc_pair, N, cycles);	//application of DFS and no. of components are found.
	cout << "\nNo. of connected components: " << components << endl << endl;

	adj_list comp[components+1];	//this list will store element which belongs to ith component in comp[i] linked list
	for (int i = 1; i <= N; ++i) {
		comp[root_list[i]->component].insert(i);
	}

	for (int i = 1; i <= components; ++i) {		//printing of components of various linked list

		cout << "Connected Components " << i << ": ";
		adj_list_node *temp = comp[i].start();
		while(temp != NULL) {
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl;
	}

	cout << "\nNo. of cycles: " << cycles << endl << endl;	//printing of no. of cycles
	cyclic_pair* head = cyc_pair.start();					//head is head of cyclic pair linked list

	for(int i = 1; i <= cycles; i++) {						//Printing of cyclic pair paths
		cout << "Cycle " << i << ": ";	
		print_path(root_list,head->b,head->a);
		cout << head->b << " ";
		cout << endl;
		head = head->next;
	}
	cout << endl;
	return 0;			//The End
}