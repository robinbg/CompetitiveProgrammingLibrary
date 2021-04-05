int find(int x) 
{ 
    for(int i=1;i<=mn;i++) 
    if(!used[i]&&map[x][i]) 
    { 
        used[i]=true; 
        if(match[i]==-1||find(match[i])) 
        { 
            match[i]=x; 
            return true; 
        } 
          
    } 
    return false; 
} 
  
int Hungry() 
{ 
    int sum=0; 
    for(int i=1;i<=cn;i++) 
    { 
        memset(used,false,sizeof(used)); 
        if(find(i))sum++; 
    } 
    return sum;  
} 
