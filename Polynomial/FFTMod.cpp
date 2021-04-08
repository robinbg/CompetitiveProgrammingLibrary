/*
     Source:matthew99(https://uoj.ac/submission/49836)
     */
#include <bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for (int i = (a), _end_ = (b); i < _end_; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mp make_pair
#define x first
#define y second
#define pb push_back
#define SZ(x) (int((x).size()))
#define ALL(x) (x).begin(), (x).end()

template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

typedef long long LL;

const int oo = 0x3f3f3f3f;

const int Mod = 1e9 + 7;

const int max0 = 262144;

struct comp
{
	double x, y;

	comp(): x(0), y(0) { }
	comp(const double &_x, const double &_y): x(_x), y(_y) { }

};

inline comp operator+(const comp &a, const comp &b) { return comp(a.x + b.x, a.y + b.y); }
inline comp operator-(const comp &a, const comp &b) { return comp(a.x - b.x, a.y - b.y); }
inline comp operator*(const comp &a, const comp &b) { return comp(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }
inline comp conj(const comp &a) { return comp(a.x, -a.y); }

const double PI = acos(-1);

int N, L;

comp w[max0 + 5];
int bitrev[max0 + 5];

void fft(comp *a, const int &n)
{
	REP(i, 0, n) if (i < bitrev[i]) swap(a[i], a[bitrev[i]]);
	for (int i = 2, lyc = n >> 1; i <= n; i <<= 1, lyc >>= 1)
		for (int j = 0; j < n; j += i)
		{
			comp *l = a + j, *r = a + j + (i >> 1), *p = w;
			REP(k, 0, i >> 1)
			{
				comp tmp = *r * *p;
				*r = *l - tmp, *l = *l + tmp;
				++l, ++r, p += lyc;
			}
		}
}

inline void fft_prepare()
{
	REP(i, 0, N) bitrev[i] = bitrev[i >> 1] >> 1 | ((i & 1) << (L - 1));
	REP(i, 0, N) w[i] = comp(cos(2 * PI * i / N), sin(2 * PI * i / N));
}

inline void conv(int *x, int *y, int *z)
{
	REP(i, 0, N) (x[i] += Mod) %= Mod, (y[i] += Mod) %= Mod;
	static comp a[max0 + 5], b[max0 + 5];
	static comp dfta[max0 + 5], dftb[max0 + 5], dftc[max0 + 5], dftd[max0 + 5];

	REP(i, 0, N) a[i] = comp(x[i] & 32767, x[i] >> 15);
	REP(i, 0, N) b[i] = comp(y[i] & 32767, y[i] >> 15);
	fft(a, N), fft(b, N);
	REP(i, 0, N)
	{
		int j = (N - i) & (N - 1);
		static comp da, db, dc, dd;
		da = (a[i] + conj(a[j])) * comp(0.5, 0);
		db = (a[i] - conj(a[j])) * comp(0, -0.5);
		dc = (b[i] + conj(b[j])) * comp(0.5, 0);
		dd = (b[i] - conj(b[j])) * comp(0, -0.5);
		dfta[j] = da * dc;
		dftb[j] = da * dd;
		dftc[j] = db * dc;
		dftd[j] = db * dd;
	}
	REP(i, 0, N) a[i] = dfta[i] + dftb[i] * comp(0, 1);
	REP(i, 0, N) b[i] = dftc[i] + dftd[i] * comp(0, 1);
	fft(a, N), fft(b, N);
	REP(i, 0, N)
	{
		int da = (LL)(a[i].x / N + 0.5) % Mod;
		int db = (LL)(a[i].y / N + 0.5) % Mod;
		int dc = (LL)(b[i].x / N + 0.5) % Mod;
		int dd = (LL)(b[i].y / N + 0.5) % Mod;
		z[i] = (da + ((LL)(db + dc) << 15) + ((LL)dd << 30)) % Mod;
	}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int n, m;
	static int a[max0 + 5], b[max0 + 5], c[max0 + 5];
	scanf("%d%d", &n, &m), ++n, ++m;
	REP(i, 0, n) scanf("%d", a + i);
	REP(i, 0, m) scanf("%d", b + i);
	L = 0;
	for ( ; (1 << L) < n + m - 1; ++L);
	N = 1 << L;
	fft_prepare();
	conv(a, b, c);
	REP(i, 0, n + m - 1) (c[i] += Mod) %= Mod, printf("%d ", c[i]);
	printf("\n");
	return 0;
}
