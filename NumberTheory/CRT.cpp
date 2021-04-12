n ← 1
ans ← 0
for i = 1 to k
  n ← n * n[i]
for i = 1 to k
  m ← n / n[i]
  b ← inv(m, n[i])               // b * m mod n[i] = 1
  ans ← (ans + a[i] * m * b) mod n
return ans


lt excrt()/* b为模数， a为余数*/
{
    lt x,y,k;
    lt M=bi[1],ans=ai[1];//第一个方程的解特判
    for(int i=2;i<=n;i++)
    {
        lt a=M,b=bi[i],c=(ai[i]-ans%b+b)%b;//ax≡c(mod b)
        lt gcd=exgcd(a,b,x,y),bg=b/gcd;
        if(c%gcd!=0) return -1; //判断是否无解，然而这题其实不用
        
        x=mul(x,c/gcd,bg);
        ans+=x*M;//更新前k个方程组的答案
        M*=bg;//M为前k个m的lcm
        ans=(ans%M+M)%M;
    }
    return (ans%M+M)%M;
}
