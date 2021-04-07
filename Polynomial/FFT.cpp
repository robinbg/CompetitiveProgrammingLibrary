/*
   Source:Huigeng Ye(jvruo.com)
   */
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring> 
#include<complex>//c++自带的复数库
#include<algorithm>
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
