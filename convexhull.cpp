#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <stdio.h>
using namespace std;

float area(pair<int,int> a,pair<int,int> b,pair<int,int> c);
int direction(pair<int,int> a,pair<int,int> b,pair<int,int> c);
void QuickHull(pair<int,int> a,pair<int,int> b,vector<pair<int,int> >list);
float distance(pair<int,int> a,pair<int,int> b,pair<int,int> c);

vector<pair<int,int> >answer;

bool comp(pair<int,int> a,pair<int,int> b)
{
	int x1=answer[0].first;
	int y1=answer[0].second;
	int x2=a.first;
	int y2=a.second;
	int x3=b.first;
	int y3=b.second;
	return (y2-y1)*(x3-x1)>(x2-x1)*(y3-y1);
}

float distance(pair<int,int> a,pair<int,int> b,pair<int,int> c)
{
	int x1,y1,x2,y2;
	x1=a.first;
	y1=a.second;
	x2=b.first;
	y2=b.second;
	float ar=area(a,b,c);
	ar=ar>0?ar:-ar;
	float dist=(2.0*ar)/sqrt(pow(x2-x1,2)+pow(y2-y1,2));
	return dist;
}

int direction(pair<int,int> a,pair<int,int> b,pair<int,int> c)
{
	float ar=area(a,b,c);
	if(ar>0)
	{
		return -1;			//anti-clockwise that is right side of a line;
	}
	else
	{
		return 1;			//clockwise that is left side of line
	}
}

float area(pair<int,int> a,pair<int,int> b,pair<int,int> c)
{
	float x1,y1,x2,y2,x3,y3;
	x1=a.first;
	y1=a.second;
	x2=b.first;
	y2=b.second;
	x3=c.first;
	y3=c.second;
	float area=x1*(y2-y3)-y1*(x2-x3)+x2*y3-y2*x3;
	return area/2.0;
}

void QuickHull(pair<int,int> a,pair<int,int> b,vector<pair<int,int> >list)
{
	vector<pair<int,int> >temp;
	for (int i = 0; i < list.size(); ++i)			//remember to  add 1st element and last elementas the currect point
	{
		if(direction(a,b,list[i])==-1)
		{
			temp.push_back(list[i]);
		}
	}
	//cout<<a.first<<" "<<a.second<<" "<<b.first<<" "<<b.second<<" "<<temp.size()<<endl;
	if(temp.size()==0)					//termination of function
	{
		return;
	}
	float current_distance=0,maximum_distance=0;
	int maximum_index=0;
	for (int i = 0; i < temp.size(); ++i)
	{
		current_distance=distance(a,b,temp[i]);
		if(current_distance>maximum_distance)
		{
			maximum_distance=current_distance;
			maximum_index=i;
		}
	}
	answer.push_back(temp[maximum_index]);
	QuickHull(a,temp[maximum_index],temp);
	QuickHull(temp[maximum_index],b,temp);
}
int main()
{
	//cout<<direction( make_pair(2,9),make_pair(8,0),make_pair(5,6))<<endl;
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n=8;
	//cin >>n;
	vector <pair<int,int> > a(n);
	for (int i = 0; i < n; ++i)
	{
		int x,y;
		cin>>x>>y;
		a[i]=make_pair(x,y);
	}
	sort(a.begin(),a.end());
	answer.push_back(a[0]);
	answer.push_back(a[n-1]);

	vector<pair<int,int> >b;
	b.assign(a.begin()++,a.end()--);

	QuickHull(a[0],a[n-1],b);
	QuickHull(a[n-1],a[0],b);

	sort(answer.begin()++,answer.end(),comp);
	for (int i = 0; i < answer.size(); ++i)
	{
		cout<<answer[i].first<<" "<<answer[i].second<<endl;
	}
	cout<<answer[0].first<<" "<<answer[0].second;
}
