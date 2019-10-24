#include <iostream>
#include <vector>

using namespace std;

int n, m, count, max_count, c, max_color;
vector<vector<int>> visited;

bool is_visited(int i, int j)
{
    return visited[i][j];
}

void reset_matrix(int n, int m)
{
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            visited[i][j] = false;
}

bool is_valid(int i, int j, int color, vector<vector<int>>& grid)
{
    if(i >= 0 && j >= 0 && i < n && j < m && !is_visited(i, j) && grid[i][j] == color)
        return true;
    else 
        return false;
}

void depth_first_search(int i, int j, int color, vector<vector<int>>& grid)
{
    visited[i][j] = true;
    count++;
    vector<pair<int,int>> mvmt = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    for(auto itr = mvmt.begin(); itr != mvmt.end(); itr++)
    {
        if(is_valid(i + itr -> first, j + itr -> second, color, grid))
            depth_first_search(i + itr -> first, j + itr -> second, color, grid);
    }
}

int largest_contiguous_component(int n, int m, vector<vector<int>>& grid)
{
    reset_matrix(n, m);
    max_count = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            count = 0;
            if(!is_visited(i, j))
                depth_first_search(i, j, grid[i][j], grid);
            if(max_count < count)
            {
                max_count = count;
                max_color = grid[i][j];
            }
        }
    }
    return max_count;
}

int main()
{
    cin >> n >> m >> c;
    visited.reserve(n);
    for(int i = 0; i < n; i++)
        visited[i].reserve(m);
    vector<vector<int>> grid(n, vector<int>(m));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cin >> grid[i][j];
    
    cout << largest_contiguous_component(n, m, grid) << ' ' << max_color << '\n';
    return 0;
}