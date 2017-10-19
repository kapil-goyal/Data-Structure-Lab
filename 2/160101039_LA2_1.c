#include <stdio.h>
#include <stdlib.h>
typedef struct tree
{
	int data;
	struct tree *left;
	struct tree *right;
}node;

node *makenode(int d)
{
	node *temp = (node *)malloc(sizeof(node));
	temp->data = d;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}


node *search(node *root, int a)
{
	if(root == NULL)
		return NULL;
	if(root->data == a)
		return root;

	node *temp = search(root->left,a);
	if(temp != NULL)
			return temp;

	temp = search(root->right, a);
	if(temp != NULL)
			return temp;
}


void insert(node *root, int a, char c, int b)
{
	node *temp = search(root, b);

	if(temp == NULL)
	{
		printf("Number not found\n");
		return;
	}

	if(c == 'L')
	{
		if(temp->left == NULL)
			temp->left = makenode(a);
		else
		{
			printf("Number %d is ignored\n",a );
			return;
		}
	}

	if(c == 'R')
	{
		if(temp->right == NULL)
			temp->right = makenode(a);
		else
		{
			printf("Number %d is ignored\n",a );
			return;
		}
	}

}

void printin(node *root)
{
	if(root == NULL)
		return;
	printin(root->left);
	printf("%d ",root->data);
	printin(root->right);
}

void printpre(node *root)
{
	if(root == NULL)
		return;
	printf("%d ",root->data);
	printpre(root->left);	
	printpre(root->right);
}

void printpost(node *root)
{
	if(root == NULL)
		return;
	printpost(root->left);
	printpost(root->right);
	printf("%d ",root->data);
}
void printleaf(node *root)
{
	if(root == NULL)
		return;
	if(root->left == NULL && root->right == NULL)
		printf("%d ",root->data );
	printleaf(root->left);
	printleaf(root->right);
}
int main()
{
	node *root = NULL;
	
	int a,b;
	char c;
		scanf("%d",&a);

		if(a != -1)
		{
			
			scanf(" %c",&c);
			scanf("%d",&b);

			root = makenode(a);
		}

	while( a != -1)
	{
		scanf("%d",&a);
		if(a == -1)
			break;
		scanf(" %c",&c);
		scanf("%d",&b);

		insert(root, a, c, b);

	}

	printf("Inorder: ");
	printin(root);
	printf("\n");
	printf("Preorder: ");
	printpre(root);
	printf("\n");
	printf("Postorder: ");
	printpost(root);
	printf("\n");
	printf("Leaf Nodes: ");
	printleaf(root);
	printf("\n");

}