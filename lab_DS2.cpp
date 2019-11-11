#include<iostream>
#include<algorithm>
#include<vector>
//#include<list>

using namespace std;

struct node
{
    int data;
    node * next;
    node(int d) : data{d}, next{nullptr}
    {}
};

class list
{
    private:
        node * head;
    public:
        list();
        void del(int);
        void del_at_end();
        void del_at_front();
        void search_and_insert(int, int);
        node * insert_at_end(int);
        node * insert_at_front(int);
        node * search(int);
        void display();
};

list::list()
{
    head = nullptr;
}

node * list::search(int d)
{
    node * temp = head;
    while(temp != nullptr)
    {
        if(temp -> data == d)
            break;
        temp = temp -> next;
    }
    return temp;
}

node * list::insert_at_front(int d)
{
    node * temp = new node(d);
    temp -> next = head;
    head = temp;
}

node * list::insert_at_end(int d)
{
    node * temp = new node(d), * temp2 = head;
    if(!head)
        return head = temp;
    while(temp2 -> next != nullptr)
        temp2 = temp2 -> next;
    temp2 -> next = temp;
    return temp;
}

void list::del(int d)
{
    node * temp = head, * prev = nullptr;
    while(temp != nullptr)
    {
        if(temp -> data == d)
        {
            if(prev)
            {
                prev -> next = temp -> next;
                break;
            }
            else
            {
                head = temp -> next;
                break;
            }
            delete(temp);
        }
        prev = temp;
        temp = temp -> next;
    }
}

void list::del_at_front()
{
    node * temp;
    if(head)
    {
        temp = head;
        head = head -> next;
        delete(temp);
    }
}

void list::del_at_end()
{
    node * temp = head, * prev = nullptr;
    if(head)
    {
        while(temp != nullptr)
        {
            prev = temp;
            temp = temp -> next;
        }
        if(prev == head)
            head = nullptr;
        delete(prev);
    }
}

void list::display()
{
    node * temp = head;
    while(temp != nullptr)
    {
        cout << temp -> data << ' ';
        temp = temp -> next;
    }
    cout << '\n';
}

void list::search_and_insert(int n, int d)
{
    node * temp = head, * temp2 = new node(d), *prev = nullptr;
    while(temp != nullptr)
    {
        if(temp -> data == n)
        {
            if(!prev)
                insert_at_front(d);
            else 
            {
                prev -> next = temp2;
                temp2 -> next = temp;
            }
            break;
        }
        prev = temp;
        temp = temp -> next;
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------
/*class dsu
{
    private:
        vector<int> parent, rank;
    public:
        dsu(int);
        void union_set(int, int);
        int find_set(int);
        bool is_same_set(int, int);
};

dsu::dsu(int n)
{
    rank.assign(n, 0);
    parent.reserve(n);
    for(int i = 0; i < n; i++)
        parent[i] = i;
}

int dsu::find_set(int i)
{
    if(parent[i] == i)
        return i;
    parent[i] = find_set(parent[i]);
    return parent[i];
}

bool dsu::is_same_set(int i, int j)
{
    return find_set(i) == find_set(j);
}

void dsu::union_set(int i, int j)
{
    if(!is_same_set(i, j))
    {
        int i_p = find_set(i), j_p = find_set(j);
        if(rank[i_p] == rank[j_p])
        {
            rank[i_p] += 1;
            parent[j_p] = i_p;
        }
        else if(rank[i_p] > rank[j_p])
            parent[j_p] = i_p;
        else 
            parent[i_p] = j_p;
    }
}
*/

//-------------------------------------------------------------------------------------------------------------------------------------
/*struct treap_node
{
    int key;
    int priority;
    treap_node * left, * right;
    treap_node(int k) : key{k}, priority{rand()}, left{nullptr}, right{nullptr}
    {}
};

class treap
{
    private:
        treap_node * root;
        treap_node * right_rotate(treap_node * x)
        {
            treap_node * y = x -> left;
            x -> left = y -> right;
            y -> right = x;
            return y;
        }
        treap_node * left_rotate(treap_node * x)
        {
            treap_node * y = x -> right;
            x -> right = y -> left;
            y -> left = x;
            return y;
        }
        treap_node * search(int k, treap_node * r)
        {
            if(!r || r -> key == k)
                return r;
            
            if(k < r -> key)
                return search(k, r -> left);
            else if(k > r -> key)
                return search(k, r -> right);
        }
        treap_node * insert(int k, treap_node * &r)
        {
            if(!r)
                return r = new treap_node(k);
            if(k <= r -> key)
            {
                insert(k, r -> left);
                if(r -> priority < r -> left -> priority)
                    return r = right_rotate(r);
            }
            else if(k > r -> key)
            {
                insert(k, r -> right);
                if(r -> priority < r -> right -> priority)
                    return r = left_rotate(r);
            }
        }
        void remove(int k, treap_node * &r)
        {
            if(!r)
                return;
            if(k < r -> key)
                remove(k, r -> left);
            else if(k > r -> key)
                remove(k, r -> right);
            else if(r -> left == nullptr && r -> right == nullptr)
            {
                delete(r);
                r = nullptr;
            }
            else if(r -> left == nullptr)
            {
                r = left_rotate(r);
                remove(k, r -> left);
            }
            else if(r -> right == nullptr)
            {
                r = right_rotate(r);
                remove(k, r -> right);
            }
            else
            {
                if(r -> right -> priority > r -> left -> priority)
                {
                    r = left_rotate(r);
                    remove(k, r -> left);
                }
                else
                {
                    r = right_rotate(r);
                    remove(k, r -> right);
                }
                
            }
            

        }
    public:
        treap() : root{} {}
        void search(int k)
        {
            if(search(k, root))
                cout << "Found\n";
            else 
                cout << "Not Found\n";
        }
        treap_node * insert(int k)
        {
            return insert(k, root);
        }
        void remove(int k)
        {
            remove(k, root);
        }
};
*/


//-------------------------------------------------------------------------------------------------------------------------------------
/*class hashtable
{
    private:
        int m;
        list<int> * table;
        int hashfunction(int x)
        {
            return x % m;
        }
    public:
        hashtable(int);
        void search(int);
        void insert(int);
        void del(int);
        void display();

};

hashtable::hashtable(int x)
{
    m = x;
    table = new list<int>[m];
}

void hashtable::search(int x)
{
    int k = hashfunction(x);
    for(auto i = table[k].begin(); i != table[k].end(); i++)
    {
        if(*i == x)
        {
            cout << "Found\n";
            return;
        }
    }
    cout << "Not Found\n";  
}

void hashtable::insert(int x)
{
    int k = hashfunction(x);
    table[k].push_front(x);
}

void hashtable::del(int x)
{
    int k = hashfunction(x);
    table[k].remove(x);
}

void hashtable::display()
{
    for(int i = 0; i < m; i++)
    {
        cout << i << " : ";
        for(auto x = table[i].begin(); x != table[i].end(); x++)
            cout << *x << ' ';
        cout << '\n';
    }
}

class hashtable_lp
{
    private:
        int m;
        int hashfunction(int x)
        {
            return x % m;
        }
        vector<int> table;
    public:
        hashtable_lp(int);
        void search(int);
        void insert(int);
        void del(int);
        void display();
};

hashtable_lp::hashtable_lp(int x)
{
    m = x;
    table.assign(m, INT32_MAX);
}

void hashtable_lp::search(int x)
{
    int k = hashfunction(x);
    while(table[k] != x && table[k] != INT32_MAX)
        k = (k + 1) % m;
    if(table[k] == x)
        cout << "Found\n";
    else 
        cout << "Not Found\n";
}

void hashtable_lp::insert(int x)
{
    int k = hashfunction(x);
    while(table[k] != INT32_MAX && table[k] != INT32_MIN)
        k = (k + 1) % m;
    table[k] = x;
}

void hashtable_lp::del(int x)
{
    int k = hashfunction(x);
    while(table[k] != x && table[k] != INT32_MAX)
        k = (k + 1) % m;
    table[k] = INT32_MIN;
}

void hashtable_lp::display()
{
    for(int i = 0; i < m; i++)
        cout << i << " : " << table[i] << '\n';
}
*/

int main()
{
    //LINKED LIST
    int c, n, m;
    list l;
    do
    {
        cin >> c;
        switch (c)
        {
            case 1:
                cin >> n;
                if(!l.search(n))
                    cout << "NO\n";
                else
                    cout << "YES\n";
                break;
            case 2:
                cin >> n;
                l.insert_at_front(n);
                break;
            case 3:
                cin >> n;
                l.insert_at_end(n);
                break;
            case 4:
                cin >> n;
                l.del(n);
                break;
            case 5:
                l.display();
                break;
            case 6:
                l.del_at_front();
                break;
            case 7:
                l.del_at_end();
                break;
            case 8:
                cin >> n >> m;
                l.search_and_insert(n, m);
                break;
        }

    }while(c);


    //HASHTABLE Both lp and chaining
    /*int c, m, n;
    cin >> m;
    hashtable_lp h(m);
    do
    {
        cin >> c;
        switch(c)
        {
            case 1 : cin >> n;
                h.insert(n);
                break;
            case 2 : cin >> n;
                h.search(n);
                break;
            case 3 : cin >> n;
                h.del(n);
                break;
            case 4 :
                h.display();
        }
    }while(c);*/

    //TREAPS
    /*treap t;
    int c, n;
    do
    {
        cin >> c;
        switch(c)
        {
            case 1: cin >> n;
                t.insert(n);
                break;
            case 2: cin >> n;
                t.search(n);
                break;
            case 3: cin >> n;
                t.remove(n);
                break;
        }
    } while (c);*/

    //DSU
    /*int n, c, k, l;
    cin >> n;
    dsu d(n);
    do
    {
        cin >> c;
        switch(c)
        {
            case 1: cin >> k;
                cout << d.find_set(k) << '\n';
                break;
            case 2: cin >> k >> l;
                if(d.is_same_set(k, l))
                    cout << "same set\n";
                else 
                    cout << "different set\n";
                break;
            case 3: cin >> k >> l;
                d.union_set(k, l);
        }
    } while (c);
    */
    
    return 0;
}