#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    cin >> n;
    set<string> s;
    string temp, rtemp;
    bool flag = false;
    while(n--)
    {
        cin >> temp;
        rtemp = temp;
        if(!flag)
        {
            reverse(rtemp.begin(), rtemp.end());
            if(temp.compare(rtemp))
            {
                if(s.find(rtemp) != s.end())
                    flag = 1;
                s.insert(temp);
            }
        }
    }
    if(flag)
        cout << "YES\n";
    else
        cout << "NO\n";
    return 0;
}