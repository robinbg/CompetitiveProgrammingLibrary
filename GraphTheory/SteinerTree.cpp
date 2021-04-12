/*
给定连通图G中的n个点与k个关键点，连接k个关键点，使得生成树的所有边的权值和最小。

结合上面的知识我们可以知道直接连接这k个关键点生成的权值和不一定是最小的，或者这k个关键点不会直接（相邻）连接。所以应当使用剩下的n-k个点。
*/
#include <bits/stdc++.h>

using namespace std;

const int maxn = 510;
const int INF = 0x3f3f3f3f;
typedef pair<int, int> P;
int n, m, k;

struct edge {
  int to, next, w;
} e[maxn << 1];

int head[maxn << 1], tree[maxn << 1], tot;
int dp[maxn][5000], vis[maxn];
int key[maxn];
priority_queue<P, vector<P>, greater<P> > q;

void add(int u, int v, int w) {
  e[++tot] = edge{v, head[u], w};
  head[u] = tot;
}

void dijkstra(int s) {
  memset(vis, 0, sizeof(vis));
  while (!q.empty()) {
    P item = q.top();
    q.pop();
    if (vis[item.second]) continue;
    vis[item.second] = 1;
    for (int i = head[item.second]; i; i = e[i].next) {
      if (dp[tree[i]][s] > dp[item.second][s] + e[i].w) {
        dp[tree[i]][s] = dp[item.second][s] + e[i].w;
        q.push(P(dp[tree[i]][s], tree[i]));
      }
    }
  }
}

int main() {
  memset(dp, INF, sizeof(dp));
  scanf("%d %d %d", &n, &m, &k);
  int u, v, w;
  for (int i = 1; i <= m; i++) {
    scanf("%d %d %d", &u, &v, &w);
    add(u, v, w);
    tree[tot] = v;
    add(v, u, w);
    tree[tot] = u;
  }
  for (int i = 1; i <= k; i++) {
    scanf("%d", &key[i]);
    dp[key[i]][1 << (i - 1)] = 0;
  }
  for (int s = 1; s < (1 << k); s++) {
    for (int i = 1; i <= n; i++) {
      for (int subs = s & (s - 1); subs; subs = s & (subs - 1))
        dp[i][s] = min(dp[i][s], dp[i][subs] + dp[i][s ^ subs]);
      if (dp[i][s] != INF) q.push(P(dp[i][s], i));
    }
    dijkstra(s);
  }
  printf("%d\n", dp[key[1]][(1 << k) - 1]);
  return 0;
}
