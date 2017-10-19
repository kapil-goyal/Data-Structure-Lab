#include <stdio.h>
#include <stdlib.h>

typedef struct list
{
	int data;
	struct list * ptr;
}node;

node * createnode()
{
	return (node *)malloc(sizeof(node));
}

node *checkcirc(node* start)		//Checks circular loop in list
{
	node *temp1, *temp2;
	temp1 = temp2 = start;
	if(temp1 == NULL)
	{
		printf("Empty List\n");
		exit(1);
	}
	temp2 = start->ptr;

	while(1)
	{
		if(temp1 == temp2)
		{
			return temp2;
		}
		if(temp2 == NULL)
		{
			return NULL;
		}
		if(temp2->ptr == NULL)
		{
			return NULL;
		}
		temp1 = temp1->ptr;
		temp2 = (temp2->ptr)->ptr;
	}
}

void insertatStart(node **start, int d)
{
	node *temp = createnode();
	temp->data = d;
	if( *start == NULL)
		temp->ptr = NULL;
	else
		temp->ptr = *start;
	*start = temp;
}

void insertatEnd(node **start, int d)
{
	node *temp = *start;
	if( temp == NULL)
	{
		temp = createnode();
		temp->data = d;
		temp->ptr = NULL;
		*start = temp;
	}

	else
	{	
		if(checkcirc(*start) != NULL)
		{
			printf("Wrong input : Insertion at end not possible\n");
			exit(4);
		}
		while(temp->ptr != NULL)
			temp = temp->ptr;
		node *temp2 = createnode();
		temp2->data = d;
		temp2->ptr = NULL;
		temp->ptr = temp2;
	}	
}

void printlist(node *start, int count)		//Just to check the elements of list.
{
	while(start != NULL && count > 0)
	{
		printf("%d ",start->data);
		start = start->ptr;
		count--;
	}
	printf("\n");
}

node * search(node *start, int d)			//search for an element and return a node
{	
	if(start == NULL)
	{
		printf("Empty List\n");
		exit(2);
	}

	node *temp = checkcirc(start);
	int i = 0;

	while(start != NULL && start->data != d )
	{
		start = start->ptr;
		if(start == temp)
			i++;
		if(i >= 2)
			break;
	}

	if(start == NULL || i >= 2)
		return NULL;
	else
		return start;
	
}

void insert(node *start, int a, int b, int c)		//insert between two elements.
{
	node *temp1 = search(start, a);
	node *temp2 = search(start, c);

	if(temp1 == NULL || temp2 == NULL)
	{
		printf("Wrong Input\n");
		exit(3);
	}

	node *temp = createnode();
	temp->data = b;
	temp->ptr = temp2;
	temp1->ptr = temp;

}

void searchIp(node *start, int a)		//searches and prints the element if found or not.
{
	node *temp = search(start, a);
	if(temp == NULL)
		printf("Output: NOT FOUND\n");
	else
		printf("Output: FOUND\n");
}

int main()
{
	node *start;
	start = NULL;

	int a,b,c,t,count=0;			//count is made for sake of printing list.
	printf("Input Numbers:\n");
	while(1)
	{
		scanf("%d",&a);
		if(a == -1)
			break;
		scanf("%d",&b);
		scanf("%d",&c);

		
		if(a == 0)
		{
			insertatStart(&start, b);
			count++;
		}

		else if(c == 0)
		{
			insertatEnd(&start, b);
			count++;			
		}

		else
		{
			insert(start, a, b, c);
			count++;
		}

	}
	printf("Input no. to be searched:\n");
	scanf("%d",&t);
	searchIp(start,t);
	//printlist(start,count);
}
