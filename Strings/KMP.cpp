int j=-1;
p[0]=-1;
for(int i=1;i<t.size();i++)
{
  for(;j!=-1 && t[j+1]!=t[i];j=p[j]);
  if(t[j+1]==t[i])j++;
  p[i]=j;
}
j=-1;
for(int i=0;i<s.size();i++)
{
  for(;j!=-1 && t[j+1]!=s[i];j=p[j]);
  if(s[j+1]==t[i])j++;
  if(j==t.size()-1)
  {
     cout<<"pattern occurs with shift "<<i-m<<endl;
    j=p[j];
  }
}
