#include <bits/stdc++.h>
using namespace std;

//struct for linked lists
struct node
{
	int data;
	node * next;
};

//This function creates and allocates memory to a node. 
node *createnode(int d)
{
	node *temp = new node;
	temp->data = d;
	temp->next = NULL;
}

//This function will print the linked list. (Just for checking).
void printlist(node *start)
{
	while(start != NULL)
	{
		if(start->data != INT_MAX)
			printf("%d ",start->data );
		start = start->next;
	}
	printf("\n");
}

// This function will print the tree array. (Just for checking).
void printree(node *tree[],int k)
{	
	for(int i = 0; i<2*k; i++)
	{
		if(tree[i] != NULL)
		printf("=%d ",tree[i]->data );
	}
	printf("\n");
}

//This function will make the final sorted linked list.
void makeFinalseq(node* &start,int d)
{
	if(start == NULL)
	{
		node *temp = createnode(d);
		start = temp;
		return;
	}
	node *temp = start;
	while(temp->next != NULL)
		temp = temp->next;
	temp->next = createnode(d);
}

int main()
{
	int k,chk=0,count=0;
	cout << "Enter no. of sequences: "; 		//scanning of k
	scanf("%d",&k);											

	if(k == 0)
	{
		printf("No sequence to sort\n");
		return 0;
	}

	cout << "Enter Sequences:(Do not enter a space after last element of a sequence.)\n";

	int t = k;						
	while(t>1)
	{
		if(t%2 != 0)
			chk = 1;
		t = t/2;
		count++;
	}
	t = k;

	if(chk == 1)
		{
			k = pow(2,count+1);
		}
	else
		k = t;

	node *tree[2*k];			//Declaration of tree array
	node *sequence[t+1];		//Declaration of sequences array. Sequence[0] will be head of final sorted linked list
	sequence[0] = NULL;			
	for(int i = 0; i<2*k; i++)
	{
		tree[i] = new node;
		tree[i] = createnode(INT_MAX);
	}

	int x = 0;
	int players = 0;			//players will store total no. of elements.
	
	for(int i = 1; i<= t; i++)	//this for loop is used to store inputs given.
	{							//Do not enter a space after a sequence otherwise inputs will not be stored properly.
		
		while(1)
		{
			int d;
			char c;

			scanf("%d",&d);
			if( x == 0)
			{
				sequence[i] = createnode(d);
				tree[k-1+i] = sequence[i];
				x = 1;
				players++;

			}
			else if( x != 0)
			{
				
				sequence[i]->next = createnode(d);
				sequence[i] = sequence[i]->next;
				players++;
			}
			scanf("%c",&c);

			if(c == '\n')
				break;				

		}
		sequence[i]->next = createnode(INT_MAX);
		sequence[i] = sequence[i]->next;
		x = 0;
	}
	if(t == 1)
	{
		printf("Output: ");
		printlist(tree[1]);
		return 1;
	}

	while(k)				//This while loop is used for playing tournament first time.
		{
			for(int i = k; i<2*k ; i++)
			{			
				tree[i/2] = (tree[i]->data)<(tree[i+1]->data) ? tree[i] : tree[i+1];
				i++;
			}
			k = k/2;
		}
	int p = (players);
	while(p)				//In this while loop next winner will be chosen by playing along the winner path.
	{
		if(chk == 1)
		{
			k = pow(2,count+1);
		}
		else
			k = t;

	 	makeFinalseq(sequence[0], tree[1]->data); //This is used to store the winner each time.

	 	if(p == 1)
	 		break;

		int i = 1;

		while(i < k)		//This loop will find the index of winner in the lowest level of tree.
		{			
			i = (tree[2*i]->data)<(tree[2*i+1]->data) ? 2*i : 2*i +1 ;
		}

		tree[i] = tree[i]->next;

		while(i > 1)		//This loop will replay the tournament along the winner path.
		{
			if(i- k > 0 && (i - k)%2 == 1)
				i = i-1;
			tree[i/2] = (tree[i]->data)<(tree[i+1]->data) ? tree[i] : tree[i +1] ;
			i = i/2;
			k = k/2;
		}
		p--;
	}
	printf("Output: ");
	printlist(sequence[0]); //Finally sorted linked list will be printed.

	return 0;
}