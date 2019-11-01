#include <iostream>
#include <list>
#include <queue>


using namespace std;

class graph
{
    private:
        int V;
        list<int> * adj;
        vector<int> color;
    public:
        graph(int v);
        void add_edge(int v, int u);
        bool is_bipartite();
        bool coloring(int i);
        vector<int>& get_color();
};

vector<int>& graph::get_color()
{
    return color;
}

graph::graph(int v)
{
    V = v;
    adj = new list<int>[v];
    color.resize(V);
    for(int i = 0; i < v; i++)
        color[i] = -1;
}

void graph::add_edge(int v, int u)
{
    adj[v].push_back(u);
    adj[u].push_back(v);
}

bool graph::is_bipartite()
{
    bool ans = true;
    for(int i = 0; i < V; i++)
        ans &= coloring(i);
    return ans;
}

bool graph::coloring(int i)
{
    if(color[i] == -1)
    {
        int s;
        queue<int> q;
        color[i] = 0;
        q.push(i);
        while(!q.empty())
        {
            s = q.front();
            q.pop();
            for(auto x = adj[s].begin(); x != adj[s].end(); x++)
            {
                if(color[*x] == color[s])
                    return false;
                if(color[*x] == -1)
                {
                    color[*x] = 1 - color[s];
                    q.push(*x);
                }
            }
        }
    }
    return true;
}

int main()
{
    int n, m, u, v, weight, k = 0;
    cin >> n >> m;
    int t = m + n;
    graph g(t);
    for(int i = 0; i < m; i++)
    {
        cin >> u >> v >> weight;
        if(weight % 2)
            g.add_edge(v, u);
        else 
        {
            g.add_edge(v, n+k);
            g.add_edge(n+k , u);
            k++;
        }
    }
    if(g.is_bipartite())
        cout << "NO\n";
    else 
        cout << "YES\n";

}
