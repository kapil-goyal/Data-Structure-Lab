//Input string limit is 199

#include <bits/stdc++.h>
using namespace std;
struct node        										 //Struct for node of a tree
{
	char c;
	int fre;
	node *left;
	node *right;
};
struct Queue       										//Struct for nodes of priority queue
{
	node *element;
	Queue *next;
};

node *createElement(char c, int f) 						//This function returns a treenode
{
	node *temp = new node;
	temp->c = c;
	temp->fre = f;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}
Queue *prevq(Queue *start, Queue* p) 					//returns previous node of the queue for a given node
{
	if(start == NULL)
		return NULL;
	Queue *temp = start;
	while(1)
	{
		if(temp->next == NULL)
			return NULL;
		if(temp->next == p)
			return temp;
		temp = temp->next;
	}
}
void insertPQ(Queue* &start, node* ele) 				//Inserts a tree node element amd make a new node in the queue
{
	if(start == NULL)
	{
		start = new Queue;
		start->element = ele;
		start->next = NULL;
		return;
	}
	Queue *temp = start;
	while(temp != NULL)
	{		
		if(ele->fre == temp->element->fre)
		{
			if(ele->c < temp->element->c)
			{
				Queue* temp2 = new Queue;
				temp2->element = ele;
				temp2->next = temp;
				Queue *temp3 = prevq(start,temp);
				if(temp3 == NULL)
					start = temp2;
				else
				{
					temp3->next = temp2;
				}
				return;
			}
			else
			{
				while(temp->next != NULL && ele->c > temp->element->c && ele->fre == temp->element->fre)
				{
					if(ele->fre != temp->next->element->fre)
						break;
					temp = temp->next;
				}
				Queue* temp2 = new Queue;
				temp2->element = ele;
				temp2->next = temp->next;
				temp->next = temp2;
				return;
			}
		}
		else if(ele->fre < temp->element->fre)
		{
			Queue* temp2 = new Queue;
			temp2->element = ele;
			temp2->next = temp;
			Queue *temp3 = prevq(start,temp);
			if(temp3 == NULL)
					start = temp2;
			else
			{
				temp3->next = temp2;
			}
			return;

		}
		else
		{
			if(temp->next == NULL)
			{
				Queue* temp2 = new Queue;
				temp2->element = ele;
				temp2->next = temp->next;
				temp->next = temp2;
				return;
			}
			else if(ele->fre > temp->element->fre)
			{
				temp = temp->next;
				continue;
			}
		}
		
	}
}
void maketree(Queue* &start) 							//Links treenode elements in the queue and makes Huffman tree.
{	
	if(start->next == NULL)
		return;
	node *q1 = start->element;
	node *q2 = start->next->element;
	start = start->next->next;
	node *q3 = createElement(q1->c,q1->fre + q2->fre);
	q3->left = q1;
	q3->right = q2;	
	insertPQ(start, q3);
	maketree(start);
}
void printHC(node *root)                     			//Print the Huffman Code.
{
	static char str[10] = "";
	if(root->left == NULL && root->right == NULL)
	{
		printf("%c=%s ",root->c ,str);
		return;
	}
	strcat(str,"0");
	printHC(root->left);
	str[strlen(str)-1] = '\0';
	strcat(str,"1");
	printHC(root->right);
	str[strlen(str)-1] = '\0';
}
int main()
{
	int i;
	Queue* start = NULL;
	int array[256] = {0};
	char str[200];
	printf("Enter string to be coded:\n");		 		//Input string limit is 199
	scanf("%s",str);
	for(i = 0; i<strlen(str); i++)
	{
		array[str[i]]++; 
	}
	for(i = 0; i <256 ; i++)
	{
		if(array[i] != 0)
		{
			node *q = createElement(i, array[i]);
			insertPQ(start,q);
		}
	}
	if(start->next == NULL)
	{
		printf("Single element not needed to be coded. It can be coded either as 0 or 1.\n");
		return 0;
	}
	maketree(start);
	printHC(start->element);
	printf("\n");
}