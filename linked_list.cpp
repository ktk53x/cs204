#include <iostream>

using namespace std;

struct node
{
	int x;
	int y;
	node * next;
};

class LinkedList
{
	private:
		node * head, * tail;
	public:
		LinkedList()
		{
			head = nullptr;
			tail = nullptr;
		}
		void AddEnd(int, int);
		void AddFirst(int, int);
		void DelFirst();
		void Del(int, int);
		void Search(double);
		bool Search(int, int);
		long long Length();
};

void LinkedList::AddEnd(int x, int y)
{
	node * temp = new node;
	temp -> x = x;
	temp -> y = y;
	temp -> next = nullptr;
	if(head == nullptr)
	{
		head = temp;
		tail = temp;
		temp = nullptr;
	}
	else
	{
		tail -> next = temp;
		tail = temp;
		temp = nullptr; //I added this
	}
}

void LinkedList::AddFirst(int x, int y)
{
	node * temp = new node;
	temp -> x = x;
	temp -> y = y;
	temp -> next = nullptr;
	if(head == nullptr)
	{
		head = temp;
		tail = temp;
		temp = nullptr;
	}
	else
	{
		temp -> next = head;
		head = temp;
	}
}

void LinkedList::DelFirst()
{
	if(head == nullptr)
	{
		cout << "-1\n";//Exception Handling
	}
	else
	{
		if(head == tail)
		{
			node * temp = head;
			head = nullptr;
			tail = nullptr;
			delete temp;
		}
		else
		{
			node * temp = head;
			head = head -> next;
			delete temp;
		}
	}
}

void LinkedList::Del(int x, int y)
{
	if(head == nullptr)
	{
		cout << "-1\n";
		return;//Exception Handling
	}
	else if(head == tail)
	{
		if(head -> x == x && head -> y == y)
		{
			node * temp = head;
			head = nullptr;
			tail = nullptr;
			delete temp;
		}
		else
		{
			cout << "-1\n";
			return;
		}
	}
	else
	{
		node * current = head, * prev;
		while(current != nullptr && current -> x != x && current -> y != y)
		{
			prev = current;
			current = current -> next;
		}
		if(current == nullptr)
		{
			cout << "-1\n";
			return;
		}
		if(current == head)
		{
			node * temp = head;
			head = head -> next;
			delete temp;
			return;
		}
		if(current == tail)
		{
			node * temp = tail;
			prev = tail;
			delete temp;
			return;
		}
		
		prev -> next = current -> next;
		delete current;
	}	
}

void LinkedList::Search(double d)
{
	long long count = 0;
	if(head == nullptr)
	{
		cout << "-1\n";//Exception Handling
	}
	else
	{
		node * current = head;
		while(current != nullptr)
		{
			long long d1 = (long long)(current -> x) * (current -> x);
			long long d2 = (long long)(current -> y) * (current -> y);
			long long d3 = d1 + d2;
			if(d3 <= d * d) // Check for out of range for integer
			{
				count++;
			}
			current = current -> next;
		}
	}
	if(count)
		cout << count << '\n';
	else
		cout << "-1\n";
}

bool LinkedList::Search(int x, int y)
{
	if(head == nullptr)
	{
		return false;//Exception Handling
	}
	else
	{
		node * current = head;
		while(current != nullptr)
		{
			if(current -> x == x && current -> y == y)
				return true;
			current = current -> next;
		}
		return false;
	}
}

long long LinkedList::Length()
{
	if(head == nullptr)
	{
		return 0;
	}
	else
	{
		long long count = 1;
		node * current = head;
		while(current != tail)
		{
			count++;
			current = current -> next;
		}
		return count;
	}
}


int main()
{
	LinkedList l;
	int choice, x, y, d;
	long long q;
	cin >> q;
	while(q > 0)
	{
		cin >> choice;
		switch(choice)
		{
			case 1:
				cin >> x >> y;
				l.AddFirst(x, y);
				break;
			case 2: 
				l.DelFirst();
				break;
			case 3:
				cin >> x >> y;
				l.Del(x, y);
				break;
			case 4:
				cin >> d;
				l.Search(d);
				break;
			case 5:
				cin >> x >> y;
				if(l.Search(x, y))
					cout << "True\n";
				else
					cout << "False\n";
				break;
			case 6:
				cout << l.Length() << '\n';
				break;
		}
		q--;
	}
	return 0;
}
