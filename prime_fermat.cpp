#include <iostream>
#include <vector>

using namespace std;

string remainder(string, string);
string subtract(string, string);
string divide(string, string);
string multiply(string, string);
string power(string, string);

bool prime(string);

int main()
{
	int q;
	cin >> q;
	while(q > 0)
	{
		string a;
		int flag_2 = 0;
		//cout << "Enter Positive Number 1: ";
		cin >> a;
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
		if(prime(a))
			cout << "Prime\n";
		else
			cout << "Not a Prime\n";
		q--;
	}
	return 0;
}

bool prime(string a)
{
	if(remainder(subtract(power("2", a), "2"), a).compare("0"))
	{
		return false;
	}
	return true;
}

string remainder(string a, string b)
{
	int l_a = a.size(), l_b = b.size();
	vector<int> quotient(l_a + 1, 0);
	if(l_a < l_b)
	{
		return a;
	}
	else if(l_a == l_b && a.compare(b) < 0)
	{
		return a;
	}
	else if(l_a == l_b && a.compare(b) == 0)
	{
		return "0";
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
		if(a.empty())
			return "0";
		return a;
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

string multiply(string a, string b)
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
		string s = "";
		while(!result[i])
		{
			i--;	
		}
		for(; i >= 0; i--)
			s += (result[i] + '0');
		return s;
	}
	else
	{
		return "0";
	}
}

string divide(string a, string b)
{
	int l_a = a.size(), l_b = b.size();
	vector<int> quotient(l_a + 1, 0);
	if(l_a < l_b)
	{
		return "0";
	}
	else if(l_a == l_b && a.compare(b) < 0)
	{
		return "0";
	}
	else if(l_a == l_b && a.compare(b) == 0)
	{
		return "1";
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
			string s = "";
			while(!quotient[i])
				i--;
			for(;i >= 0; i--)
				s += (quotient[i] + '0');
			return s;
		}
		else
		{
			int i = l_a - 1;
			string s = "";
			while(!quotient[i])
				i--;
			for(;i >= 0; i--)
				s += (quotient[i] + '0');
			return s;
		}
	}	
	
}

string power(string a, string b)
{
	string prod = "1";
	string prodSeq = a;
	while(b.compare("0"))
	{
		if(!(remainder(b, a).compare("1")))
		{
			prod = multiply(prod, prodSeq);
		}
		b = divide(b, a);
		prodSeq = multiply(prodSeq, prodSeq);
	}
	return prod;
}

