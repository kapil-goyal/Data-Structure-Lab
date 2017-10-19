#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
	int data;
	struct _node *next;
}node;

node * createnode()
{
	return (node *)malloc(sizeof(node));
}

void push(node **start, int d)
{
	node *temp = createnode();
	temp->data = d;
	temp->next = *start;
	*start = temp;
}

int pop(node **start)
{
	if(*start == NULL)
		return 0;
	int d = (*start)->data;
	(*start) = (*start)->next;
	return d;
}

int main()
{
	int n;
	printf("Input no. of elements:\n");
	scanf("%d",&n);

	int a[n], b[n], i, j;

	for(i= 0; i<n; i++)
		a[i] = i+1;

	printf("Input your permutation:\n");
	for(i= 0; i<n; i++)
		scanf("%d",&b[i]);

	node *top;
	i = j = 0;

	while(j < n)
	{
		if(i < n && b[j]==a[i] )
		{
			printf("enqueue(Q2, dequeue(Q1)..%d)\n",a[i] );
			i++;
			j++;

		}

		else if(i < n && b[j] > a[i])
		{
			while(b[j] != a[i])
			{
				push(&top, a[i]);
				printf("push(S, dequeue(Q1)..%d)\n",a[i] );
				i++;
			}
			printf("enqueue(Q2, dequeue(Q1)..%d)\n",a[i] );
			i++;
			j++;
		}

		else
		{
			int d = pop(&top);
			if(d == b[j])
			{
				printf("enqueue(Q2, pop(S)..%d)\n",d );
				j++;
			}
			else
			{
				printf("It is NOT a Stack Permutation, since next element should have been %d instead of %d\n",d,b[j]);
				return 0;
			}

		}
	}


}