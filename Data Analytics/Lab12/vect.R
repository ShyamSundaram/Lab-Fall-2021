m <- matrix(1/36, nrow=6, ncol=6)
su=rep(0,12)
su[2]
for (i in 1:6)
{
  for(j in 1:6)
  {
    su[i+j]=m[i,j]+su[i+j]
  }
}
su[12]