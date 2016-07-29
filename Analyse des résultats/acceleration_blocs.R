#script R permettant d'analyser les résultats du produit matriciel par blocs sur des matrices de taille 4096 avec 4 threads

library(ggplot2)
library(plyr)

#extraction des données
setwd("~/Stage-LIG-Poncet/Mesures/Blocs")


data <- data.frame(read.csv2(file="mesures_acceleration_blocs.csv",sep=';', dec='.'))
data_seq <- cbind.data.frame(c(rep(20.6952,4),rep(19.4738,4),rep(20.2996,4),rep(19.3687,4),rep(20.3357,4),rep(21.3352,4),rep(20.865,4),rep(19.5966,4)))

# analyse statistique

stat <- ddply(data,c("Taille_blocs","Nb_threads"),summarise,N=length(Time),mean=mean(Time),sd=sd(Time),se=1.96*(sd/sqrt(N)))
stat <- cbind.data.frame(stat,data_seq)
stat <- ddply(stat,c("Taille_blocs","Nb_threads"),summarise, acceleration=Temps_seq/mean)

# tracé des résultats obtenus

p <- ggplot(data=stat,aes(x=Taille_blocs,y=mean,colour=Taille_blocs))
p <- p + geom_point()
p <- p + geom_errorbar(aes(ymin=mean-se,ymax=mean+se),width=5)
show(p)
