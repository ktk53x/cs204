#include <iostream>
#include <vector>

using namespace std;

void multiply(string, string);

int main()
{
	int q;
	cin >> q;
	while(q > 0)
	{
		string a, b;
		//cout << "Enter positive number 1: ";
		cin >> a;
		//cout << "Enter positive number 2: ";
		cin >> b;
		if(a[0] == '-' && b[0] == '-')
		{
			a = a.substr(1);
			b = b.substr(1);
		}
		else if(a[0] == '-')
		{
			cout << '-';
			a = a.substr(1);
		}
		else if(b[0] == '-')
		{
			cout << '-';
			b = b.substr(1);
		}
		multiply(a, b);
		q--;
	}
	return 0;
}

void multiply(string a, string b)
{
	int flag = 0;
	int l_a = a.size(), l_b = b.size();
	int p_a = 0, p_b = 0;
	int carry = 0, product;
	vector<int> result(l_a + l_b, 0);
	for(int i = l_b - 1; i >= 0; i--)
	{
		for(int j = l_a - 1; j >= 0; j--)
		{
			product = (a[j] - '0') * (b[i] - '0') + result[p_a + p_b];
			result[p_a + p_b] = product % 10;
			carry = product / 10;
			//cout << product << ' ' << result[p_a + p_b] << '\n';
			p_a++;
			result[p_a + p_b] += carry;
			//cout << carry << ' ' << result[p_a + p_b] << '\n';
		}
		p_b++;
		p_a = 0;
	}
	for(int i = 0; i < l_a + l_b; i++)
	{
		if(result[i])
			flag = 1;
	}
	if(flag)
	{
		int i = l_a + l_b - 1;
		while(!result[i])
		{
			i--;	
		}
		for(; i >= 0; i--)
			cout << result[i];
		cout << '\n';
	}
	else
	{
		cout << "\b0\n";
	}
}
