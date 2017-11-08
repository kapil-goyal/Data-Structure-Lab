#include <iostream>
using namespace std;

struct node
{
	int key;
	int occurence;
	node* left, *right;
};

node* createnode(int key, int occ)
{
	node* temp = new node;
	temp->key = key;
	temp->occurence = occ;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

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
	cin >> N;
	for (int _ = 0; _ < N; ++_) {
		cin >> d;
		array[d]++;
	}

	node* root = NULL;

	for (int i = 1; i < 1001; ++i)
	{
		if(array[i] != 0) {
			insert(root,i,array[i]);
		}
	}
	print_in(root);
	cout << endl;

}