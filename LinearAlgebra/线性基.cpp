/*
线性基的元素能相互异或得到原集合的元素的所有相互异或得到的值。

线性基是满足性质 1 的最小的集合。

线性基没有异或和为 0 的子集。

线性基中每个元素的异或方案唯一，也就是说，线性基中不同的异或组合异或出的数都是不一样的。

线性基中每个元素的二进制最高位互不相同。
*/
struct Linear_Basis{
    ll p[65],d[65];
    int cnt;
    Linear_Basis() {memset(p,0,sizeof p);}
    ~Linear_Basis() {}
    bool ins(ll x){ //向线性基中插入一个数
        for(int i = 62; i >= 0; i--){
            if(x&(1ll<<i)){
                if(!p[i]) {p[i] = x; break;}
                x ^= p[i];
            }
        }
        return x > 0ll;
    }
    ll MAX(ll x){ //求线性空间与ans异或的最大值
        for(int i = 62; i >= 0; i--)
            if((x^p[i]) > x) x ^= p[i];
        return x;
    }
    //如果是求一个数与线性基的异或最小值，则需要先rebuild，再从高位向低位依次进行异或
    ll MIN(){
        rep(i,0,62)
            if(p[i]) return p[i];
    }
    //将线性基改造成每一位相互独立，即对于二进制的某一位i，只有pi的这一位是1，其它都是0
    void rebuild(){
        cnt = 0;
        for(int i = 62; i >= 0; i--)
            for(int j = i-1; j >= 0; j--)
                if(p[i]&(1ll<<j))
                    p[i]^=p[j];
        rep(i,0,62)
            if(p[i]) d[cnt++] = p[i];
    }
    //求线性基能够组成的数中的第K大
    ll Kth(ll k){
        ll ret = 0;
        if(k >= (1ll<<cnt)) return -1; //k大于子集总数, 找不到
        for(int i = 62; i >= 0; i--)
            if(k&(1ll<<i)) ret ^= d[i];
        return ret;
    }
    //合并两个线性基
    Linear_Basis& merge(const Linear_Basis &xx){
        for(int i = 62; i >= 0; i--)
            if(xx.p[i]) ins(xx.p[i]);
        return *this;
    }
}LB;

//两个线性基求交
Linear_Basis merge(Linear_Basis a, Linear_Basis b){
    Linear_Basis A = a, tmp = a, ans; //tmp不断构建A+(B\ans)
    ll cur,d;
    rep(i,0,33) //从低到高，使得不存在一个基底可以仅由(tmp\A)表示
        if(b.p[i]){ //b中有这个基底
            cur = 0, d = b.p[i];
            per(j,i,0)
                if((d>>j)&1){
                    if(tmp.p[j]){
                        d ^= tmp.p[j], cur ^= A.p[j];
                        if(d) continue;
                        ans.p[i] = cur; //cur的第i位不为0
                    }
                    else tmp.p[j] = d, A.p[j] = cur; //如果不能被表示, A的赋值是为了让高位中含有j这位的基底下放到A中j的位置
                    break;
                }
        }
    return ans;
}
