#script R permettant d'analyser les résultats du produit matriciel par blocs sur des matrices de taille 4096 avec 4 threads

library(ggplot2)
library(plyr)

#extraction des données
setwd("~/Stage-LIG-Poncet/Mesures/Blocs")


data <- data.frame(read.csv2(file="mesures_4096_8.csv",sep=';', dec='.'))

# analyse statistique

stat<-ddply(data,c("Taille_blocs"),summarise,N=length(Time),mean=mean(Time),sd=sd(Time),se=1.96*(sd/sqrt(N)))


# tracé des résultats obtenus
p <- ggplot(stat, aes(x=Taille_blocs,y=mean))
p <- p + geom_point(color="red") + geom_line(color="red")
p <- p + geom_errorbar(aes(ymin=mean-se,ymax=mean+se),width=5)
show(p)
