deck<-read.csv("deck.csv")

#draw a random card
ind<-sample(nrow(deck),1)
drawn<-deck[ind,]
ind
drawn
deck2<-data.frame(matrix(ncol=3,nrow=0))
colnames(deck2)<-c("face","suit","value")

#put that card on deck2
deck2<-rbind(deck2,drawn)
deck2

#remove that card from deck1
deck<-deck[-c(ind),]
deck

deck3<-data.frame(matrix(ncol=3,nrow=0))
colnames(deck3)<-c("face","suit","value")

print("Face: ")
face=readline();
print("Suit: ")
suit=readline();
value=readline();
value=as.integer(value)