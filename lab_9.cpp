#include<bits/stdc++.h>
#define lli long long int
using namespace std;
struct Point 
{
	lli x;
	lli y;

};

int orientation(Point a, Point b, Point c)
{
	lli val=(b.x-a.x)*(c.y-a.y)-(c.x-a.x)*(b.y-a.y);
	if(val==0)
	{
		return 0;  
	}
	if(val<0)
	{
		return 1;
	}
	if(val>0)
	{
		return -1;
	}
}
//returns minimum and places the point with least y-coordinate in the beginning
Point minY(Point * arr, int n)
{
	Point ans;
	ans=arr[0];
	int minindex=0;
	for(int i=1;i<n;i++)
	{
		if(arr[i].y<ans.y)
		{
			ans=arr[i];
			minindex=i;
			continue;
		}

		if(arr[i].y==ans.y)
		{
			if(arr[i].x<ans.x)
			{
				ans=arr[i];
				minindex=i;
				continue;
			}
		}
	}
	Point temp;
	temp=arr[0];
	arr[0]=ans;
	arr[minindex]=temp;

	return ans;
}
//Watch out overflow if the points are too far away
lli squaredistance(Point a,Point b)
{
	return (b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y);
}
Point p0;

bool compare(Point a,Point b)
{
	lli val=orientation(p0,a,b);
	if(val==0)
	{
		if(squaredistance(p0,a)<squaredistance(p0,b))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	if(val==1)
	{
		return false;
	}
	else
	{
		return true;
	}

}

void graham_scan(Point *arr,int n)
{


	if(n<=2)
	{
		cout<<-1;
		return;
	}
	p0=minY(arr,n);
	sort(arr+1,arr+n,compare);

	int nfinal=n;
	int j=1;
	for(int i=1;i<n;i++)
	{
		while(i<n-1&&orientation(p0,arr[i],arr[i+1])==0)
		{
			nfinal--;
			i++;
		}
		arr[j]=arr[i];
		j++;
	}

	
	if(nfinal==2)
	{
		cout<<2<<endl;
		if(arr[0].x<arr[1].x)
		{
		cout<<arr[0].x<<" "<<arr[0].y<<endl;
		cout<<arr[1].x<<" "<<arr[1].y<<endl;
		return;
		}
		else
		{
		cout<<arr[1].x<<" "<<arr[1].y<<endl;
		cout<<arr[0].x<<" "<<arr[0].y<<endl;
		return;
		}
		
	}

vector<Point>convex_hull;
convex_hull.push_back(arr[0]);
convex_hull.push_back(arr[1]);
convex_hull.push_back(arr[2]);

for(int i=3;i<nfinal;i++)
{
	
	while(orientation(convex_hull[convex_hull.size()-2],convex_hull[convex_hull.size()-1],arr[i])!=-1)
	{
		convex_hull.pop_back();
	}
	convex_hull.push_back(arr[i]);
	
}

//Printing convex hull, fix if same points are added twice
cout<<convex_hull.size()<<endl;
int mini=0;
for(int i=0;i<convex_hull.size();i++)
{
	if(convex_hull[i].x<convex_hull[mini].x)
	{
		mini=i;
	}

}
for(int j=0;j<convex_hull.size();j++)
{
	int ind=((mini-j)+convex_hull.size())%convex_hull.size();
	cout<<convex_hull[ind].x<<" "<<convex_hull[ind].y<<endl;
}

}


int main()
{
int n;
cin>>n;

Point a[n];

for(int i=0;i<n;i++)
{
	cin>>a[i].x>>a[i].y;
}


graham_scan(a,n);

return 0;
}
