#include<bits/stdc++.h>

using namespace std;
 
bool isBalanced(string expr) 
{ 
	stack<char> s; 
	char x;
	for(int i = 0; i < expr.length(); i++) 
	{ 
		if(expr[i] == '(' || expr[i] == '{' || expr[i] == '[' || expr[i] == '<') 
		{
				s.push(expr[i]);
		}

		if(expr[i] == '|')
		{
				if(!s.empty() && s.top() == '|')
					s.pop();
				else
					s.push(expr[i]);
		}
		else
		{
			if(s.empty())
				return false;
			switch(expr[i]) 
			{ 
				case ')':
					x = s.top(); 
					s.pop(); 
					if(x != '(') 
						return false; 
					break;
				case '}':  
					x = s.top(); 
					s.pop(); 
					if(x != '{') 
						return false; 
					break;
				case ']': 
					x = s.top(); 
					s.pop(); 
					if(x != '[') 
						return false; 
					break;  
				case '>':  
					x = s.top(); 
					s.pop(); 
					if(x != '<') 
						return false; 
					break; 
				
			} 
		}
	} 
	return (s.empty()); 
} 

int main() 
{ 
	int n;
	cin >> n;
	string expr;
	while(n--)
	{
		cin >> expr;
		if(isBalanced(expr))
			cout << "YES\n";
		else
			cout << "NO\n";
	}
	return 0; 
} 

