#include<bits/stdc++.h>
using namespace std;

struct node
{
	int data;
	struct node* next=NULL;
};



class stck
{
	public:
	node* head=NULL;
	int max_size=-1;
	int size=0;

stck(int num)
{
	max_size=num;
}

stck()
{

}

int pop()
{
	if(isempty()==true)
	{
		cout<<"stack is empty\n";
		return INT_MIN;
	}

	else
	{
		node* temp=head;
		if(temp->next==NULL)
		{
			int r=head->data;
			free(head);
			head=NULL;
			size--;
			return r;
		}

		else
		{
			int r=head->data;
			node *temp=head->next;
			free(head);
			head=temp;
			return r;
		}
	}
}

void push(int data)
{
	if(isfull()==true&&max_size!=-1)
	{
		cout<< "stack is already full\n";
	}


	else if(head==NULL)
	{
		node* q=new node;
		q->data=data;
		q->next=NULL;
		head=q;
	}

	else
	{
		node* q=new node;
		q->data=data;
		q->next=NULL;
		node* temp=head;
		head=q;
		q->next=temp;
	}

	size++;
}

bool isempty()
{
	if(head==NULL)
		return true;
	else
		return false;
}

bool isfull()
{
	if(size==max_size)
		return true;
	else
		return false;
}

void print_stack()
{
	node* temp= head;

	while(temp!=NULL)
	{
		cout<<temp->data<<" ";
		temp=temp->next;
	}
	cout<<"\n";
}

};

int main()
{
	char p;
	cout<<"you want to decide a maximum size for stack or not? if yeas then type y if no then type n\n";
	cin>>p;
	if(p=='y')
	{
		cout<<"enter size:";
		int size;
		cin>>size;
		stck s1(size);
		cout<<" encoding is \n 1 push \n 2 pop \n  3 print_que \n 4 isempty \n 5 isfull \n -1 exit enter the option u want to do \n ";
		while(1)
		{
			int r;
			cin>>r;
			if(r==-1) break;
			switch(r)
			{
				case 1: cout<<"enter element:" ; int e; cin>>e; s1.push(e);break;
				case 2: cout<<s1.pop()<<"\n";break;
				case 3: s1.print_stack();break;
				case 4: if(s1.isempty()==true) cout<<"yes empty\n"; else cout<<"no\n" ;break;
				case 5: if(s1.isfull()==true)  cout<<"yes full\n"; else cout<<"no\n";break;
				case 6: break;
			}
		}
	}

	else
	{
		stck s1;
		cout<<" encoding is \n 1 push \n 2 pop \n 3 print_stack \n 4 isempty \n 5 isfull \n -1 exit enter the option u want to do \n";
		while(1)
		{
			int r;
			cin>>r;
			if(r==-1) break;
			switch(r)
			{
				case 1: cout<<"enter element:" ; int e; cin>>e; s1.push(e);break;
				case 2: cout<<s1.pop()<<"\n";break;
				case 3: s1.print_stack();break;
				case 4: if(s1.isempty()==true) cout<<"yes\n"; else cout<<"no\n" ;break;
				case 5: if(s1.isfull()==true)  cout<<"yes full\n"; else cout<<"no\n";break;
				case 6: break;
			}
		}

	}
}
