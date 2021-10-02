setwd("D:/FALL2122/Lab/Lab6_DataCleaning")
(txt <- readLines("PeopleBirthDeathData.txt"))

#ignoring lines containing %

T=grepl("%",txt)

#removing lines containing %
data=txt[!T]

#splitting data
(fieldList <- strsplit(data, split = ","))

#Standardizing rows
#The above function accepts a character vector and assigns three values to an output vector of
#class character. 
#The grepl statement detects fields containing alphabetical values a-z or
#A-Z. 
#To assign year of birth and year of death, we use the knowledge that all Dalton brothers
#were born before and died after 1890. To retrieve the fields for each row in the example, we
#need to apply this function to every element of fieldList.
assignFields <- function(x){
  out <- character(3)
  # get names
  i <- grepl("[[:alpha:]]",x)
  out[1] <- x[i]
  # get birth date (if any)
  i <- which(as.numeric(x) < 1890)
  out[2] <- ifelse(length(i)>0, x[i], NA)
  # get death date (if any)
  i <- which(as.numeric(x) > 1890)
  out[3] <- ifelse(length(i)>0, x[i], NA)
  out
}

standardFields <- lapply(fieldList, assignFields)
#Transform to data frame
(M <- matrix(
  unlist(standardFields)
  , nrow=length(standardFields)
  , byrow=TRUE))

#convert matrix to data frame
colnames(M) <- c("name","birth","death")
(daltons = as.data.frame(M, stringsAsFactors=FALSE))
#Normalize to correct type "coersion"
daltons$birth <- as.numeric(daltons$birth)
daltons$death <- as.numeric(daltons$death)
daltons
# example:
gender <- c(2, 1, 1, 2, 0, 1, 1)
# recoding table, stored in a simple vector
recode <- c(male = 1, female = 2)
(gender <- factor(gender, levels = recode, labels = names(recode)))


gender <- c("M", "male ", "Female", "fem.")
grepl("m", gender)
## [1] FALSE TRUE TRUE TRUE
grep("m", gender)
## [1] 2 3 4

T=grepl("^%",txt)
