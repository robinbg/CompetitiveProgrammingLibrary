/*
  Source:https://www.cnblogs.com/cjyyb/p/9065615.html
  */
void FWT_or(int *a,int opt)
{
    for(int i=1;i<N;i<<=1)
        for(int p=i<<1,j=0;j<N;j+=p)
            for(int k=0;k<i;++k)
                if(opt==1)a[i+j+k]=(a[j+k]+a[i+j+k])%MOD;
                else a[i+j+k]=(a[i+j+k]+MOD-a[j+k])%MOD;
}
void FWT_and(int *a,int opt)
{
    for(int i=1;i<N;i<<=1)
        for(int p=i<<1,j=0;j<N;j+=p)
            for(int k=0;k<i;++k)
                if(opt==1)a[j+k]=(a[j+k]+a[i+j+k])%MOD;
                else a[j+k]=(a[j+k]+MOD-a[i+j+k])%MOD;
}
void FWT_xor(int *a,int opt)
{
    for(int i=1;i<N;i<<=1)
        for(int p=i<<1,j=0;j<N;j+=p)
            for(int k=0;k<i;++k)
            {
                int X=a[j+k],Y=a[i+j+k];
                a[j+k]=(X+Y)%MOD;a[i+j+k]=(X+MOD-Y)%MOD;
                if(opt==-1)a[j+k]=1ll*a[j+k]*inv2%MOD,a[i+j+k]=1ll*a[i+j+k]*inv2%MOD;
            }
}
/*
   Source:https://www.cnblogs.com/flashhu/p/9732902.html
 */
#include<bits/stdc++.h>
#define LL long long
#define RG register
#define R RG int
#define G if(++ip==ie)fread(ip=buf,1,S,stdin)
#define For						\
	R i,j,k,d;					\
	for(i=2;i<=N;i<<=1)			\
		for(d=i>>1,j=0;j<N;j+=i)\
			for(k=j;k<j+d;++k)
using namespace std;
const LL I=499122177;
const int S=1<<17,YL=998244353;
char buf[S],*ie=buf+S,*ip=ie-1;
int N,a[S],b[S],p[S],q[S];
inline int in(){
	G;while(*ip<'-')G;
	R x=*ip&15;G;
	while(*ip>'-'){x*=10;x+=*ip&15;G;}
	return x;
}
void FWTo(R*a){For(a[k+d]+=   a[k])%=YL;}
void IWTo(R*a){For(a[k+d]+=YL-a[k])%=YL;}
void FWTa(R*a){For(a[k]+=   a[k+d])%=YL;}
void IWTa(R*a){For(a[k]+=YL-a[k+d])%=YL;}
void FWTx(R*a){For{R x=a[k+d];a[k+d]=(a[k]+YL-x)  %YL;a[k]=(a[k]+x)  %YL;}}
void IWTx(R*a){For{R x=a[k+d];a[k+d]=(a[k]+YL-x)*I%YL;a[k]=(a[k]+x)*I%YL;}}
void(*Fun[6])(R*)={FWTo,IWTo,FWTa,IWTa,FWTx,IWTx};
int main(){
	freopen("fwt.in","r",stdin);
	R n=in(),i,j;N=1<<n;
	for(i=0;i<N;++i)a[i]=in();
	for(i=0;i<N;++i)b[i]=in();
	for(j=0;j<6;j+=2){
		memcpy(p,a,N<<2);Fun[j](p);
		memcpy(q,b,N<<2);Fun[j](q);
		for(i=0;i<N;++i)p[i]=(LL)p[i]*q[i]%YL;
		Fun[j+1](p);
		for(i=0;i<N;++i)printf("%d ",p[i]);puts("");
	}
	return 0;
}
  
