#include <bits/stdc++.h>
using namespace std;

//Struct for binomial node.
struct btNode
{
	int key;
	int degree;
	btNode *parent, *child, *sibling;	
};

//this function will create a binomial tree node.
btNode* createBtNode(int key)
{
	btNode* temp = new btNode;
	temp->key = key;
	temp->degree = 0;
	temp->parent = temp->sibling = temp->child = NULL;
	return temp;
}

//this function will link two binomial trees of same degree and return the head.
btNode* binomial_link(btNode *head1, btNode *head2)
{
	if(head1 == NULL)
		return head2;

	if(head2 == NULL)
		return head1;

	if(head1->key < head2->key)
		swap(head1, head2);

	head1->sibling = head2->child;
	head2->child = head1;
	head1->parent = head2;
	head2->degree++;

	return head2;
}

//Show heap function will show binomial heap
void ShowHeap(btNode *x, int depth)
{
	if(x->sibling != NULL)
		ShowHeap(x->sibling, depth);

	if((x->child != NULL) || ( x->parent == NULL))
	{
		for (int i = 0; i < depth + 1; ++i)
		{
			cout << "\t";
		}
		cout << x->key;

		if(x->child == NULL)
			cout << endl ;
	}
	else
	{
			cout << "\t" << x->key << endl;
	}
	if(x->child != NULL)
		ShowHeap(x->child, depth+1);	
}

//This function will call showheap function
void showBinomialHeap(btNode *head)
{
	if( head == NULL)
		cout << "Empty heap\n";
	else
	{
		cout << "Stucture of binomial heap (rotated 90 degrees ccwise):\n";
		ShowHeap(head, 0);
	}
}

//this function will merge two binomial heaps acc. to ascending order of degree.
btNode* mergeBH(btNode* head1, btNode* head2)
{
	btNode *temp1 = head1, *temp2 = head2, *temp, *head;

	if(head1 == NULL)
		return head2;

	if(head2 == NULL)
		return head1;

	if(head1->degree < head2->degree)
	{
		head = head1;
		temp1 = temp1->sibling;
	}
	else
	{
		head = head2;
		temp2 = temp2->sibling;
	}
	temp = head;
	temp->sibling = NULL;

	while(temp1 != NULL && temp2 != NULL)
	{
		if(temp1->degree < temp2->degree)
		{
			temp->sibling = temp1;
			temp1 = temp1->sibling;
			temp = temp->sibling;
			temp->sibling = NULL;
		}
		else
		{
			temp->sibling = temp2;
			temp2 = temp2->sibling;
			temp = temp->sibling;
			temp->sibling = NULL;
		}
	}

	if(temp1 != NULL)
		temp->sibling = temp1;
	if(temp2 != NULL)
		temp->sibling = temp2;

	return head;
}


//This function will make union of two merged meaps.
btNode* UnionBH(btNode *head1, btNode *head2)
{
	btNode *head = mergeBH(head1, head2);

	if(head == NULL)
		return NULL;

	btNode *prev_x = createBtNode(INT_MAX);
	btNode *beforeHead = prev_x;
	prev_x->sibling = head;
	btNode *x = head;
	btNode *next_x = x->sibling;

	while(next_x != NULL)
	{
		if(x->degree == next_x->degree)
		{
			if(next_x->sibling != NULL)
			{
				if(x->degree != next_x->sibling->degree)
				{
				
					btNode *temp = next_x->sibling;
					x = binomial_link(x, next_x);
					next_x = temp;
					x->sibling = next_x;
					prev_x->sibling = x;
				}
				else
				{
					prev_x = prev_x->sibling;
					x = x->sibling;
					next_x = next_x->sibling;
				}
			}
			else
			{
				btNode *temp = next_x->sibling;
				x = binomial_link(x, next_x);
				next_x = temp;
				x->sibling = next_x;
				prev_x->sibling = x;
			}
		}
		else
		{
			prev_x = prev_x->sibling;
			x = x->sibling;
			next_x = next_x->sibling;
		}
	}
	head = beforeHead->sibling;
	beforeHead->sibling = NULL;
	delete beforeHead;

	return head;
}

//Insertion in Binomial heap.
btNode* insertBH(btNode *head, int x )
{
	btNode *temp = createBtNode(x);

	if(head == NULL)
		return temp;

	head = UnionBH(head, temp);
	return head;
}

//This function will return node previous to the node x such that head is sibling of x.
btNode* prevNode(btNode *head, btNode* x)
{
	btNode *temp = head;
	if(x == head || head == NULL)
		return NULL;
	while(temp->sibling != x)
	{
		temp = temp->sibling;
	}
	return temp;
}

//This will return key of minimum node.
int ExtractMin(btNode* &head)
{
	int minKey;

	btNode *temp = head;
	btNode *min = head;

	if(head == NULL)
		return INT_MAX;

	while(temp != NULL)
	{
		if(temp->key < min->key)
			min = temp;
		temp = temp->sibling;
	}

	btNode *prev = prevNode(head, min);

	if(prev != NULL)
		prev->sibling = min->sibling;

	btNode *childHead = min->child;
	btNode *childTemp = childHead;
	btNode *last = childTemp;

	min->child =  NULL;

	if(min == head)
		head = min->sibling;

	min->sibling = NULL;		
	
	if(childHead != NULL)
	{
		childHead->parent = NULL;

		while(childTemp->sibling != NULL)
			childTemp = childTemp->sibling;
		last = childTemp;

		btNode *prevChild = prevNode(childHead, childTemp);

		while(prevChild != NULL)
		{
			prevChild->sibling = NULL;
			childTemp->sibling = prevChild;
			childTemp = prevChild;
			prevChild = prevNode(childHead, childTemp);
		}
	}

	head = UnionBH(head, last);
	minKey = min->key ;

	delete min;

	return minKey;
}

//This function will delete the binomial heap and will start new heap.
void makeBH(btNode* &head)
{
	if(head == NULL)
		return;

	if(head->sibling != NULL)
		makeBH(head->sibling);

	if(head->child != NULL)
		makeBH(head->child);


		head = NULL;
		delete head;		
}
int main()
{
	btNode *head = NULL; //head of BH
	int flag = 1;		//print flag
	cout << "type 'quit' to exit the program!! \n";
	string word;		//this take input command and following while loop will operate acc. to the command.
	while((cin >> word))
	{
		if(word == "#")	//if # is i/p command then ignore rest till new line
		{
			cin.ignore(2e9,'\n');
		}
		else if(word == "c")	//if c is i/p command, then previous heap will be deleted new heap will be created
		{
			makeBH(head);
			head = NULL;
			cout << "New heap created\n";
		}
		else if(word == "S")	//if S is i/p command then heap will be shown
		{
			cout << endl;
			showBinomialHeap(head);
			cout << endl;
		}
		else if(word == "+")	//flag will be turned on
			flag = 1;
		else if(word == "-")	//flag will be turned off
			flag = 0;
		else if(word == "i")	//insertion in BH will happen
		{
			int d;
			cin >> d;
			head = insertBH(head,d);
		}
		else if(word == "d")	//minimum from BH will be extracted
		{
			int d = ExtractMin(head);
			if(d == INT_MAX)
				cout << "Empty Heap!!\n";
			else
			{
				if(flag)
					cout << "Minimum Extracted: " << d << endl;
			}
		}
		else if(word == "quit")	//quit the program
		{
			break;
		}
		else if(word == "u");
		else					//if command is none of the above, then it is invalid command.
		{
			cout << "Invalid command!!\n";
		}
	}
}