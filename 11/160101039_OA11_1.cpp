#include <iostream>
#include <cstdio>
using namespace std;

/*
	caution: Printing of no. of output sequences is done at last. (I have asked instructor about this) Because for large sequences storing may result in overflow

	algo:

	1.) A recursive function is used for printing permutations based on tree structure.
*/


// struct node for a tree node
struct node
{
	int key,color;
	node* left, *right;
};

//createnode function for tree node
node* createnode(int key)
{
	node* temp = new node;
	temp->key = key;
	temp->color = 0;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

//This function will construct BST from a given pre order
node* build_tree(int *pre, int start, int end)
{
	if(start > end)
		return NULL;

	node* root = createnode(pre[start]);

	int i = start;
	while( i <= end && pre[i] <= pre[start])
		i++;

	root->left = build_tree(pre,start+1, i - 1);
	root->right = build_tree(pre,i,end);

	return root;
}

//Printing of inorder just for debugging
void print_in(node* root)
{
	if(root == NULL)
		return ;
	
	print_in(root->left);
	cout << root->key << " ";
	print_in(root->right);
}

// A class and struct for linked list functions
////////////////////////////////////////////////////
struct list_node
{
	node* ptr;
	list_node* next;
};

class my_list
{
private:
	list_node* head = NULL;
	list_node* tail = NULL;

public:
	list_node* start() {
		return head;
	}
	list_node* end() {
		return tail;
	}
	void ins_start(list_node* temp) {
		temp->next = head;
		head = temp;
		if(tail == NULL)
			tail = head;
	}
	void ins_end(list_node* temp) {
		temp->next = NULL;
		if(tail == NULL) {
			head = tail = temp;
			return;
		}
		tail->next = temp;
		tail = temp;
	}
	void del_start() {
		list_node* temp = head;
		list_node* temp2 = tail;
		if(head == NULL || head->next == NULL) {
			head = NULL;
			tail = NULL;
			delete temp;
			return;
		}
		else {
			head = head->next;
		}
		delete temp;
	}
	void del_end() {
		list_node* temp = tail;
		list_node* temp2 = head;
		if(head == NULL || head->next == NULL) {
			head = NULL;
			tail = NULL;
			delete temp;
			return;
		}
		while(temp2->next != tail) {
			temp2 = temp2->next;
		}
		delete temp;
		temp2->next = NULL;
		tail = temp2;
	}
};
void print(my_list lis) {
	list_node* temp = lis.start();
	while(temp != NULL) {
		printf("%d ",temp->ptr->key);
		temp = temp->next;
	}
	printf("\n");
}

list_node *createlistnode(node* point) {
	list_node* temp = new list_node;
	temp->ptr = point;
	temp->next = NULL; 
	return temp;
}
////////////////////////////////////////////////////


//A utility function which is used in printing of permutations
void givelist(node* root, my_list& treelist)
{
	if(root == NULL ) {
		return;
	}
	if(root->color == 0) {
		treelist.ins_end(createlistnode(root));
		return;
	}
	else {
		givelist(root->left,treelist);
		givelist(root->right,treelist);
	}
}

//A recursive function which will print permutations
void print_permu(node* x, node* root, my_list list_x, int& count)
{
	if(x==NULL)
		return;

	givelist(x,list_x);
	x->color = 1;

	my_list list3;
	givelist(root,list3);
	list_node* temp = list3.start();
	if(temp == NULL) {
		print(list_x);
		count++;
	}
	while(temp != NULL) {
		print_permu(temp->ptr,root,list_x, count);
		temp = temp->next;
	}
	x->color = 0;
	list_x.del_end();
}


int main()
{
	int N,d;
	cout << "Input: \n";
	cin >> N;						//Input taken
	int *preorder = new int [N];
	for (int i = 0; i < N; ++i)
	{
		cin >> d;
		preorder[i] = d;
	}

	node *root = NULL;
	root = build_tree(preorder,	0,N-1);	//making of tree
	
	int count=0;
	my_list list_x;

	cout << "Output:"  << endl;
	print_permu(root,root,list_x,count);	//printing of permutations will occur
	cout << "No. of Possible Sequences: "  << count << endl;	//printing of no. of output sequences
}