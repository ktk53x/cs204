#include<iostream>
#include<vector>

using namespace std;

void add(string, string);

int main()
{
	int q;
	cin >> q;
	while(q > 0)
	{
		string a, b;
		//cout << "Enter positive number 1:\n";
		cin >> a;
		//cout << "Enter positive number 2:\n";
		cin >> b;
		add(a, b);
		q--;
	}
	return 0;
}

void add(string a, string b)
{
	int l_a = a.size(), l_b = b.size();
	vector<int> c(max(l_a + 1, l_b + 1), 0);
	int i = l_a - 1, j = l_b - 1, k = 0;
	int carry = 0, digit;
	int flag = 0;
	while(i >= 0 && j >= 0)
	{
		digit = (a[i] - '0') + (b[j] - '0') + carry;
		c[k++] = digit % 10;
		carry = digit / 10;
		i--;
		j--;
	}

	while(i >= 0)
	{
		digit = (a[i] - '0') + carry;
		c[k++] = digit % 10;
		carry = digit / 10;
		i--;
	}

	while(j >= 0)
	{
		digit = (b[j] - '0') + carry;
		c[k++] = digit % 10;
		carry = digit / 10;
		j--;
	}
	
	if(carry)
	{
		c[k++] = carry;
	}
	
	for(int i = 0; i < k; i++)
	{
		if(c[i])
			flag = 1;
	}
	
	if(flag)
	{
		int i = k - 1;
		while(!c[i])
		{
			i--;	
		}
		for(; i >= 0; i--)
			cout << c[i];
		cout << '\n';
	}
	else
	{
		cout << "0\n";
	}
}
