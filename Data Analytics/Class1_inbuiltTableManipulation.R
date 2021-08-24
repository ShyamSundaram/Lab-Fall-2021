getwd() # print the current working directory - cwd 
ls()    # list the objects in the current workspace
#setwd(mydirectory)      # change to mydirectory
#setwd("C:/Users/abc/Documents/original")  # / instead of \ in windows 
#setwd("/usr/rob/mydir") # on linux
# view and set options for the session
help(options) # learn about available options
options() # view current option settings
options(digits=3) # number of digits to print on output
# work with your previous commands
history() # display last 25 commands
history(max.show=Inf) # display all previous commands

# save your command history 
MyFileName<-paste0("MyHistoryFile","_",format(Sys.time(),format="%b_%d_%y_%H_%M"))

savehistory(file=MyFileName) # default is ".Rhistory" 

# recall your command history 
loadhistory(file=MyFileName) # default is ".Rhistory"
# save the workspace to the file .RData in the cwd 
save.image()


x<-10
y<-20
# save specific objects to a file
# if you don't specify the path, the cwd is assumed 
save(x,y,file="myfile.RData")
# load a workspace into the current session
# if you don't specify the path, the cwd is assumed 
load("myfile.RData")
q() # quit R. You will be prompted to save the workspace.

# Data frame ------------------------------------------------------------------

# table with the same type within a column and different types between columns # defined with a data.frame() function
my_df <- data.frame(id = c(1, 2, 3), 
                    name = c("Name", "count", "Freq"), 
                    Goals = c(50, 49, 25))
dim(my_df)
str(my_df)
summary(my_df)

# Workspace & Environment -----------------------------------------------------

getwd()                       # Get working directory
setwd("C:/")                  # set working directory
ls()                          # List elements of the environment

rm(x)                         # remove an object from workspace
rm(a,b)                       # remove multiple object from workspace
rm(list=ls())                 # clear workspace


# Installing & managing packages -------------------------------------------------------------------------------------------

browseURL("http://cran.r-project.org/web/views/")                              # categorical view of packages
browseURL("http://cran.stat.ucla.edu/web/packages/available_packages_by_name") #CRAN stands for comprehensive r archive network
browseURL("http://crantastic.org")

library()                     # see current packages #brings editor with list of installed packages
search()                      # shows packages that are currently loaded

install.packages("ggplot2")   # TO install packages # download packages from CRAN and install in R
library("ggplot2")            # make package available ; often used for loading in scripts
require("ggplot2")            # prefered for loading in functions; may be better
library(help="ggplot2")       # brings up documentation  in editor window
update.packages("ggplot2")    # check for pacakge updates; do it regularly
detach("package:ggplot2", unload=TRUE) # Unload/Remove  packages # by default, all loaded packges are unloaded when R quits.
remove.packages("ggplot2")    # TO permanantly remove it.   

#Datasets -----------------------------------------------------------------------------------------------------------------------
?datasets                     # Using R's built in data sets

library(help=datasets)
library(datasets)

data(mtcars)                 # Loading mtcars data set
cars <-mtcars                # Save the data into workspace
detach(package:datasets)     # To remove the datasets package

# Viewing data set
mtcars                       # Total data set in console
View(mtcars)                 # Viewing dataset in spreadsheet
head(mtcars,10)              # Viewing top-10 observations (default: top-6)
tail(mtcars)                 # Viewing bottom 10 observations
str(mtcars)                  # Viewing data dictionary
names(mtcars)                # Viewing column names

v1 = mtcars$disp
newvar <- mtcars$disp + mtcars$hp
v1 <- mtcars$mpg             # Assigning single variable from mtcars data to v1
v2 <- mtcars$cyl
v3 <- mtcars$disp
v4 <- mtcars$hp

mtcars1<-rbind(v1,v2,v3,v4) # Combined as rows #Horizontal joins
mtcars2<-cbind(v1,v2,v3,v4) # Combined as columns # Vertical joins

# DATA IMPORT =================================================================

# Import from flat file -------------------------------------------------------

path <- choose.dir()                            # Specify path to data set
file <- paste0(path, "\\", "Car_data_cf_prices.dat")  # Specify file
data_cf_prices <- read.table(file, header = TRUE, sep = " ", na.strings = "NA", stringsAsFactor = TRUE) # Import file
data_cf_prices <- read.table("Car_sales.txt", header = TRUE, sep = ",", na.strings = "NA", stringsAsFactor = TRUE) # Import file
# Get overview of data
head(data_cf_prices)            # first 6 rows
tail(data_cf_prices)            # last 6 rows
summary(data_cf_prices)         # summary statistics
str(data_cf_prices)             # structure of data frame
nrow(data_cf_prices)            # number of rows
ncol(data_cf_prices)            # number of columns
dim(data_cf_prices)             # dimensions (rows, columns)
names(data_cf_prices)           # variable names

# Import from csv -------------------------------------------------------------

# Specify file
file <- paste0(path,"\\", "Car_data_cf.csv")
data_cf <- read.csv(file)

# SPSS files
require(foreign)
file <- paste0(path,"\\", "hsb2.sav")
dat.spss <- read.spss(file, to.data.frame=TRUE)

# Stata files
file <- paste0(path,"\\", "hsb2.dta")
dat.dta <- read.dta(file)
#Importing SAS File

install.packages("sas7bdat")
library(sas7bdat)
file <- paste0(path,"\\", "hsb2.sas7bdat")
data.Sas <- read.sas7bdat(file, debug=FALSE)

#Importing WEB File 

fpe <- read.table("http://data.princeton.edu/wws509/datasets/effort.dat")


# DATA EXPORT =================================================================

# Export to flat file ---------------------------------------------------------

file <- paste0(path, "MyRClassDemo.csv")                     # Specify file
write.table(cars, file, row.names = TRUE, sep = " ", dec = ".", na = "NA", col.names = FALSE) # Export file
dir(path)

# Export to csv ---------------------------------------------------------------

file <- paste0(path, "MyRClassDemo.csv")        # Specify file
write.csv(cars, file)                              # Export file
dir(path)

            

# DATA MANIPULATION =======================================================================================

# Data Manipuation in R

#Sub setting(Filtering)
#Sorting
#Removing Duplicates
#Converting Data Types
#New Variable Creation(Derived Variable Creation)
#Recoding Variables(Binning Variables)
#Renaming Variables
#Reordering column Names
#Appending(adding rows)
#Adding/Removing columns
#Merging(adding columns)
#Transposing the variables
#Modifying values based on some conditions
#Using Functions
#Randomly Selected Samples
#Aggregating - Summarizing data at different levels


# Using existing data set in R
data(mtcars)
MyDF<-mtcars
mpg2<-cbind(mtcars$mpg, mtcars$cyl,mtcars$disp)
obs4 <- mtcars[4:10,]
cols4 <- mtcars[,c(1,2,3)]

subset1 <- mtcars[c("mpg", "cyl")]
subset2 <- subset(mtcars, mpg>18)
subset3 <- subset(mtcars, select= c(mpg, cyl))
subset4 <- subset(mtcars, cyl>5 & mpg>16, select=c(-mpg,-cyl))
