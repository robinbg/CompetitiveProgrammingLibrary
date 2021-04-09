/*
   Source:Huigeng Ye(jvruo.com)
   */
#include<complex>//c++自带的复数库
using namespace std;
double pi=acos(-1);

complex<double> a[410000],b[410000],c[410000];
int i,j,k,m,n,o,p,js,jl;

void fft(complex<double> *a,int n,int op)
{
    if(n==1)return; 
    complex<double> w(1,0),wn(cos(2*pi/n),sin(2*pi*op/n)),a1[n/2],a2[n/2];

    for(int i=0;i<n/2;i++)
    {
        a1[i]=a[2*i];
        a2[i]=a[2*i+1];
    }
    fft(a1,n/2,op);
    fft(a2,n/2,op);

    for(int i=0;i<n/2;i++)
    {
        a[i]=a1[i]+w*a2[i];
        a[i+n/2]=a1[i]-w*a2[i];
        w=w*wn;
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<=n;i++)scanf("%lf",&a[i]);
    for(int i=0;i<=m;i++)scanf("%lf",&b[i]);
    m=m+n;n=1;
    while(n<=m)n=n*2;

    fft(a,n,1);fft(b,n,1);
    for(int i=0;i<=n;i++)c[i]=a[i]*b[i];
    fft(c,n,-1);
    for(int i=0;i<=m;i++)printf("%d ",int(c[i].real()/n+0.5));
    return 0;
}
/*高精乘*/

int main()
{
	ios::sync_with_stdio(false);
	string x,y;
	while(cin>>x>>y)
	{
		int n=x.length(), m = y.length();
		memset(a,0,sizeof a);
		memset(b,0,sizeof b);
		for(int i=1;i<=n;i++) a[n-i] = double(x[i-1]-'0');
		for(int j=1;j<=m;j++) b[m-j] = double(y[j-1]-'0');
		memset(c,0,sizeof c);
		m+=n;
		n=1;
		while(n<=m)n<<=1;
		fft(a,n,1);
		fft(b,n,1);
		for(int i=0;i<=n;i++)c[i]=a[i]*b[i];
		fft(c,n,-1);
		memset(ans,0,sizeof(ans));
		for(int i=0;i<=m;i++)ans[i]=int(c[i].real()/n+0.5);
		for(int i=1;i<=m;i++)
		{
			ans[i]+=ans[i-1]/10;
			ans[i-1]%=10;
		}
		int i=m;
      
		while(!ans[i] && i>=0)i--;
		if(i<0)cout<<0;
		for(;i>=0;i--)cout<<ans[i];
	
		cout<<endl;
   } 
}
/*非递归*/
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
const int MAXN=1e7+10;
inline int read()
{
    char c=getchar();int x=0,f=1;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
const double Pi=acos(-1.0);
struct complex
{
    double x,y;
    complex (double xx=0,double yy=0){x=xx,y=yy;}
}a[MAXN],b[MAXN];
complex operator + (complex a,complex b){ return complex(a.x+b.x , a.y+b.y);}
complex operator - (complex a,complex b){ return complex(a.x-b.x , a.y-b.y);}
complex operator * (complex a,complex b){ return complex(a.x*b.x-a.y*b.y , a.x*b.y+a.y*b.x);}//不懂的看复数的运算那部分 
int N,M;
int l,r[MAXN];
int limit=1;
void fast_fast_tle(complex *A,int type)
{
    for(int i=0;i<limit;i++) 
        if(i<r[i]) swap(A[i],A[r[i]]);//求出要迭代的序列 
    for(int mid=1;mid<limit;mid<<=1)//待合并区间的中点
    {
        complex Wn( cos(Pi/mid) , type*sin(Pi/mid) ); //单位根 
        for(int R=mid<<1,j=0;j<limit;j+=R)//R是区间的右端点，j表示前已经到哪个位置了 
        {
            complex w(1,0);//幂 
            for(int k=0;k<mid;k++,w=w*Wn)//枚举左半部分 
            {
                 complex x=A[j+k],y=w*A[j+mid+k];//蝴蝶效应 
                A[j+k]=x+y;
                A[j+mid+k]=x-y;
            }
        }
    }
}
int main()
{
    int N=read(),M=read();
    for(int i=0;i<=N;i++) a[i].x=read();
    for(int i=0;i<=M;i++) b[i].x=read();
    while(limit<=N+M) limit<<=1,l++;
    for(int i=0;i<limit;i++)
        r[i]= ( r[i>>1]>>1 )| ( (i&1)<<(l-1) ) ;
    // 在原序列中 i 与 i/2 的关系是 ： i可以看做是i/2的二进制上的每一位左移一位得来
    // 那么在反转后的数组中就需要右移一位，同时特殊处理一下复数 
    fast_fast_tle(a,1);
    fast_fast_tle(b,1);
    for(int i=0;i<=limit;i++) a[i]=a[i]*b[i];
    fast_fast_tle(a,-1);
    for(int i=0;i<=N+M;i++)
        printf("%d ",(int)(a[i].x/limit+0.5));
    return 0;
}
