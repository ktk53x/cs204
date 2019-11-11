#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

class hashing
{
    private:
        int m, hash;
        list<string> * hashtable;
        int hash_function(const string& s)
        {
            hash = 5381;
            for (auto x: s)
                hash = ((hash << 5) + hash) + static_cast<int>(x); 
            return (hash % m);
        }
    public:
        bool search(string&);
        hashing();
        void insert(string);
        void display();
};

hashing::hashing()
{
    hash = 5381;
    m = 111323;
    hashtable = new list<string>[m];
}

bool hashing::search(string& x)
{
    int k = hash_function(x);
    for(auto v : hashtable[k])
        if(v == x)
            return true;
    return false;
}

void hashing::insert(string x)
{
    int k = hash_function(x);
    hashtable[k].push_front(x);
}

void hashing::display()
{
    for(int i = 0; i < m; i++)
    {
        cout << i << " : ";
        for(auto x : hashtable[i])
            cout << x << ' ';
        cout << '\n';
    }
}
hashing t;
int main()
{
    int n;
    bool flag = false;
    cin >> n;
    string s, rs;
    while(n--)
    {
        cin >> s;
        if(!flag)
        {
            rs = s;
            reverse(rs.begin(), rs.end());
            if(s.compare(rs))
            {
                if(t.search(rs))
                    flag = true;
                t.insert(move(s));
            }
        }
    }
    if(flag)
        cout << "YES\n";
    else
        cout << "NO\n";

    return 0;
}