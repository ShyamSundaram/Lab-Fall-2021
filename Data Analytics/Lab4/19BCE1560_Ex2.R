#q1
v1<-c(1,2,3)
v2<-c(4,5,6,7,8,9)
arr<-array(c(v1,v2),dim=c(3,3,2))
arr

#q2
r.names<-c("rname1","rname2","rname3")
c.names<-c("cname1","cname2","cname3")
m.names<-c("mname1","mname2")
v1<-c(1,2,3,4,5,6,7,8,9)
v2<-c(10,11,12,13,14,15,16,17,18)
arr<-array(c(v1,v2),dim=c(3,3,2),dimnames=list(r.names,c.names,m.names))
print(arr)

#q3
#a
arr[2,,1]
#b
arr[,2,1]
#c
arr[2,3,2]
#d
arr[,,2]

#q4
M1<-matrix(arr[,,1],nrow=3,byrow=TRUE)
M1
M2<-matrix(arr[,,2],nrow=3,byrow=TRUE)
M2
M3<-M1+M2
M3
mean(M3)

#q5
face<-c("ace","king","queen","jack","ten")
suit<-c("spades","spades","spades","spades","spades")
flush<-matrix(c(face,suit),nrow=5)
flush

#q6
card<-c("ace","heart",1)
card
typeof(card)