//prime number
memset(check, false, sizeof(check));
int tot = 0;
for(int i = 2; i <= N; i++){
  if(!check[i])prime[tot++] = i;
  for(int j = 0; j < tot; j++){
    if(i * prime[j] > N)break;
    check[i * prime[j]] = true;
    if(i % prime[j] ==0)break;
  }
}

//euler+moibus
memset(check, false, sizeof(check));
int tot = 0;
for(int i = 2; i <= N; i++){
  if(!check[i])prime[tot++] = i, phi[i] = i-1,mu[i]=-1;
  for(int j = 0; j < tot; j++){
    if(i * prime[j] > N)break;
    check[i * prime[j]] = true;
    if(i % prime[j] ==0)
    {
      phi[i*prime[j]] = phi[i]*prime[j];
      mu[i*prime[j]] = 0;
      break;
  }
    else
    {
      phi[i*prime[j]] = phi[i]*(prime[j]-1);
      mu[i*prime[j]] = -mu[i];
    }
  }
      
}
