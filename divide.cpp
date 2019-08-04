#include <iostream>
#include <vector>

using namespace std;

void divide(string, string);
string subtract(string, string);
int main()
{
	int q;
	cin >> q;
	while(q > 0)
	{
		string a, b;
		int flag_2 = 0;
		//cout << "Enter Positive Number 1: ";
		cin >> a;
		//cout << "Enter Positive Number 2: ";
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
		divide(a, b);
		q--;
	}
	return 0;
}

void divide(string a, string b)
{
	int l_a = a.size(), l_b = b.size();
	vector<int> quotient(l_a + 1, 0);
	if(l_a < l_b)
	{
		cout << 0 << '\n' << a << '\n';
	}
	else if(l_a == l_b && a.compare(b) < 0)
	{
		cout << 0 << '\n' << a << '\n';
	}
	else if(l_a == l_b && a.compare(b) == 0)
	{
		cout << 1 << '\n' << 0 << '\n';
	}
	else
	{
		while(1)
		{
			if(a.size() == 0)
			{
				break;
			}
			if(a.size() == b.size())
			{
				if(a.compare(b) < 0)
					break;
			}
			if(a.size() < b.size())
			{
				break;
			}
			string temp = b;
			if(a.compare(b) >= 0)
			{
				temp.append(a.size() - b.size(), '0');
				quotient[a.size() - b.size()]++;
				a = subtract(a, temp);
			}
			else
			{
				temp.append(a.size() - b.size() - 1, '0');
				quotient[a.size() - b.size() - 1]++;
				a = subtract(a, temp);
			}
			//cout << a << '\n';
			
		}
		for(int i = 0; i < l_a + 1; i++)
		{
			if(quotient[i] > 9)
			{
				quotient[i+1] += quotient[i] / 10;
				quotient[i] = quotient[i] % 10;
			}
		}
			
		if(a.size())
		{
			int i = l_a - 1;
			while(!quotient[i])
				i--;
			for(;i >= 0; i--)
				cout << quotient[i];
			cout << '\n';
			cout << a << '\n';
		}
		else
		{
			int i = l_a - 1;
			while(!quotient[i])
				i--;
			for(;i >= 0; i--)
				cout << quotient[i];
			cout << '\n';
			cout << 0 << '\n';
		}
	}	
	
}

string subtract(string a, string b)
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
	for(i = 0; i < k; i++)
	{
		if(c[i])
			flag = 1;
	}
	j = 0;
	string d = "";
	if(flag)
	{
		i = k-1;
		while(!c[i])
			i--;
		for(; i >= 0; i--)
		{
			d += (c[i] + '0');
		}
	}
	return d;

}
