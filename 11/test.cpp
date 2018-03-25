#include <iostream>
#include <cstdio>
using namespace std;

struct node
{
	int key,color;
	node* left, *right;
};

node* createnode(int key)
{
	node* temp = new node;
	temp->key = key;
	temp->color = 0;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

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

void print_in(node* root)
{
	if(root == NULL)
		return ;
	
	print_in(root->left);
	cout << root->key << " ";
	print_in(root->right);
}
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
void print(my_list lis, string & res) {
	list_node* temp = lis.start();
	char arry[100] = "";
	while(temp != NULL) {
		printf("%d ",temp->ptr->key);
		res += arry;
		temp = temp->next;
	}
	printf("\n");
	res += arry;
}

list_node *createlistnode(node* point) {
	list_node* temp = new list_node;
	temp->ptr = point;
	temp->next = NULL; 
	return temp;
}

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
void print_permu(node* x, node* root, my_list list_x, int& count,string& result)
{
	givelist(x,list_x);
	x->color = 1;

	my_list list3;
	givelist(root,list3);
	list_node* temp = list3.start();
	if(temp == NULL) {
		print(list_x,result);
		count++;
	}
	while(temp != NULL) {
		print_permu(temp->ptr,root,list_x, count, result);
		temp = temp->next;
	}
	x->color = 0;
	list_x.del_end();
}

int main()
{
	int N,d;
	cin >> N;

	int *preorder = new int [N];

	for (int i = 0; i < N; ++i)
	{
		cin >> d;
		preorder[i] = d;
	}

	node *root = NULL;
	root = build_tree(preorder,	0,N-1);

	print_in(root);
	cout << endl << endl;
	int count=0;
	my_list list_x;
	string res = "";
	print_permu(root,root,list_x,count,res);
	cout << count << endl;
	cout << res;
}