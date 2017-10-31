#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

vector<vector<int>> matrix_add(vector<vector<int>> a, vector<vector<int>> b, int n)
{
	vector<vector<int>> c (n, vector<int> (n));
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<n;j++)
		{
			c[i][j]=a[i][j]+b[i][j];
		}
	}
	return c;
}

vector<vector<int>> matrix_sub(vector<vector<int>> a, vector<vector<int>> b, int n)
{
	vector<vector<int>> c (n, vector<int> (n));
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<n;j++)
		{
			c[i][j]=a[i][j]-b[i][j];
		}
	}
	return c;
}

vector<vector<int>> base_case(vector<vector<int>> a, vector<vector<int>> b, int n)
{
	vector<vector<int>> c (n, vector<int> (n));

  int m1= (a[0][0] + a[1][1])*(b[0][0]+b[1][1]);
  int m2= (a[1][0]+a[1][1])*b[0][0];
  int m3= a[0][0]*(b[0][1]-b[1][1]);
  int m4= a[1][1]*(b[1][0]-b[0][0]);
  int m5= (a[0][0]+a[0][1])*b[1][1];
  int m6= (a[1][0]-a[0][0])*(b[0][0]+b[0][1]);
  int m7= (a[0][1]-a[1][1])*(b[1][0]+b[1][1]);

  c[0][0]=m1+m4-m5+m7;
  c[0][1]=m3+m5;
  c[1][0]=m2+m4;
  c[1][1]=m1-m2+m3+m6;

  return c;
}

vector<vector<int>> Strassens(vector<vector<int>> a, vector<vector<int>> b, int n)
{
	if(n<=2)
	{
		vector<vector<int>> c=base_case(a,b,n);
		return c;
	}

	vector<vector<int>> a11(n/2, vector<int>(n/2,0));
	vector<vector<int>> a12(n/2, vector<int>(n/2,0));
	vector<vector<int>> a21(n/2, vector<int>(n/2,0));
	vector<vector<int>> a22(n/2, vector<int>(n/2,0));
	vector<vector<int>> b11(n/2, vector<int>(n/2,0));
	vector<vector<int>> b12(n/2, vector<int>(n/2,0));
	vector<vector<int>> b21(n/2, vector<int>(n/2,0));
	vector<vector<int>> b22(n/2, vector<int>(n/2,0));

	for(int i=0;i<n/2;i++)
	{
		for (int j=0;j<n/2;j++)
		{
			a11[i][j]=a[i][j];
			a12[i][j]=a[i][j+n/2];
			a21[i][j]=a[i+n/2][j];
			a22[i][j]=a[i+n/2][j+n/2];
			b11[i][j]=b[i][j];
			b12[i][j]=b[i][j+n/2];
			b21[i][j]=b[i+n/2][j];
			b22[i][j]=b[i+n/2][j+n/2];
		}
	}
	vector<vector<int>>p=Strassens(matrix_add(a11, a22, n/2), matrix_add(b11,b22, n/2), n/2);
	vector<vector<int>>q=Strassens(matrix_add(a21, a22, n/2), b11, n/2);
	vector<vector<int>>r=Strassens(a11, matrix_sub(b12, b22, n/2), n/2);
	vector<vector<int>>s=Strassens(a22, matrix_sub(b21, b11, n/2), n/2);
	vector<vector<int>>t=Strassens(matrix_add(a11, a12, n/2), b22, n/2);
	vector<vector<int>>u=Strassens(matrix_sub(a21, a11, n/2), matrix_add(b11, b12, n/2), n/2);
	vector<vector<int>>v=Strassens(matrix_sub(a12, a22, n/2), matrix_add(b21, b22, n/2), n/2);

	vector<vector<int>>c11=matrix_add(matrix_add(p, v, n/2), matrix_sub(s, t, n/2), n/2);
	vector<vector<int>>c12=matrix_add(r, t, n/2);
	vector<vector<int>>c21=matrix_add(q, s, n/2);
	vector<vector<int>>c22=matrix_add(matrix_add(p, u, n/2), matrix_sub(r, q, n/2), n/2);

	vector<vector<int>> c(n, vector<int>(n,0));
	for(int i=0;i<n/2;i++)
	{
		for(int j=0;j<n/2;j++)
		{
			c[i][j]=c11[i][j];
			c[i][j+n/2]=c12[i][j];
			c[i+n/2][j]=c21[i][j];
			c[i+n/2][j+n/2]=c22[i][j];
		}
	}
	return c;
}

int main (){
    int dim;
    cout<<"Enter Dimension:";
    cin>>dim;
    int n=pow(2, ceil(log2(dim)));
    vector<vector<int>>a(n, vector<int>(n,0));
    vector<vector<int>>b(n, vector<int>(n,0));
    cout<<"Enter values of matrices:";
    for(int i=0;i<dim;i++)
	{
		for(int j=0;j<dim;j++)
		{
		    cout<<"a["<<i<<"]["<<j<<"]\n";
			cin>>a[i][j];
		}
	}

	for(int i=0;i<n;i++)
	{
	    cout<<"\n";
		for(int j=0;j<n;j++)
		{
		    cout<<a[i][j];
		    cout<<"\t";
		}
	}

	for(int i=0;i<dim;i++)
	{
		for(int j=0;j<dim;j++)
		{
		    cout<<"b["<<i<<"]["<<j<<"]\n";
			cin>>b[i][j];
		}
	}

	for(int i=0;i<n;i++)
	{
	    cout<<"\n";
		for(int j=0;j<n;j++)
		{
			cout<<b[i][j];
			cout<<"\t";

		}
	}

	vector<vector<int>> c = Strassens(a,b,n);
	for(int i=0;i<dim;i++)
	{
	    cout<<"\n";
		for(int j=0;j<dim;j++)
		{
			cout<<c[i][j];
			cout<<"\t";
		}
	}


}
