#include<iostream>
#include<vector>

using namespace std;

void subtract(string, string);

int main()
{
	int q;
	cin >> q;
	while(q > 0)
	{
		string a, b;
		int flag = 1, flag_2 = 0;
		//cout << "Enter positive number 1:\n";
		cin >> a;
		//cout << "Enter positive number 2:\n";
		cin >> b;
		int i;
		for(i = 0; i < a.size(); i++)
		{
			if(a[i] != '0')
			{
				flag_2 = 1;
				break;
			}
		}
		if(flag_2)
			a = a.substr(i);
		else
			a = "0";
		flag_2 = 0;
		
		for(i = 0; i < b.size(); i++)
		{
			if(b[i] != '0')
			{
				flag_2 = 1;
				break;
			}
		}
		if(flag_2)
			b = b.substr(i);
		else
			b = "0";
		int l_a = a.size(), l_b = b.size();
		if(l_a < l_b)
		{
			a.swap(b);
			flag = 0;
		}
		else
		{
			if(l_a == l_b)
			{
				if(a.compare(b) < 0)
				{
					a.swap(b);
					flag = 0;
				}
			}
		}
		if(!flag)
		{
			cout << '-';
		}
		subtract(a, b);
		q--;
	}
	return 0;
}

void subtract(string a, string b)
{
	vector<int> c(max(a.size(), b.size()));
	int l_a = a.size(), l_b = b.size();
	int i = a.size() - 1, j = b.size() - 1, k = 0;
	int carry = 0, digit;
	int flag = 0;
	while(i >= 0 && j >= 0)
	{
		digit = a[i] - b[j] - carry;
		if(digit < 0)
		{
			digit += 10;
			carry = 1;
		}
		else
		{
			carry = 0;
		}
		c[k++] = digit;
		i--;
		j--;
	}
	while(i >= 0)
	{
		digit = a[i] - '0' - carry;
		if(digit < 0)
		{
			digit += 10;
			carry = 1;
		}
		else
		{
			carry = 0;
		}
		c[k++] = digit;
		i--;
	}
	/*digit = a[i] - '0' - carry;
	c[k++] = digit;*/
	for(i = 0; i < k; i++)
	{
		if(c[i])
			flag = 1;
	}
	if(flag)
	{
		i = k-1;
		while(!c[i])
			i--;
		for(; i >= 0; i--)
			cout << c[i];
		cout << '\n';
	}
	else
	{
		cout << "0\n";
	}
	

}

