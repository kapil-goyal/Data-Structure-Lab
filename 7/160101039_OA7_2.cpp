#include <bits/stdc++.h>
using namespace std;

//Struct for fibonacci heap node
struct fh_node
{
	int degree,key;
	fh_node *parent, *child, *left, *right;
	bool mark;
};

//struct for a particular fib heap that stores head and size
struct fib_heap
{
	fh_node* head;
	int size;
};

//this function will create a node of key x. 
fh_node* create_fh_node(int key)
{
	fh_node* temp = new fh_node;
	temp->key = key;
	temp->degree = 0;
	temp->child = temp->parent  = NULL;
	temp->left = temp->right = temp;
	temp-> mark = false;
	return temp;
}

//it will insert a singleton node in another fib heap
void fh_insert(fh_node* &min_head, fh_node* temp, int &N)
{
	N++;

	if(min_head == NULL)
	{
		min_head = temp;
		min_head->left = min_head;
		min_head->right = min_head;
		return;
	}

	temp->right = min_head->right;
	min_head->right->left = temp;
	min_head->right = temp;
	temp->left = min_head;

	if(temp->key < min_head->key)
		min_head = temp;
}

//return no. of root nodes in circular linked list
int no_nodes(fh_node *x)
{
	if(x == NULL)
		return 0;

	fh_node *temp = x;

	int i;
	for (i = 1; temp->right != x; ++i)
		temp = temp->right;

	return i;
}
//makes temp child of parent
void fh_child_link(fh_node* &parent, fh_node* temp)
{
	fh_node* min_head = parent->child;

	if(min_head == NULL)
	{
		temp->parent = parent;
		parent->child = temp;
		parent->degree = no_nodes(temp);
		return;
	}

	temp->right = min_head->right;
	min_head->right->left = temp;
	min_head->right = temp;
	temp->left = min_head;

	temp->parent = min_head->parent;
	parent->degree = no_nodes(min_head);

	if(temp->key < min_head->key)
		parent->child = temp;

}

//make union of two heaps.
fib_heap fh_union(fib_heap head1, fib_heap head2)
{
	fh_node* h1 = head1.head;
	fh_node* h2 = head2.head;

	if(h1 == NULL)
		return head2;

	if(h2 == NULL)
		return head1;

	fh_node *temp1 = h1->right;
	fh_node *temp2 = h2->right;

	h1->right = temp2;
	temp2->left = h1;
	h2->right = temp1;
	temp1->left = h2;

	head1.size += head2.size;
	head2.size = head1.size;

	return h1->key < h2->key ? head1 : head2;
}

//Consolidate function required in fib heap extract min
void Consolidate(fib_heap& heap)
{
	int N = heap.size;
	int D = log2(N) + 1;
	fh_node* a[D];

	for (int i = 0; i < D; ++i)
		a[i] = NULL;

	int count = no_nodes(heap.head);

	fh_node* h = heap.head;

	for (int i = 0; i < count; ++i)
	{
		fh_node* x = h;
		h = h->right;
		int d = x->degree;
		while(a[d] != NULL)
		{
			fh_node* temp =a[d];
			if(x->key > temp->key)
				swap(x,temp);

			if(h == temp)
				h = h->right;

			temp->left->right =temp->right;
			temp->right->left = temp->left;

			temp->right = temp;
			temp->left = temp;

			fh_child_link(x,temp);
			a[d] = NULL;
			d++;
		}
		a[d] = x;
	}

	heap.head = NULL;
	for (int i = 0; i < D; ++i)
	{
		if(a[i] != NULL)
		{
			fh_insert(heap.head, a[i], heap.size);
			heap.size--;
		}
	}
}

//it will print fibonacci heap
void fh_print(fh_node *list , int depth )
{
	if (list != NULL)
	{
		fh_node *ptr = list;

		do
		{
			for(int i =0; i<depth+1;i++)
				cout<<"\t";
			cout<<ptr->key<<"\n";
			if (ptr->child != NULL)
			{
				fh_print(ptr->child , depth+1);
			}
			ptr = ptr->right;
		}while(ptr != list && ptr != NULL);
	}
	else
	{
		cout<<"Empty heap!!"<<endl;
	}
	return ;
}

//return a node which is minimum of fib heap.
fh_node *Extract_min(fib_heap& heap)
{
	fh_node* h = heap.head;
	
	if( h != NULL)
	{
		if(h == h->right)
			heap.head = h->child;
		else
		{
			fib_heap heap2;
			heap2.head = h->child;
			heap2.size = 0;
			
			h->right->left = h->left;
			h->left->right = h->right;
			heap.head = h->right;
			heap = fh_union(heap,heap2);
			Consolidate(heap);
		}
		heap.size--;
		h->left = h->right = h->child = h->parent = NULL;
	}
	return h;
}
int main()
{
	fib_heap heap1;	//declaration of fib heap

	heap1.head = NULL;	//initialization

	int flag = 1;		//print flag
	cout << "type 'quit' to exit the program!! \n";
	string word;		//this take input command and following while loop will operate acc. to the command.
	while((cin >> word))
	{
		if(word == "#")	//if # is i/p command then ignore rest till new line
		{
			cin.ignore(2e9,'\n');
		}
		else if(word == "c")	//if c is i/p command, then previous heap will be deleted new heap will be created
		{
			heap1.head = NULL;
			cout << "New heap created\n";
		}
		else if(word == "S")	//if S is i/p command then heap will be shown
		{
			cout << endl << "Structure of fibonacci heap turned 90 degree ccwise:" << endl;
			fh_print(heap1.head,0);
			cout << endl;
		}
		else if(word == "+")	//flag will be turned on
			flag = 1;
		else if(word == "-")	//flag will be turned off
			flag = 0;
		else if(word == "i")	//insertion in FH will happen
		{
			int d;
			cin >> d;
			fh_node* temp = create_fh_node(d);
			fh_insert(heap1.head, temp, heap1.size);
		}
		else if(word == "e")	//minimum from FH will be extracted
		{
			fh_node* temp = Extract_min(heap1);
			if(temp == NULL)
				cout << "Empty Heap!!\n";
			else
			{
				if(flag)
					cout << "Minimum Extracted: " << temp->key << endl;
			}
		}
		else if(word == "quit")	//quit the program
		{
			break;
		}
		else if(word == "u");
		else					//if command is none of the above, then it is invalid command.
		{
			cout << "Invalid command!!\n";
		}
	}
}	
