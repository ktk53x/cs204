#include <bits/stdc++.h>
#define inf INT_MIN

using namespace std;

// Node of the evaluation tree
struct node 
{ 
    string val; 
    node* left, *right; 
    node(string s) : left{nullptr}, right{nullptr}, val{s}
    {}
    node() : left{nullptr}, right{nullptr}, val{NULL}
    {}
};

// Function Declarations
bool isOperator(string&);
vector<string>& stringParser(string&, vector<string>&);
vector<string>& unaryMinusReplacer(vector<string>&);
int precedence(string&);
vector<string>& infixToPostfix(vector<string>&, vector<string>&);
bool isNumber(string&);
node* evaluationTreeCreator(vector<string>&);
int evaluation(node* root);

// Global Map
map<string, string> variable;

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
            vector<string> s;
            cin >> a;
            s = stringParser(a, s);
            s = unaryMinusReplacer(s);
            if(s.size() > 1 && !s[1].compare("="))
            {
                vector<string> s2;
                vector<string> p;
                for(int i = 0; i < s.size() - 2; i++)
                {
                    s2.push_back(s[i+2]);
                }
                s2 = unaryMinusReplacer(s2);
                p = infixToPostfix(s2, p);
                node * t = evaluationTreeCreator(p);
                if(variable.find(s[0]) != variable.end())
                {
                    map<string, string>::iterator it  = variable.find(s[0]);
                    it -> second = to_string(evaluation(t));
                }
                else
                {
                    variable.insert(pair<string, string>(s[0], to_string(evaluation(t))));
                }
            }
            else
            {
                vector<string> p;
                p = infixToPostfix(s, p);
                node * t = evaluationTreeCreator(p);
                if(evaluation(t) != inf)
                    cout<< evaluation(t) << '\n';
                else
                    cout << "Can't be evaluated\n";
            }
        }
        variable.clear();
    }
    return 0;
}

bool isOperator(string& c) 
{ 
    if (!c.compare("+") || !c.compare("-") || !c.compare("*") || !c.compare("/") || !c.compare("^") || !c.compare("$")) 
        return true;
    return false; 
} 

int precedence(string& c) 
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

vector<string>& stringParser(string& s, vector<string>& token)
{
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
        //Since numbers and variables are always separated by an operator we can't enter both loops simultaneously
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

vector<string>& unaryMinusReplacer(vector<string>& s)
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

vector<string>& infixToPostfix(vector<string>& s, vector<string>& ans) 
{ 
    stack<string> p;
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
                ans.push_back(c); 
            } 
            if(!(p.top()).compare("(")) 
            { 
                string c = p.top(); 
                p.pop(); 
            } 
        }
        else if(!s[i].compare("+") || !s[i].compare("-") || !s[i].compare("*") || !s[i].compare("/"))
        { 
            while(!p.empty() && (p.top()).compare("(") && precedence(s[i]) <= precedence(p.top())) 
            { 
                string c = p.top(); 
                p.pop(); 
                ans.push_back(c); 
            } 
            p.push(s[i]); 
        }
        else if(!s[i].compare("^") || !s[i].compare("$"))
        {
            while(!p.empty() && (p.top()).compare("(") && precedence(s[i]) < precedence(p.top()))
            {
                string c = p.top();
                p.pop();
                ans.push_back(c);
            }
            p.push(s[i]);
        } 
        else
        {
            ans.push_back(s[i]);
        }
    } 
    while(!p.empty()) 
    { 
        string c = p.top(); 
        p.pop(); 
        ans.push_back(c);
    }
    return ans; 
} 

bool isNumber(string& s)
{
    string::iterator it = s.begin();
    if(*it == '-')
        it++;
    if(it == s.end())
        return false;
    while (it != s.end() && isdigit(*it)) 
        ++it;
    return !s.empty() && it == s.end();
}

node* evaluationTreeCreator(vector<string>& s) 
{ 
    stack<node*> st; 
    node *t, *t1, *t2;
    for (int i = 0; i < s.size(); i++) 
    { 
        if (!isOperator(s[i])) 
        { 
            t = new node(s[i]); 
            st.push(t); 
        }
        else 
        { 
            if(!s[i].compare("$"))
            {
                t = new node("-1");
                st.push(t);
            } 
            t = new node(s[i]); 
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

int evaluation(node* root)  
{   
    if (!root)  
        return 0;   
    if (!root->left && !root->right)
    {  
        if(variable.find(root->val) != variable.end())
        {
            return stoi(variable.at(root->val));
        }
        else
        {
            if(isNumber(root->val))
                return stoi(root->val); 
            else
                return inf;
        } 
    }
    int l_val = evaluation(root->left);  
    int r_val = evaluation(root->right);

    if(l_val == inf || r_val == inf)
        return inf;
    if (root -> val == "+")  
        return l_val + r_val;  
    if (root -> val == "-")  
        return l_val - r_val;  
    if (root -> val == "*")  
        return l_val * r_val;  
    if (root -> val == "/")  
        return l_val / r_val; 
    if (root -> val == "$")
        return l_val * r_val;
    return pow(l_val, r_val);
}
