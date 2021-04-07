/*
  Source：https://www.cnblogs.com/Mychael/p/8782679.html
 */ 
  
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define LL long long int
#define Redge(u) for (int k = h[u],to; k; k = ed[k].nxt)
#define REP(i,n) for (int i = 1; i <= (n); i++)
#define BUG(s,n) for (int i = 1; i <= (n); i++) cout<<s[i]<<' '; puts("");
using namespace std;
const int maxn = 4000005,maxm = 100005,INF = 1000000000;
inline int read(){
	int out = 0,flag = 1; char c = getchar();
	while (c < 48 || c > 57){if (c == '-') flag = -1; c = getchar();}
	while (c >= 48 && c <= 57){out = (out << 3) + (out << 1) + c - 48; c = getchar();}
	return out * flag;
}
const int G = 3,P = (119 << 23) + 1;//P=998244353
int n,m,L,R[maxn];
int A[maxn],B[maxn];
int qpow(int a,int b){
	int ans = 1;
	for (; b; b >>= 1,a = 1ll * a * a % P)
		if (b & 1) ans = 1ll * ans * a % P;
	return ans;
}
void NTT(int* a,int f){
	for (int i = 0; i < n; i++) if (i < R[i]) swap(a[i],a[R[i]]);
	for (int i = 1; i < n; i <<= 1){
		int gn = qpow(G,(P - 1) / (i << 1));
		for (int j = 0; j < n; j += (i << 1)){
			int g = 1;
			for (int k = 0; k < i; k++,g = 1ll * g * gn % P){
				int x = a[j + k],y = 1ll * g * a[j + k + i] % P;
				a[j + k] = (x + y) % P; a[j + k + i] = (x - y + P) % P;
			}
		}
	}
	if (f == 1) return;
	int nv = qpow(n,P - 2); reverse(a + 1,a + n);
	for (int i = 0; i < n; i++) a[i] = 1ll * a[i] * nv % P;
}
int main(){
	n = read(); m = read();
	for (int i = 0; i <= n; i++) A[i] = read();
	for (int i = 0; i <= m; i++) B[i] = read();
	m = n + m; for (n = 1; n <= m; n <<= 1) L++;
	for (int i = 0; i < n; i++) R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));
	NTT(A,1); NTT(B,1);
	for (int i = 0; i < n; i++) A[i] = 1ll * A[i] * B[i] % P;
	NTT(A,-1);
	for (int i = 0; i <= m; i++) printf("%d ",A[i]);
	return 0;
}
/*
