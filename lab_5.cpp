#include <bits/stdc++.h>
#define inf INT_MIN

using namespace std;

map<string, string> my_map;

bool isOperator(string c) 
{ 
    if (!c.compare("+") || !c.compare("-") || !c.compare("*") || !c.compare("/") || !c.compare("^") || !c.compare("$")) 
        return true;
    return false; 
} 

vector<string> StringParser(string s)
{
    vector<string> token;
    int j, count;
    for(int i = 0; i < s.size(); i++)
    {
        j = i;
        count = 0;
        while(j < s.size() && s[j] >= '0' && s[j] <= '9')
        {
            count++;
            j++;
        }
        while(j < s.size() && ((s[j] >= 'a' && s[j] <= 'z') || (s[j] >= 'A' && s[j] <= 'Z')))
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

vector<string> UnaryMinusReplacer(vector<string> s)
{   
    for(int i = 0; i < s.size(); i++)
    {
        if(!s[i].compare("-") && (i == 0 || !s[i-1].compare("(") || isOperator(s[i-1])))
        {
            s[i] = "$";
        }
    }
    return s;
}

int prec(string c) 
{ 
    if(!c.compare("$"))
        return 4;
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
        else if(!s[i].compare("$"))
        {
            while(!p.empty() && (p.top()).compare("(") && prec(s[i]) < prec(p.top()))
            {
                string c = p.top();
                p.pop();
                ans.push(c);
            }
            p.push(s[i]);
        }
        else if(!s[i].compare("^"))
        {
            while(!p.empty() && (p.top()).compare("(") && prec(s[i]) < prec(p.top()))
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

/*vector<string> UnaryMinusRemoval(vector<string> s)
{
    for(int i = 0; i < s.size(); i++)
    {
        if(!s[i].compare("$"))
        {
            for(int j = 0; j < i; j++)
            {
                if(!isOperator(s[j]))
                {
                    if(s[j][0] == '-')
                    {
                        s[j].erase(s[j].begin());
                    }
                    else
                    {
                        s[j].insert(0, "-");
                    }
                }
            }

        }
    }
    return s;
}*/

struct node 
{ 
    string val; 
    node* left, *right; 
};

node* newNode(string v) 
{ 
    node * temp = new node; 
    temp->left = nullptr; 
    temp->right = nullptr;
    temp->val = v; 
    return temp; 
} 

bool is_number(string& s)
{
    string::const_iterator it = s.begin();
    if(*it == '-')
        it++;
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

int eval(node* root)  
{   
    if (!root)  
        return 0;   
    if (!root->left && !root->right)
    {  
        if(my_map.find(root->val) != my_map.end())
        {
            return stoi(my_map.at(root->val));
        }
        else
        {
            if(is_number(root->val))
                return stoi(root->val); 
            else
            {
                return inf;
            }
        } 
    }
    int l_val = eval(root->left);  
    int r_val = eval(root->right);
    if(l_val == inf || r_val == inf)
        return inf;  
    if (root->val=="+")  
        return l_val+r_val;  
  
    if (root->val=="-")  
        return l_val-r_val;  
  
    if (root->val=="*")  
        return l_val*r_val;  
        
    if (root->val=="/")  
        return l_val/r_val; 
    if (root->val=="$")
        return l_val*r_val;
  
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
            if(!s[i].compare("$"))
            {
                t = newNode("-1");
                st.push(t);
            } 
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
            s = UnaryMinusReplacer(s);
            if(s.size() > 1 && !s[1].compare("="))
            {
                vector<string> v;
                vector<string> s2;
                for(int i = 0; i < s.size() - 2; i++)
                {
                    s2.push_back(s[i+2]);
                }
                s2 = UnaryMinusReplacer(s2);
                p = InfixToPostfix(s2);
                while(!p.empty())
                {
                    v.push_back(p.top());
                    p.pop();
                }
                reverse(v.begin(), v.end());
                node * t = Tree(v);
                if(my_map.find(s[0]) != my_map.end())
                {
                    map<string, string>::iterator it  = my_map.find(s[0]);
                    it -> second = to_string(eval(t));
                }
                else
                {
                    my_map.insert(pair<string, string>(s[0], to_string(eval(t))));
                }
            }
            else
            {
                vector<string> v;
                p = InfixToPostfix(s);
                while(!p.empty())
                {
                    v.push_back(p.top());
                    p.pop();
                }
                reverse(v.begin(), v.end());
                node *t = Tree(v);
                if(eval(t) != inf)
                    cout<< eval(t) << '\n';
                else
                    cout << "Cant be evaluated\n";
            }
        }
    }
    return 0;
}