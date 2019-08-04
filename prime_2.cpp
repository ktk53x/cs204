#include <iostream>
#include <math.h>
 
using namespace std; 

bool isPrime(long long n)
{
	if(n <= 1)
		return false;
	for(int i = 2; i <= sqrt(n); i++)
		if(n % i == 0)
			return false;
	return true;
}

int main()
{
	int q;
	long long p;
	cin >> q;
	while(q > 0)
	{
		cin >> p;
		if(isPrime(p))
		{
			cout << "Prime\n";
		}
		else
		{
			cout << "Not a Prime\n";
		}
		q--;
	}
	return 0;
}
