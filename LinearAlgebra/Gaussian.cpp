/*Gaussian-Jordan */
#include<bits/stdc++.h>
#define re register
#define il inline
#define debug printf("Now is %d\n",__LINE__);
using namespace std;
#define maxn 105
#define D double
D a[maxn][maxn];
int n;
int main()
{
	scanf("%d",&n);
	for(re int i=1;i<=n;++i)
	{
		for(re int j=1;j<=n+1;++j)
		{
			scanf("%lf",&a[i][j]);
		}
	}
	for(re int i=1;i<=n;++i)//枚举列（项） 
	{
		re int max=i;
		for(re int j=i+1;j<=n;++j)//选出该列最大系数 
		{
			if(fabs(a[j][i])>fabs(a[max][i]))
            //fabs是取浮点数的绝对值的函数
			{
				max=j;
			}
		}
		for(re int j=1;j<=n+1;++j)//交换
		{
			swap(a[i][j],a[max][j]);
		}
		if(!a[i][i])//最大值等于0则说明该列都为0，肯定无解 
		{
			puts("No Solution");
			return 0;
		}
		for(re int j=1;j<=n;++j)//每一项都减去一个数（即加减消元）
		{
			if(j!=i)
			{
				re D temp=a[j][i]/a[i][i];
				for(re int k=i+1;k<=n+1;++k)
				{
					a[j][k]-=a[i][k]*temp;
                    //a[j][k]-=a[j][i]*a[i][k]/a[i][i];
				}
			}
		}
	}
    //上述操作结束后，矩阵会变成这样
    /*
    k1*a=e1
    k2*b=e2
    k3*c=e3
    k4*d=e4
    */
    //所以输出的结果要记得除以该项系数，消去常数
	for(re int i=1;i<=n;++i)
	{
		printf("%.2lf\n",a[i][n+1]/a[i][i]);
	}
	return 0;
}
//xor
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 110;

int n;
int a[N][N];

int gauss()
{
    int r, c;
    for(r = 0, c = 0; c < n; c ++) {
        int t = r;
        for(int i = r; i < n; i ++) {
            if(a[i][c]) {
                t = i;
                break;
            }
        }
        if(!a[t][c]) continue;
        for(int i = c; i < n + 1; i ++) swap(a[r][i], a[t][i]);
        for(int i = r + 1; i < n; i ++) {
            if(a[i][c]) {
                for(int j = n; j >= c; j --) {
                    a[i][j] ^= a[r][j];
                }
            }
        }
        r ++;
    }
    if(r < n) {
        for(int i = r; i < n; i ++) {
            if(a[i][n]) {
                return 2;
            }
        }
        return 1;
    }
    for(int i = n - 1; i >= 0; i --) {
        for(int j = i + 1; j < n; j ++) {
            a[i][n] ^= a[j][n] & a[i][j];
        }
    }
    return 0;
}

int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < n + 1; j ++) {
            scanf("%d", &a[i][j]);
        }
    }
    int t = gauss();
    if(!t) for(int i = 0; i < n; i ++) printf("%d\n", a[i][n]);
    else if(t == 1) puts("Multiple sets of solutions");
    else puts("No solution");
    return 0;
}
