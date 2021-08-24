data<-read.csv("stores.csv")
View(data)

# add new variables to a data frame
#Method-1
stores<-data
stores$MyColumn <- (stores$AcqCostPercust + stores$OperatingCost)/2
View(stores)

#Method-2
stores2 = transform(stores, MyColumn2 = (AcqCostPercust + OperatingCost)/2)
View(stores2)

#--------------------------------------------------------------------------------------------------

# Recoding variables in a data frame
#Method-1
# Continuous variables
stores$storeclass1[stores$TotalSales > 240 & stores$TotalSales <= 300] <- "High Perform Store"
stores$storeclass1[stores$TotalSales > 120 & stores$TotalSales <= 240] <- "Average Perform store"
stores$storeclass1[1<2] <- "Low Perform Store"
View(stores)

#Method 2
stores$storeclass2 <- cut(stores$TotalSales,
                          breaks=c(-Inf, 120, 240, Inf),
                          labels=c("low","medium","high"))
View(stores)
#---------------------------------------------------------------------------------------------------
# renaming variables in a data frame
df2 <- stores # working on a copy so later examples still work
names(df2)
names(df2)[names(df2)=="storeclass2"] <- "My_Store_class"
names(df2)

#rename interactively
fix(stores) # results are saved on close
names(stores)
str(stores)


# rename programmatically
install.packages("reshape")
library(reshape)
mydata <- rename(stores, c(StoreCode="MyStoreCode", Location = "MyLocation"))
str(mydata)

#-----------------------------------------------------------------------------------------------------

##### Re-ordering column names
stores1 <- stores[c("StoreType","Location","OperatingCost" , "Total_Customers",
                    "AcqCostPercust", "BasketSize" ,"ProfitPercust","OwnStore")]
str(stores1)

#reorder row (here sorting order of rows by Operating cost in descending order)
View(stores)
store <- stores[order(stores$OperatingCost, decreasing=TRUE),] # use built in function
View(store)

#another way to order rows
newstores1 <- stores[order(-(stores$OperatingCost)),] # use built in function
newstores1
View(newstores1)

# Method-2 # Using plyr and dplyr package
install.packages("plyr")
library(plyr)
newstores1 <- arrange(stores, StoreName) # Use arrange from plyr package
newstores1 <- arrange(stores, StoreName,Location ) # Use arrange from plyr package. Here ordered by storename and within each category of store name, they are sorted by location
View(newstores1)

newstores <- stores[order(stores$Location, stores$TotalSales, decreasing=TRUE),] #using built in function
View(newstores)

stores <- with(stores, stores[order(StoreType, Location, -TotalSales),])



# Use arrange from plyr package
newstores1 <- arrange(stores, -BasketSize) # Use arrange from plyr package
newstores1 <- arrange(stores, -BasketSize, Location ) # Use arrange from plyr package



#####REmoving duplicates



duplicated(stores)
stores[duplicated(stores),] # Show the repeat entries



setwd("D://NASSCOM//data")
Score<- read.csv("Score.csv")
score1<-Score
str(score1)
duplicated(Score)
duplicated(c(Score$Student))
names(Score)
duplicated(c(Score$Test1))



duplicates <- score1[duplicated(score1$Student) & duplicated(score1$Section),]
str(duplicates)
Unique <- score1[!duplicated(score1) ,]
str(Unique)
row.names(Unique) <-NULL
Unique1 <- score1[duplicated(score1$Student) == TRUE & duplicated(score1$Section)==TRUE ,] # Show unique records based on variable
str(Unique1)



unique(score1) # Original data with repeats removed. These do the same:
score1[!duplicated(score1),]