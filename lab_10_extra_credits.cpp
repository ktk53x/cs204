#include <iostream>
#include <vector>

using namespace std;

int n, m, count, max_count, c, max_color;
vector<vector<int>> visited;

bool is_visited(int i, int j)
{
    return visited[i][j];
}

void reset_matrix(int m, int n)
{
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            visited[i][j] = 0;
}

bool is_valid(int i, int j, int color, vector<vector<int>>& grid)
{
    if(i >= 0 && j >= 0 && i < m && j < n && !is_visited(i, j) && grid[i][j] == color)
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

int largest_contiguous_component(int m, int n, vector<vector<int>>& grid)
{
    reset_matrix(m, n);
    max_count = 0;
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
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
    cin >> m >> n >> c;
    visited.reserve(m);
    for(int i = 0; i < m; i++)
        visited[i].reserve(n);
    vector<vector<int>> grid(m, vector<int>(n));
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            cin >> grid[i][j];
    
    cout << largest_contiguous_component(m, n, grid) << ' ' << max_color << '\n';
    return 0;
}
