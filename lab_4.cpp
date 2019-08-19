#include <bits/stdc++.h>

using namespace std;

vector<string> StringParser(string s)
{
	vector<string> token;
	int j, count;
	for(int i = 0; i < s.size(); i++)
	{
		j = i;
		count = 0;
		while(s[j] >= '0' && s[j] <= '9')
		{
			count++;
			j++;
		}
		if(j == i)
		{
			string a(1, s[i]);
			token.push_back(a);
		}
		else
		{
			token.push_back(s.substr(i, count));
			i = j - 1;
		}
		
	}
	return token;
}


int prec(string c) 
{ 
    if(!c.compare("^"))
    	return 3;
    if(!c.compare("*") || !c.compare("/")) 
    	return 2; 
    if(!c.compare("+") || !c.compare("-")) 
    	return 1;
} 

stack<string> InfixToPostfix(vector<string> s) 
{ 
    stack<string> p, ans;
    for(int i = 0; i < s.size(); i++) 
    { 
        if(!s[i].compare("(")) 
 		p.push("("); 
 		
        else if(!s[i].compare(")")) 
        { 
            while(!p.empty() && (p.top()).compare("(")) 
            { 
                string c = p.top(); 
                p.pop(); 
               	ans.push(c); 
            } 
            if(!(p.top()).compare("(")) 
            { 
                string c = p.top(); 
                p.pop(); 
            } 
        }    
        else if(!s[i].compare("+") || !s[i].compare("-") || !s[i].compare("*") || !s[i].compare("/"))
        { 
            while(!p.empty() && (p.top()).compare("(") && prec(s[i]) <= prec(p.top())) 
            { 
                string c = p.top(); 
                p.pop(); 
                ans.push(c); 
            } 
            p.push(s[i]); 
        }
        else if(!s[i].compare("^"))
        {
        	while(!p.empty() && prec(s[i]) < prec(p.top()))
        	{
        		string c = p.top();
        		p.pop();
        		ans.push(c);
        	}
        	p.push(s[i]);
        } 
        else
        {
        	ans.push(s[i]);
        }
  
    } 
    
    while(!p.empty()) 
    { 
        string c = p.top(); 
        p.pop(); 
        ans.push(c);
    }
    return ans; 
} 

struct node 
{ 
    string val; 
    node* left, *right; 
};

bool isOperator(string c) 
{ 
    if (!c.compare("+") || !c.compare("-") || !c.compare("*") || !c.compare("/") || !c.compare("^")) 
        return true;
    return false; 
} 


node* newNode(string v) 
{ 
    node * temp = new node; 
    temp->left = nullptr; 
    temp->right = nullptr;
    temp->val = v; 
    return temp; 
} 

int eval(node* root)  
{   
    if (!root)  
        return 0;   
    if (!root->left && !root->right)  
        return stoi(root->val);  
    int l_val = eval(root->left);  
    int r_val = eval(root->right);  
    if (root->val=="+")  
        return l_val+r_val;  
  
    if (root->val=="-")  
        return l_val-r_val;  
  
    if (root->val=="*")  
        return l_val*r_val;  
        
    if (root->val=="/")  
        return l_val/r_val; 
  
    return pow(l_val, r_val);
}


node* Tree(vector<string> s) 
{ 
    stack<node*> st; 
    node *t, *t1, *t2;
    for (int i=0; i < s.size(); i++) 
    { 
        if (!isOperator(s[i])) 
        { 
            t = newNode(s[i]); 
            st.push(t); 
        } 
        else 
        { 
            t = newNode(s[i]); 
            t1 = st.top();
            st.pop();
            t2 = st.top(); 
            st.pop();
            t->right = t1; 
            t->left = t2; 
            st.push(t); 
        } 
    }
    t = st.top(); 
    st.pop(); 
  
    return t; 
} 


int main()
{
	int q, n;
	cin >> q;
	while(q--)
	{
		cin >> n;
		while(n--)
		{
			string a;
			stack<string> p;
			cin >> a;
			vector<string> s = StringParser(a);
			vector<string> v;
			p = InfixToPostfix(s);
			while(!p.empty())
			{
				v.push_back(p.top());
				p.pop();
			}
			reverse(v.begin(), v.end());
			node *t = Tree(v);
			cout<< eval(t) << '\n';
		}
	}
	return 0;
}
