	int value[1001], ch[1001][2], fa[1001], sz[1001], tag[1001];
	int root;

inline bool isright(int x)
	{
		return x == ch[fa[x]][1];
	}
	inline void rev(int x)
	{
		swap(ch[x][0],ch[x][1]);
	}
	inline void pushdown(int x)
	{
		if(x && tag[x])
		{
			if(ch[x][0]) rev(ch[x][0]), tag[ch[x][0]] ^= 1;
			if(ch[x][1]) rev(ch[x][1]), tag[ch[x][1]] ^= 1;
			tag[x] = 0;
		}
	}
	inline void maintain(int x)
	{
		sz[x] = 1 + sz[ch[x][0]] + sz[ch[x][1]];
	}
	inline void rotate(int x)
	{
		
		register int y = fa[x], z = fa[y], chk = isright(x);
		
		ch[y][chk] = ch[x][chk^1];
		if(ch[x][chk^1])fa[ch[x][chk^1]] = y;
		ch[x][chk^1] = y;
		if(z)ch[z][isright(y)] = x;
		
		fa[y] = x;
		fa[x] = z;
		maintain(y);
		maintain(x);
	}
	void splay(int x, int s=0)
	{
		for(int y;(y=fa[x])!=s;rotate(x))
			if(fa[y]!=s)rotate((isright(x)==isright(y))?y:x);
		if(!s)root_ = x;
	}
