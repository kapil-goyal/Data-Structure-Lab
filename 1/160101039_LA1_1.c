#include <stdio.h>
#include <stdlib.h>

typedef struct list
{
	int data;
	struct list * nxt;

}node;

node * createnode()
{
	return (node *)malloc(sizeof(node));
}


void printlist(node * start)
{
	node *temp = start;
	while(temp != NULL)
	{
		printf("%d ",temp->data);
		temp = temp->nxt;
	}
	printf("\n");
}

node * findend(node *start)
{
	node *temp = start;
	while(temp->nxt != NULL)
		temp = temp->nxt;
	return temp;
}

node * find2last(node *start,node * p)
{
	node *temp = start;
	if(temp->nxt != NULL)
	{
		while((temp->nxt) != p)
			temp = temp->nxt;
		return temp;
	}
	return temp;
}

void reverselist(node * start)
{
	//node *temp = start;
		node * end = findend(start);
	while(1)
	{
		if(end == start || start == NULL || end == NULL || start->nxt == NULL)
			return;
		if(start->nxt == end)
		{
			int d = end->data;
			end->data = start->data;
			start->data = d;
			return;
		}
		int d = end->data;
		end->data = start->data;
		start->data = d;
		end = find2last(start,end);
		if(start->nxt == NULL)
			break;
		start = start->nxt;
	}
}

void createlist(node *start)
{
	node *temp1 = findend(start);
	
	int c;
	while(1)
	{
		scanf("%d",&c);
		if(c == 0)
		{
			return;
		}
		else
		{
			node *temp = createnode();
			temp->data = c;
			temp->nxt = NULL;
			temp1->nxt = temp;
			temp1 = temp;
		}
	}
}
int main()
{
	node * start;
	start = createnode();
	start->data = 0;
	start->nxt = NULL;

	createlist(start);
	reverselist(start);
	printlist(start);
}