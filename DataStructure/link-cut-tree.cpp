/*
  Source:hzwer NOI2014魔法森林
 */
int top,q[200005];
int n,m,ans=inf;
int mx[200005],val[200005];
int p[200005],fa[200005],c[200005][2];
bool rev[200005];
struct data{
    int u,v,a,b;       
}e[100005];
int find(int x)
{
    return x==p[x]?x:p[x]=find(p[x]);
}
bool operator<(data a,data b)
{
    return a.a<b.a;
}
bool isroot(int x)
{
     return c[fa[x]][0]!=x&&c[fa[x]][1]!=x;
}
void update(int x)
{
    int l=c[x][0],r=c[x][1];
    mx[x]=x;
    if(val[mx[l]]>val[mx[x]])mx[x]=mx[l];
    if(val[mx[r]]>val[mx[x]])mx[x]=mx[r];
}
void pushdown(int x)
{
     int l=c[x][0],r=c[x][1];
     if(rev[x])
     {
         rev[x]^=1;rev[l]^=1;rev[r]^=1;
         swap(c[x][0],c[x][1]);
     }
}
void rotate(int &x)
{
     int y=fa[x],z=fa[y],l,r;
     if(c[y][0]==x)l=0;else l=1;r=l^1;
     if(!isroot(y))
     {
         if(c[z][0]==y)c[z][0]=x;
         else c[z][1]=x;
     }
     fa[x]=z;fa[y]=x;fa[c[x][r]]=y;
     c[y][l]=c[x][r];c[x][r]=y;
     update(y);update(x);
}
void splay(int &x)
{
     top=0;q[++top]=x;
     for(int i=x;!isroot(i);i=fa[i])q[++top]=fa[i];
     while(top)pushdown(q[top--]);
     while(!isroot(x))
     {
         int y=fa[x],z=fa[y];
         if(!isroot(y))
         {
             if(c[y][0]==x^c[z][0]==y)rotate(x);
             else rotate(y);
         }
         rotate(x);
     }
}
void access(int x)
{
    for(int t=0;x;t=x,x=fa[x])
        splay(x),c[x][1]=t,update(x);
}
void makeroot(int x)
{
     access(x);splay(x);rev[x]^=1;
}
void link(int x,int y)
{
    makeroot(x);fa[x]=y;
}
void cut(int x,int y)
{
    makeroot(x);access(y);splay(y);
    c[y][0]=fa[x]=0;update(y);
}
int query(int x,int y)
{
    makeroot(x);access(y);splay(y);
    return mx[y]; 
}
