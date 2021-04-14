#include <bits/stdc++.h>
using namespace std;

const int maxn = 1 << 20, mod = 998244353;

int a[maxn], b[maxn], g[maxn], gg[maxn];

int qpow(int x, int y) {
  int ans = 1;

  while (y) {
    if (y & 1) {
      ans = 1LL * ans * x % mod;
    }
    x = 1LL * x * x % mod;
    y >>= 1;
  }
  return ans;
}

int inv2 = qpow(2, mod - 2);

inline void change(int *f, int len) {
  for (int i = 1, j = len >> 1; i < len - 1; i++) {
    if (i < j) {
      swap(f[i], f[j]);
    }

    int k = len >> 1;
    while (j >= k) {
      j -= k;
      k >>= 1;
    }
    if (j < k) {
      j += k;
    }
  }
}

inline void NTT(int *f, int len, int type) {
  change(f, len);

  for (int q = 2; q <= len; q <<= 1) {
    int nxt = qpow(3, (mod - 1) / q);
    for (int i = 0; i < len; i += q) {
      int w = 1;

      for (int k = i; k < i + (q >> 1); k++) {
        int x = f[k];
        int y = 1LL * w * f[k + (q >> 1)] % mod;

        f[k] = (x + y) % mod;
        f[k + (q >> 1)] = (x - y + mod) % mod;
        w = 1LL * w * nxt % mod;
      }
    }
  }

  if (type == -1) {
    reverse(f + 1, f + len);
    int iv = qpow(len, mod - 2);

    for (int i = 0; i < len; i++) {
      f[i] = 1LL * f[i] * iv % mod;
    }
  }
}

inline void inv(int deg, int *f, int *h) {
  if (deg == 1) {
    h[0] = qpow(f[0], mod - 2);
    return;
  }

  inv(deg + 1 >> 1, f, h);

  int len = 1;
  while (len < deg << 1) {
    len <<= 1;
  }

  copy(f, f + deg, gg);
  fill(gg + deg, gg + len, 0);

  NTT(gg, len, 1);
  NTT(h, len, 1);
  for (int i = 0; i < len; i++) {
    h[i] = 1LL * (2 - 1LL * gg[i] * h[i] % mod + mod) % mod * h[i] % mod;
  }

  NTT(h, len, -1);
  fill(h + deg, h + len, 0);
}

int n, t[maxn];

inline void sqrt(int deg, int *f, int *h) {
  if (deg == 1) {
    h[0] = 1;
    return;
  }

  sqrt(deg + 1 >> 1, f, h);

  int len = 1;
  while (len < deg << 1) {
    len <<= 1;
  }
  fill(g, g + len, 0);
  inv(deg, h, g);
  copy(f, f + deg, t);
  fill(t + deg, t + len, 0);
  NTT(t, len, 1);
  NTT(g, len, 1);
  NTT(h, len, 1);

  for (int i = 0; i < len; i++) {
    h[i] = 1LL * inv2 * (1LL * h[i] % mod + 1LL * g[i] * t[i] % mod) % mod;
  }
  NTT(h, len, -1);
  fill(h + deg, h + len, 0);
}

int main() {
  cin >> n;

  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  sqrt(n, a, b);

  for (int i = 0; i < n; i++) {
    printf("%d ", b[i]);
  }

  return 0;
}
