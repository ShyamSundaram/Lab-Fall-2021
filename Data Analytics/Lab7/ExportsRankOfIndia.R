setwd("D:/FALL2122/Lab")
globaldata=read.csv("EuropeanImportsFromOtherCountries.csv",header=TRUE)
globaldata$Volume = as.numeric(as.character(globaldata$Volume))
#converted all NA to zero
globaldata$Volume[is.na(globaldata$Volume)]=0
totalImports=sum(globaldata$Volume)
IndianImports=sum(globaldata$Volume[globaldata$ExportCountry=="India"])
#install.packages("data.table")
#library(data.table)
globtab = data.table(globaldata$ExportCountry,globaldata$Crop,globaldata$Volume)
names(globtab)=c("ExportCountry","Crop","Volume")
globExpPer = globtab[,sum(Volume),by=ExportCountry]
globExpPer$Perc=(globExpPer$V1/totalImports)*100
barplot( globExpPer[globExpPer$Perc>1]$Perc,
        main = "Export Percentage",
        xlab = "Country",
        ylab = "%Export",
        names.arg = globExpPer[globExpPer$Perc>1]$ExportCountry,
        col = "darkred",
        horiz = FALSE,las=2)
globExpPer=globExpPer[order(globExpPer$V1,decreasing=TRUE)]

barplot(globExpPer[which(globExpPer$Perc>5 | globExpPer$ExportCountry == "India")]$Perc,
         main = "Export Percentage",
         xlab = "Country",
         ylab = "%Export",
         names.arg = globExpPer[which(globExpPer$Perc>5| globExpPer$ExportCountry == "India")]$ExportCountry,
         col = "darkred",
         horiz = FALSE,las=2)
