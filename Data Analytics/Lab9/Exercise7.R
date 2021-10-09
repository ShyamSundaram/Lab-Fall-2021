setwd("D:/Fall2122/Lab/Lab7")
df=read.csv("countrydata_1.csv",header=TRUE)
install.packages("tidyverse")
library("dplyr")
select(df,country,year)
mutate(df,rate=10000*cases/population)
library(ggplot2)
ggplot(df, aes(year, cases)) +
  geom_line(aes(group = country), color = "grey50") +
  geom_point(aes(color = country))

df=read.csv("countrydata_1.csv",header=TRUE)
> 
  > df
country year cases population
1 Afghanistan 1999   745    2344565
2 Afghanistan 2000   845    2344675
3      Brazil 1999  2345     234523
4      Brazil 2000  3345     235342
5       China 1999 10342    8572693
6       China 2000 10343    8583443
> filter(df,year==2000)

> df %>% filter(year==2000)

> df %>% filter(year==2000 & cases <1000)

> df %>% select(country,cases,population) %>% filter(year==2000)

> df %>% filter(year==2000) %>%  select(country,cases,population)

> mutate(df,rate = 10000*cases/population)

select(df,-c(cases,population))

select(df,c(cases,population))

select(df,contains("pul"))

select(df,starts_with("cou"))

mutate(df,rate=10000*cases/population) %>% select(country,rate,everything())


rename(df,case=cases)


count(df,year,wt=cases)

arrange(df,year,population)

arrange(df,desc(year,population))

