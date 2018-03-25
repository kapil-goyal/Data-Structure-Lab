#include <iostream>
using namespace std;

/*
	Algo:
	1.) BST is formed acc. to frequency first and then acc to key value if no. of occurence match
	2.) then call print inorder like function for printing

	That's all.
*/

//Struct for tree node
struct node
{
	int key;
	int occurence;
	node* left, *right;
};

//Createnode function for tree node
node* createnode(int key, int occ)
{
	node* temp = new node;
	temp->key = key;
	temp->occurence = occ;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

//Insertion in Binary tree acc to occurence and then key value for tie breaking
void insert(node*& root, int key, int occ)
{
	if( root == NULL) {
		root = createnode(key,occ);
		return;
	}
	if(occ > root->occurence){
		insert(root->left,key,occ);
	}
	else if( occ < root->occurence) {
		insert(root->right,key,occ);
	}
	else {
		if(key < root->key)
			insert(root->left,key,occ);
		else
			insert(root->right,key,occ);
	}
}

//Printing function that works like pre order 
void print_in(node* root)
{
	if(root == NULL)
		return;

	print_in(root->left);
	for (int i = 0; i < root->occurence; ++i)
	{
		cout << root->key << " ";
	}
	print_in(root->right);
}

int main()
{
	int array[1001] = {0};
	int N,d;
	cout << "Input: \n";			//Input taken
	cin >> N;
	for (int _ = 0; _ < N; ++_) {
		cin >> d;
		array[d]++;
	}

	node* root = NULL;

	for (int i = 1; i < 1001; ++i)	//Insertion in Binary tree
	{
		if(array[i] != 0) {
			insert(root,i,array[i]);
		}
	}
	cout << "Output:" << endl;		//printing of output
	print_in(root);
	cout << endl;

}