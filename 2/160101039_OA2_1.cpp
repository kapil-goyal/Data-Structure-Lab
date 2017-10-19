#include <bits/stdc++.h>
#include <iostream>
#include <new>
using namespace std;

struct mqueue											//Struct for queue of files
{
	char p[50];
	mqueue* next;
};
void deletewqueue(mqueue *start)						//Delete queue of files
{
	if(start == NULL)
		return;
	mqueue *temp = start;
	start = start->next;
	temp = NULL;
	if(start != NULL)
		deletewqueue(start->next);
}

struct node												//Struct for folders
{
	char name[50];
	node* child;
	node* parent;
	mqueue* Q;
};

void createFolder(node **current, char name[])			//function to create a folder
{
	cout << "Made " << name << " in " << (*current)->name << endl;
	(*current)->child = new node;
	(*current)->child->parent = *current;
	*current = (*current)->child;
	strcpy((*current)->name,name);
	return;
}

void deleteFolder(node **current)						//function to delete a folder and hence all files in it.
{

	node *temp = *current;
	if((*current)->parent == NULL)
	{
		cout << "Cannot back from root"<< endl;
		return;
	}
	cout << "Back from "<< (*current)->name << endl;
	*current = (*current)->parent;	
	deletewqueue(temp->Q);
	temp = NULL;
}

void createFile(node *current, char p[])				//function to create file
{
	cout << "Created "<< p << " in " << current->name << endl;
	if(current->Q == NULL)
	{
		mqueue *temp = new mqueue;
		strcpy(temp->p,p);
		temp->next = NULL;
		current->Q = temp;
		return;
	}
	else
	{	
		mqueue *temp1 = current->Q;
		while((temp1)->next != NULL)
			temp1 = (temp1)->next;
		mqueue *temp = new mqueue;
		strcpy(temp->p,p);
		temp->next = NULL;
		(temp1)->next = temp;
		return;
	}

}

void deleteFile(node *current)							//function to delete a file
{
	if(current->Q == NULL)
	{	
		printf("Cannot delete from %s\n",current->name);
		return;
	}
	cout << "Deleted "<< (current->Q)->p << " from " << current->name << endl;

	mqueue *temp1;
	temp1 = current->Q;
	current->Q = (current->Q)->next;
	//free(temp1);
	temp1 = NULL;
	return;
	
}

int main()
{	
	node* root = new node;
	char p[100] = "root";
	strcpy(root->name,p);
	node* current = root;
	root->parent == NULL;
	while(1)
	{
		cin >> p;
		if(p[0] == '-')
			break;
		if(!strcmp(p,"CREATE"))
		{
			cin >> p;
			createFile(current,p);
		}
		else if(!strcmp(p,"NEW"))
		{
			cin >> p;
			createFolder(&current,p);
		}
		else if(!strcmp(p,"DELETE"))
		{
			deleteFile(current);
		}
		else if(!strcmp(p,"BACK"))
		{
			deleteFolder(&current);
		}
		else
		{
			cout << "Command not found\n" ;
		}
	}
}