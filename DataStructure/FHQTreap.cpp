#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
struct node
{
    int c,d,key,son[2];
}tr[5500000];int len;

int seed=233,root=1;

int Rand()//随机key值
{
    return seed=int(seed*482711ll%2147483647);
}

int add(int d)//新建值为d的节点
{
    tr[++len].c=1;
    tr[len].d=d;
    tr[len].key=Rand();
    tr[len].son[0]=tr[len].son[1]=0;
    return len; 
}

void update(int now)//维护子树大小
{
    tr[now].c=tr[tr[now].son[0]].c+tr[tr[now].son[1]].c+1;
}

void split(int now,int &a,int &b,int d)
{//拆分操作
    //now原Treap，a左树，b右树，d判定值
    //注意传地址符
    if(now==0){
        a=b=0;//若now=0分割完毕；
        return;
    }
    if(tr[now].d<=d)//因为now左子树中的所有值都小于now的值，所以若now属于左树，那么他们都属于左树递归now的右子树；
        a=now,split(tr[now].son[1],tr[a].son[1],b,d);//a=now已经使a的右子树=now的右子树，不再递归a的右子树；
        else//同上now右子树也都属于左树，递归左子树；
        b=now,split(tr[now].son[0],a,tr[b].son[0],d); 
    update(now);//因为后面会用到左（右）树的siz所以更新维护
}

void merge(int &now,int a,int b)
{//合并操作
    //now新树
    if(a==0||b==0){
        now=a+b;//若某个树已空，则将另一个树整体插入
        return;
    }
    //按照key值合并（堆性质）
    if(tr[a].key<tr[b].key)//若a树key值<b树，那么b树属于a树的后代，因为b树恒大于a树，那么b树一定属于a树的右后代，a的左子树不变，直接赋给now，递归合并a的右子树和b
        now=a,merge(tr[now].son[1],tr[a].son[1],b);
    else
        now=b,merge(tr[now].son[0],a,tr[b].son[0]);//同理，a树一定是b树的左儿子，递归合并b的左儿子和a
    update(now);
} 

void find(int now,int rank)
{//找第k大
    while(tr[tr[now].son[0]].c+1!=rank){
        if(tr[tr[now].son[0]].c>=rank)
            now=tr[now].son[0];//若左子树大小大于rank，找左子树
        else
            rank-=(tr[tr[now].son[0]].c+1),now=tr[now].son[1];//找右子树（rank-左子树大小-树根（大小为1））号的元素
    }
    printf("%d\n",tr[now].d);
}

void insert(int d)
{
    int x=0,y=0,z;
    z=add(d);//新建节点z，作为z树
    split(root,x,y,d);//将树分为两部分，x树为<=待插入值，y树大于
    merge(x,x,z);//合并x树和新节点z（树），赋给x树
    merge(root,x,y);//合并新x树和y树，赋给根
    //就这么简单
}
void delet(int d)
{
    int x=0,y=0,z=0;
    split(root,x,y,d);//分为x树为<=待aaa删除，y树大于
    split(x,x,z,d-1);//x树分为新x树<待删除，z树等于待删除
    merge(z,tr[z].son[0],tr[z].son[1]);//合并z树左右儿子，赋给z树，即丢弃z树根节点（实现删除）
    merge(x,x,z);
    merge(root,x,y);//合并，不在重复
}

void get_rank(int d)
{
    int x=0,y=0;
    split(root,x,y,d-1);//分为小于待查找值的x树和大于等于的y树
    printf("%d\n",tr[x].c+1);//即为待查找值的编号
    merge(root,x,y);//合并
} 
void get_val(int rank)
{
    find(root,rank);//find查找即可
}

void get_pre(int d)
{
    int x=0,y=0;
    split(root,x,y,d-1);//x树为<=val-1值即小于val值
    find(x,tr[x].c);//在小于val值中找最大的（编号为siz的）就是前驱
    merge(root,x,y);
}

void get_nxt(int d)
{
    int x=0,y=0;
    split(root,x,y,d);//x树小于等于val值，那么y树大于val值
    find(y,1);//在y树中找最小的，即为后继
    merge(root,x,y);//合并
}

int main()
{
    int i,j,k,m;root=1;
    add(2147483627);//初始虚节点
    tr[1].c=0;//siz为0，不算虚节点的大小
    scanf("%d",&m);
    for(i=1;i<=m;i++){
        scanf("%d%d",&j,&k);
        if(j==1)insert(k);
        if(j==2)delet(k);
        if(j==3)get_rank(k);
        if(j==4)get_val(k);
        if(j==5)get_pre(k);
        if(j==6)get_nxt(k);
    }
    return 0;
} 
