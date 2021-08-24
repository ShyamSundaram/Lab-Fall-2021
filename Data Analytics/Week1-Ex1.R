library(ggplot2)
library(datasets)
data("CO2")
co<-CO2
conc<-co$conc
uptake<-co$uptake
qplot(conc,uptake)