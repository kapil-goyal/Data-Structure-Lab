#include <bits/stdc++.h>
using namespace std;

struct node 
{
	int data;
	node *left;
	node *right;
	bool rthread;
};

void setleft(node *parent, int d)
{
	if(parent == NULL)
		return;
	if(parent->left != NULL)
	{
		printf("\n%d is ignored.\n",d );
		return;
	}
	else
	{
		node *temp = new node;
		temp->data = d;
		temp->left = NULL;
		temp->right = parent;
		temp->rthread = true;
		parent->left = temp;
		return;
	}
}
void setright(node *parent, int d)
{
	if(parent == NULL)
		return;
	if(parent->rthread == false)
	{
		printf("\n%d is ignored.\n",d );
		return;
	}
	else
	{
		node *temp = new node;
		temp->data = d;
		temp->left = NULL;
		temp->right = parent->right;
		temp->rthread = true;
		parent->rthread = false;
		parent->right = temp;
		return;
	}
}
node *search(node *root, int d)
{
	if(root == NULL)
		return NULL;
	if(root->data == d)
		return root;
		node *temp1 = NULL;
		node *temp2 = NULL;

	if(root->left != NULL)	
		temp1 = search(root->left,d);
	if(root->rthread == false )
		temp2 = search(root->right,d);

	if(temp1 != NULL)
		return temp1;
	else
		return temp2;


}
void intrav(node *parent)
{
	node *q = NULL;
	printf("Inorder: ");
	while(1)
	{
		
		while(parent != NULL)
		{
			q = parent;
			parent = parent->left;
		}
		if(q != NULL)
		{
			printf("%d ",q->data );
			parent = q;
			parent = parent->right;
		}
		while(q->rthread & parent != NULL)
		{
			printf("%d ",parent->data );
			q = parent;
			parent = parent->right;
		}
		q = parent;
		if(q == NULL)
		{
			printf("\n");
			break;
		}
	}
}
int main()
{
	int num1, num2;
	char c;
	node *root = new node;
	scanf("%d",&num1);

	if(num1 != -1)
	{
		scanf(" %c %d",&c,&num2);
			root->data = num1;
			root->left = NULL;
			root->right = NULL;
			root->rthread = true;
	}

	while(1)
	{
		scanf("%d",&num1);
		if(num1 == -1)
			break;
		scanf(" %c %d",&c,&num2);
		node *temp = search(root,num2);
		if(temp == NULL)
		{
			printf("num2 not found\n");
			continue;
		}
		if(c == 'L')
			setleft(temp,num1);
		if(c == 'R')
			setright(temp,num1);
	}
	intrav(root);
	
}