#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
long long R = 10e9 + 7;

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

class wgraph
{
    private:
        int V;
        vector<pair<int, int>> * adj;
    public:
        wgraph(int);
        void add_edge(int, int, int);
        void print_adj();
};

wgraph::wgraph(int n)
{
    V = n;
    adj =  new vector<pair<int, int>>[V];
}

void wgraph::add_edge(int v, int u, int w)
{
    adj[v].push_back(make_pair(u, w));
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

bool comp(pair<int, pair<int, int>> &a, pair<int, pair<int, int>> &b)
{
    return (a.first > b.first);
}

void minimum_spanning_tree(vector<pair<int, pair<int, int>>>& e, int n)
{
    long long edges = 0, weight = 1;
    sort(e.begin(), e.end(), comp);
    wgraph g(n);
    dsu d(n);
    for(auto x : e)
    {
        if(!d.is_same_set(x.second.first, x.second.second))
        {
            edges++;
            weight = (weight * x.first) % R;
            d.union_set(x.second.first, x.second.second);
            g.add_edge(x.second.first, x.second.second, x.first);
            if(edges == n - 1)
                break;
        }
    }
    cout << weight << '\n';
    //g.print_adj();
}

int main()
{
    int n, m, u, v, w;
    cin >> n >> m;
    vector<pair<int, pair<int, int>>> e;
    while(m--)
    {
        cin >> u >> v >> w;
        e.push_back(make_pair(w, make_pair(u, v)));
    }
    minimum_spanning_tree(e, n);

    
}