#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
using namespace std;


//-------------------------------------------------------------------------------------------------------------------------------------
struct node
{
    int data;
    node * next;
    node(int d) : data{d}, next{nullptr}
    {}
};


//-------------------------------------------------------------------------------------------------------------------------------------
class queue
{
    private:
        node * rear, * front;
    public:
        queue();
        void enqueue(int);
        int dequeue();
        int get_front();
        int get_rear();
        int size();
};

queue::queue()
{
    front = nullptr;
    rear = nullptr;
}

void queue::enqueue(int d)
{
    node * temp = new node(d);
    if(!front && !rear)
        front = rear = temp;
    else
    {
        rear -> next = temp;
        rear = temp;
    }
}

int queue::dequeue()
{
    int d;
    node * temp;
    if(!front && !rear)
        ;
    else if(rear == front)
    {
        d = front -> data;
        temp = front;
        front = rear = nullptr;
        delete temp;
    }
    else
    {
        d = front -> data;
        temp = front;
        front = front -> next;
        delete temp;
    }
    return d;
}

int queue::get_front()
{
    return front -> data;
}

int queue::get_rear()
{
    return rear -> data;
}

int queue::size()
{
    node * temp = front;
    if(!front)
        return 0;
    int count = 1;
    while(temp != rear)
    {
        count++;
        temp = temp -> next;
    }
    return count;
}


//-------------------------------------------------------------------------------------------------------------------------------------
class priority_queue
{
    private:
        vector<pair<int, int>> edges; // shortest path weight and vertex number
        int parent(int i) {return (i - 1) / 2;}
        int left(int i) {return 2 * i + 1;}
        int right(int i) {return 2 * i + 2;}
        void min_heapify(int);
        void build_min_heap();
        void decrease_key(int, int);
    public:
        void insert(pair<int, int>);
        pair<int, int> extract_min();
        pair<int, int> get_min(){return edges[0];}
        bool empty(){return edges.size() == 0;}
};

void priority_queue::min_heapify(int i)
{
    int l = left(i), r = right(i);
    int smallest = i;
    if(l < edges.size() && edges[smallest].first > edges[l].first)
        smallest = l;
    if(r < edges.size() && edges[smallest].first > edges[r].first)
        smallest = r;
    if(smallest != i)
    {
        swap(edges[smallest], edges[i]);
        min_heapify(smallest);
    }
    
}

void priority_queue::build_min_heap()
{
    for(int i = edges.size() - 1; i >= 0; i--)
        min_heapify(i);
}

void priority_queue::decrease_key(int i, int key)
{
    edges[i].first = key;
    while(i >= 0 && edges[parent(i)].first > edges[i].first)
    {
        swap(edges[i], edges[parent(i)]);
        i = parent(i);
    }
}

pair<int, int> priority_queue::extract_min()
{
    swap(edges[0], edges[edges.size() - 1]);
    auto x = edges.back();
    edges.pop_back();
    min_heapify(0);
    return x;
}

void priority_queue::insert(pair<int, int> e)
{
    edges.push_back(make_pair(INT32_MAX, e.second));
    decrease_key(edges.size() - 1, e.first);
}


//-------------------------------------------------------------------------------------------------------------------------------------
class graph
{
    private:
        int V;
        vector<int> * adj;
    public:
        graph(int);
        void add_edge(int, int);
        void DFS(int);
        void BFS(int);
        void print_adj();
};

graph::graph(int n)
{
    V = n;
    adj =  new vector<int>[V];
}

void graph::add_edge(int v, int u)
{
    adj[v].push_back(u);
}

void graph::print_adj()
{
    for(int i = 0; i < V; i++)
    {
        cout << i << " : ";
        for(auto x = adj[i].begin(); x != adj[i].end(); x++)
            cout << *x <<  ' ';
        cout << '\n';
    }
}
void graph::DFS(int v)
{
    static vector<bool> visited(V, false);
    if(!visited[v])
    {
        visited[v] = true;
        cout << v << ' ';
        for(auto x = adj[v].begin(); x != adj[v].end(); x++)
            DFS(*x);
    }
}

void graph::BFS(int v)
{
    vector<bool> visited(V, false);
    queue q;
    q.enqueue(v);
    visited[v] = true;
    while(!q.size())
    {
        int a = q.get_front();
        cout << a << ' ';
        q.dequeue();
        for(auto x = adj[a].begin(); x != adj[a].end(); x++)
            if(!visited[*x])
            {
                visited[*x] = true;
                q.enqueue(*x);
            }
    }
    cout << '\n';
}


//-------------------------------------------------------------------------------------------------------------------------------------
class circular_queue
{
    private:
        node * rear, * front;
    public:
        circular_queue();
        void enqueue(int);
        int dequeue();
        int get_front();
        int get_rear();
        int size();
};

circular_queue::circular_queue()
{
    front = nullptr;
    rear = nullptr;
}

void circular_queue::enqueue(int d)
{
    node * temp = new node(d);
    if(!front && !rear)
    {
        front = rear = temp;
        rear -> next = front;
    }
    else
    {
        rear -> next = temp;
        temp -> next = front;
        rear = temp;
    }
}

int circular_queue::dequeue()
{
    int d;
    node * temp;
    if(!front && !rear)
        ;
    else if(front == rear)
    {
        d = front -> data;
        temp = front;
        front = rear = nullptr;
        delete temp;
    }
    else
    {
        d = front -> data;
        temp = front;
        front = front -> next;
        rear -> next = front;
        delete temp;
    }
    return d;
}

int circular_queue::get_front()
{
    return front -> data;
}

int circular_queue::get_rear()
{
    return rear -> data;
}

int circular_queue::size()
{
    node * temp = front;
    if(!front)
        return 0;
    int count = 1;
    while(temp != rear)
    {
        count++;
        temp = temp -> next;
    }
    return count;
}


//-------------------------------------------------------------------------------------------------------------------------------------
class dsu
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
    rank.assign(n, 1);
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
        if(rank[i_p] > rank[j_p])
        {
            rank[i_p] += rank[j_p];
            parent[j_p] = i_p;
        }
        else 
        {
            rank[j_p] += rank[i_p];
            parent[i_p] = j_p;
        }
    }
}


//-------------------------------------------------------------------------------------------------------------------------------------
class wgraph
{
    private:
        int V;
        vector<pair<int, int>> * adj;
    public:
        wgraph(int);
        void add_edge(int, int, int);
        void DFS(int);
        void BFS(int);
        void print_adj();
        void minimum_spanning_tree();
        void dijkstra_algorithm(int);
};

wgraph::wgraph(int n)
{
    V = n;
    adj =  new vector<pair<int, int>>[V];
}

void wgraph::add_edge(int v, int u, int w)
{
    adj[v].push_back(make_pair(u, w));
    adj[u].push_back(make_pair(v, w));
}

void wgraph::print_adj()
{
    for(int i = 0; i < V; i++)
    {
        cout << i << " : ";
        for(auto x = adj[i].begin(); x != adj[i].end(); x++)
            cout << x -> first <<  ':' << x -> second << ' ';
        cout << '\n';
    }
}
void wgraph::DFS(int v)
{
    static vector<bool> visited(V, false);
    if(!visited[v])
    {
        visited[v] = true;
        cout << v << ' ';
        for(auto x = adj[v].begin(); x != adj[v].end(); x++)
            DFS(x -> first);
    }
}

void wgraph::BFS(int v)
{
    vector<bool> visited(V, false);
    queue q;
    q.enqueue(v);
    visited[v] = true;
    while(!q.size())
    {
        int a = q.get_front();
        cout << a << ' ';
        q.dequeue();
        for(auto x = adj[a].begin(); x != adj[a].end(); x++)
            if(!visited[x -> first])
            {
                visited[x -> first] = true;
                q.enqueue(x -> first);
            }
    }
    cout << '\n';
}

void wgraph::minimum_spanning_tree()
{
    priority_queue pq;
    int src = 0, w = 0;
    vector<int> key(V, INT32_MAX);
    vector<int> parent(V, -1);
    vector<bool> in_MST(V, false);
    pq.insert(make_pair(0, src));
    key[src] = 0;

    while(!pq.empty())
    {
        int u = pq.get_min().second;
        pq.extract_min();
        if(in_MST[u]) continue;
        in_MST[u] = true;
        for(auto x : adj[u])
        {
            int v = x.first;
            int weight = x.second;
            if(in_MST[v] == false && key[v] > weight)
            {
                key[v] = weight;
                pq.insert(make_pair(key[v], v));
                parent[v] = u;
            }
        }
    }
    for(int i = 0; i < V; i++)  
        w += key[i];
    cout << "Weight : " << w << '\n';
}

void wgraph::dijkstra_algorithm(int x)
{
    vector<int> shortest(V, INT16_MAX);
    priority_queue pq;
    pq.insert(make_pair(0, x));
    shortest[x] = 0;
    while(!pq.empty())
    {
        int u = pq.get_min().second;
        pq.extract_min();
        for(auto x : adj[u])
        {
            int v = x.first;
            int w = x.second;
            if(shortest[v] > shortest[u] + w)
            {
                shortest[v] = shortest[u] + w;
                pq.insert(make_pair(shortest[v], v));
            }
        }
    }

}


//-------------------------------------------------------------------------------------------------------------------------------------
void minimum_spanning_tree(vector<pair<int, pair<int, int>>>& e, int n)
{
    int edges = 0, weight = 0;
    sort(e.begin(), e.end());
    wgraph g(n);
    dsu d(n);
    for(auto x : e)
    {
        if(!d.is_same_set(x.second.first, x.second.second))
        {
            edges++;
            weight += x.first;
            d.union_set(x.second.first, x.second.second);
            g.add_edge(x.second.first, x.second.second, x.first);
            if(edges == n - 1)
                break;
        }
    }
    cout << "Weight = " << weight << '\n';
    g.print_adj();
}


//-------------------------------------------------------------------------------------------------------------------------------------
void all_pair_shortest_path(vector<vector<long long>>& g, int n)
{
    for(int k = 0; k < n; k++)
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                if(g[i][j] > g[i][k] + g[k][j])
                    g[i][j] = g[i][k] + g[k][j];
    
}



int main()
{
    int n, m, u, v, w;
    cin >> n >> m;
    vector<vector<long long>> g;
    g.reserve(n);
    for(int i = 0; i < n; i++)
        g[i].assign(n, INT32_MAX);
    while(m--)
    {
        cin >> v >> u >> w;
        g[u][v] = w;
    }
    all_pair_shortest_path(g, n);
    return 0;
}