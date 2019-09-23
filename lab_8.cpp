#include <iostream>
#include <cmath>

using namespace std;

int select(long long [], int, int , int);
int partition(long long [], int, int, int, int);
int pivot(long long [], int, int);
int median_of_5_elements(long long [], int, int);

int main()
{
    int test_cases, n, x, y;
    cin >> test_cases;
    while(test_cases--)
    {
        cin >> n;
        long long d[n];
        for(int i = 0; i < n; i++)
        {
            cin >> x >> y;
            d[i] = x * x + y * y;
        }
        int pos = select(d, 0, n - 1, floor((n - 1) / 2));
        cout << sqrt(d[pos]) << '\n';

    }
    return 0;
}

int select(long long d[], int l, int r, int pos)
{
    int median_of_medians_index;
    while(1)
    {
        if(l == r)
            return l;
        median_of_medians_index = pivot(d, l, r);
        median_of_medians_index = partition(d, l, r, median_of_medians_index, pos);
        if(pos == median_of_medians_index)
            return pos;
        else if(pos > median_of_medians_index)
        {
            l = median_of_medians_index + 1;
        }
        else
        {
            r = median_of_medians_index - 1;
        }
    }   
}

int partition(long long d[], int l, int r, int median_of_medians_index, int pos)
{
    int pivot_value = d[median_of_medians_index];
    swap(d[median_of_medians_index], d[r]);
    int i = l - 1;
    for(int j = l; j < r; j++)
    {
        if(d[j] <= pivot_value)
        {
            i++;
            swap(d[i], d[j]);
        }
    }
    swap(d[i+1], d[r]);
    return i+1;
    
}

int pivot(long long d[], int l, int r)
{
    if(r - l < 5)
        return median_of_5_elements(d, l, r);
    int median_5, median_of_medians, sr;
    for(int i = l; i <= r; i += 5)
    {
        sr = i + 4;
        if(sr > r)
            sr = r;
        median_5 = median_of_5_elements(d, i, sr);
        swap(d[median_5], d[l + (int)floor((i - l) / 5)]);
    }
    median_of_medians = (r - l) / 10 + l + 1;
    return select(d, l, l + floor((r - l) / 5), median_of_medians);
}

int median_of_5_elements(long long d[], int l, int r)
{
    for(int i = l + 1; i <= r; i++)
    {
        int temp = d[i];
        int j = i - 1;
        while(j >= l && d[j] > temp)
        {
            d[j+1] = d[j];
            j--;
        }
        d[j+1] = temp;
    }
    return floor((l + r) / 2);
}

