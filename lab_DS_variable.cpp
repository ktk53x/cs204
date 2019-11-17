#include <bits/stdc++.h> 
using namespace std; 

struct Node 
{ 
	int key; 
	vector<Node *>child; 
}; 

Node *newNode(int key) 
{ 
	Node *temp = new Node; 
	temp->key = key; 
	return temp; 
} 

void LevelOrderTraversal(Node * root) 
{ 
	if (root==NULL) 
		return; 
	queue<Node *> q;
	q.push(root);
	while (!q.empty()) 
	{ 
		int n = q.size(); 
		while (n > 0) 
		{ 
			Node * p = q.front(); 
			q.pop(); 
			cout << p->key << " "; 
			for (int i=0; i<p->child.size(); i++) 
				q.push(p->child[i]); 
			n--; 
		} 

		cout << endl;
	} 
} 

int main() 
{ 
	Node *root = newNode(10); 
    srand(time(nullptr));
    for(int i = 0; i < 4; i++)
        (root->child).push_back(newNode(rand() % 10)); 
    for(int i = 0; i < 2; i++)
        (root->child[0]->child).push_back(newNode(rand() % 10));
	
	(root->child[2]->child).push_back(newNode(1)); 
    for(int i = 0; i < 3; i++)
        (root->child[3]->child).push_back(newNode(rand() % 10)); 

	cout << "Level order traversal\n"; 
	LevelOrderTraversal(root); 
	
	return 0; 
} 