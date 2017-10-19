#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define true 1
#define false 0


typedef struct stack
{
	float data;
	struct stack *next;
}node;

node *createnode()
{
	return (node *)malloc(sizeof(node));
}

node * push(node *start, float d)
{
	node *temp;
	temp = (node *)malloc(sizeof(node));
	temp->data = d;
	temp->next = start;
	start = temp;
	return start;
}
int isempty(node *start)
{
	if(start == NULL)
		return true;
	else
		return false;
}

float pop(node **start)
{
	if(*start != NULL)
	{
		float d = (*start)->data;
		(*start) = (*start)->next;
		return d;
	}
	else
		return 0;	
}



int main()
{
	node *top = NULL;
	char a[35];
	scanf("%s",a);
	int i;
	float sum = 0,p,b;
	for(i = 0;a[i] != '\0'; i++)
	{
		if( a[i] >= '0' && a[i] <= '9')
			top = push(top,a[i]-'0');
		else if(a[i] == '+') 
		{
			if(isempty(top))
			{
				printf("Incorrect Input\n");
				return 0;
			}
			p = pop(&top);
			if(isempty(top))
			{
				printf("Incorrect Input\n");
				return 0;
			}
			b = pop(&top);
			top = push(top,p + b);
		}
		else if(a[i] == '*') 
		{
			if(isempty(top))
			{
				printf("Incorrect Input\n");
				return 0;
			}

			p = pop(&top);
			if(isempty(top))
			{
				printf("Incorrect Input\n");
				return 0;
			}
			b = pop(&top);
			
			top = push(top,p * b);
		}
		else if(a[i] == '-') 
		{
			if(isempty(top))
			{
				printf("Incorrect Input\n");
				return 0;
			}
			p = pop(&top);
			if(isempty(top))
			{
				printf("Incorrect Input\n");
				return 0;
			}
			b = pop(&top);
			top = push(top, b-p);
		}
		else if(a[i] == '/') 
		{	
			if(isempty(top))
			{
				printf("Incorrect Input\n");
				return 0;
			}
			p = pop(&top);
			if(isempty(top))
			{
				printf("Incorrect Input\n");
				return 0;
			}
			b = pop(&top);
			top = push(top,b/p);
		}
		else if(a[i] == '$') 
		{
			if(isempty(top))
			{
				printf("Incorrect Input\n");
				return 0;
			}
			p = pop(&top);
			if(isempty(top))
			{
				printf("Incorrect Input\n");
				return 0;
			}
			b = pop(&top);
			top = push(top,pow(b,p));
		}

	}
	if(isempty(top))
			{
				printf("Incorrect Input\n");
				return 0;
			}
	sum = pop(&top);
	if(!isempty(top))
			{
				printf("Incorrect Input\n");
				return 0;
			}

		printf("%f\n",sum);
}