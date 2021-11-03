install.packages('ggpubr')
install.packages('datarium')
library(tidyverse)
library(datarium)
library(ggpubr)

# Load the package
data("marketing", package = "datarium")
head(marketing, 4)

ggplot(marketing, aes(x = youtube, y = sales)) +
  geom_point() +
  stat_smooth()

cor(marketing$sales, marketing$youtube)

model <- lm(sales ~ youtube, data = marketing)
model

#Scatter plot with the regression line
ggplot(marketing, aes(youtube, sales)) +
  geom_point() +
  stat_smooth(method = lm)

#Assessing the model
summary(model)

#
#The summary outputs shows 6 components, including:

#Call. Shows the function call used to compute the regression model.
#Residuals. Provide a quick view of the distribution of the residuals, which by definition have a mean zero. Therefore, the median should not be far from zero, and the minimum and maximum should be roughly equal in absolute value.
#Coefficients. Shows the regression beta coefficients and their statistical significance. Predictor variables, that are significantly associated to the outcome variable, are marked by stars.
#Residual standard error (RSE), R-squared (R2) and the F-statistic are metrics that are used to check how well the model fits to our data.
##Coefficients significance
#The coefficients table, in the model statistical summary, shows:
  
 # the estimates of the beta coefficients
#the standard errors (SE), 
#which defines the accuracy of beta coefficients. 
#For a given beta coefficient, the SE reflects how the coefficient varies under repeated sampling. It can be used to compute the confidence intervals and the t-statistic.
#the t-statistic and the associated p-value, which defines the statistical significance of the beta coefficients.
#

#The statistical hypotheses are as follow:
  
 # Null hypothesis (H0): the coefficients are equal to zero (i.e., no relationship between x and y)
#Alternative Hypothesis (Ha): the coefficients are not equal to zero (i.e., there is some relationship between x and y)

# The higher the t-statistics and lower the p-value the 

#A statistically significant coefficient indicates that 
#there is an association between the predictor (x) and the outcome (y) variable.


#In our example, both the p-values for the intercept and the predictor variable are highly significant, so we can reject the null hypothesis and accept the alternative hypothesis, which means that there is a significant association
#between the predictor and the outcome variables.

#The t-statistic is a very useful guide for whether or not to include a predictor in a model. High t-statistics (which go with low p-values near 0) indicate that a predictor should be retained in a model, #
#while very low t-statistics indicate a predictor could be dropped

#Standard errors and confidence intervals:
  
#  The standard error measures the variability/accuracy of the beta coefficients. It can be used to compute the confidence intervals of the coefficients.

#For example, the 95% confidence interval for the coefficient b1 is defined as b1 +/- 2*SE(b1), where:
  
#  the lower limits of b1 = b1 - 2*SE(b1) = 0.047 - 2*0.00269 = 0.042
#the upper limits of b1 = b1 + 2*SE(b1) = 0.047 + 2*0.00269 = 0.052
#That is, there is approximately a 95% chance that the interval [0.042, 0.052] 
#will contain the true value of b1. 
#Similarly the 95% confidence interval for b0 can be computed as b0 +/- 2*SE(b0).

#Whether or not an RSE of 3.9 units is an acceptable prediction error 
#is subjective and depends on the problem context. 
#However, we can calculate the percentage error. 
#In our data set, the mean value of sales is 16.827, 
#and so the percentage error is 3.9/16.827 = 23%.

sigma(model)*100/mean(marketing$sales)

#Model accuracy
#Once you identified that, at least, one predictor variable is 
#significantly associated the outcome, 
#you should continue the diagnostic by checking how well the model fits the data. 
#This process is also referred to as the goodness-of-fit

#The overall quality of the linear regression fit can be assessed 
#using the following three quantities, displayed in the model summary:
  
 # The Residual Standard Error (RSE).
#The R-squared (R2)
#F-statistic

#To get these information, simply type:
confint(model)


#An (adjusted) R2 that is close to 1 indicates that 
#a large proportion of the variability in the outcome has been 
#explained by the regression model.
#A number near 0 indicates that the regression model did not explain 
#much of the variability in the outcome.
#F-Statistic:
 # The F-statistic gives the overall significance of the model. 
#It assess whether at least one predictor variable has a non-zero coefficient.

#In a simple linear regression, 
#F1 test is not really interesting since it just duplicates 
#the information in given by the t-test, 
#available in the coefficient table. 
#In fact, the F test is identical to the square of the t test: 312.1 = (17.67)^2. 
#This is true in any model with 1 degree of freedom.

#The F-statistic becomes more important once we start using multiple predictors 
#as in multiple linear regression.

#A large F-statistic will corresponds to a 
#statistically significant p-value (p < 0.05). 
#In our example, the F-statistic equal 312.14 producing a p-value of 1.46e-42,

#which is highly significant.
