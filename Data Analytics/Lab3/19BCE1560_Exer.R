data<-read.csv(file='Score.csv')
#Order by section
stud<-data
stud<-stud[order(stud$Section, decreasing=FALSE),]
stud
dim(stud)

#remove duplicates
studu<-unique(stud)
studu
dim(studu)

#transform (adding the columns needed)
studu <- transform(studu,upTest1 = (Test1/100)*25)
studu <- transform(studu,upTest2 = (Test2/100)*25)
studu <- transform(studu,upFinal = (Final/100)*50)

studu

#Sum the normalized marks to get total ot of 100 and Mean
studu <- transform(studu,TotalMarks = upTest1+upTest2+upFinal)
studu
me<-mean(studu$TotalMarks)
me

#add grade
studu$Grades <- cut(studu$TotalMarks,breaks=c(-Inf,50,me,Inf), labels=c("FAIL","BA","AA"))
studu