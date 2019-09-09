#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool lexicographical_sort(string a, string b)
{
    return ((a + b).compare(b + a) > 0);
}
int main()
{
    int t, q;
    string buff;
    vector<string> numbers;
    cin >> t;
    while(t--)
    {
        cin >> q;
        while(q--)
        {
            cin >> buff;
            numbers.push_back(buff);
        }
        sort(numbers.begin(), numbers.end(), lexicographical_sort);
        for(auto x : numbers)
            cout << x;
        cout << '\n';
        numbers.clear();
    }
    return 0;
}