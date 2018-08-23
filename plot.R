#Gongjin Lan
rm(list = ls())
library(ggplot2)
library(dplyr)

setwd("~/projects/bayesian/LimboTest/")
fitnessBO = read.table("value5-2000.txt")
fitnessBO = data.frame(evaluations = c(1:2000),fit = fitnessBO$V1)
fitnessEA = read.table("/Users/lan/Documents/MATLAB/GaTest/5DvsB.O./fitness5-2000.txt")
fitnessEA = data.frame(evaluations = c(1:2000),fit = fitnessEA$V1)

#plot(fitnessBO$evaluations, fitnessBO$fit, main = "B.O. vs E.A.")

ggplot(fitnessBO, aes(evaluations, fit)) + 
  geom_point(alpha = 1/2, colour = "blue", size = 0.5) +
  #geom_smooth(colour = "blue", method = "loess") +
  geom_point(aes(fitnessEA$evaluations, fitnessEA$fit), alpha = 1/2, colour = "red", size = 0.5) +
  #geom_smooth(data = fitnessEA, colour = "red", method = "loess") +
  labs(x="evaluation", y="fitness")+
  #title="The fitness of directed locomotion") +
  ylim(-2.5,5) 
  