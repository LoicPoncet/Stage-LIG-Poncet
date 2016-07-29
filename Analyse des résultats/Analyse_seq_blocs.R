# script R permettant de comparer les temps de calcul des produits de matrices carrées 
# pour des tailles variant de 1 à 100

# extraction des données
data_seq <- read.csv2("mesures_60_550_30_seq.csv",header= T)
data_seq_blocs <- read.csv2("mesures_bocs_seq_64_512_30.csv",header= T)

# déclaration de nos vecteurs
abs <- seq(64,312,4)
ord_seq <- seq(64,312,4)
ord_seq_ma <- seq(64,312,4)


# Calcul des temps moyens de calcul séquentiel pour n allant de 14 à 100 (entre 1 et 14, le temps est infiniment petit)
for (i in seq(1:63)){
  result <- subset(data_seq, data_seq$Taille_mat == 64+(i-1)*4, select = Time, drop = FALSE)
  result <- as.numeric(as.character(result$Time))
  ord_seq[i] <- mean(result)
}

# Calcul des temps moyens de calcul séquentiel avec un mauvais algo pour n allant de 14 à 100 (entre 1 et 14, le temps est infiniment petit)
for (i in seq(1:63)){
  result <- subset(data_seq_blocs, data_seq_blocs$Taille_mat == 64+(i-1)*4, select = Time, drop = FALSE)
  result <- as.numeric(as.character(result$Time))
  ord_seq_ma[i] <- mean(result)
}


# tracé des résultats obtenus
plot(abs,ord_seq,type="l",axes = F, ann = F,col="blue")
par(tcl= -0.2)
axis(1, at=seq(64, 312, by=4), labels=F, lwd=1, lwd.ticks=1)
par(tcl= -0.5)
axis(1, at=seq(64, 312, by=8), labels=seq(64,312,8), lwd=0, lwd.ticks=2)
par(tcl= -0.5)
axis(2)
lines(abs,ord_seq_ma,col="red")
title(main="Temps de calcul en fonction de la taille des matrices", xlab="n", ylab="temps (s)")
legend("topleft", legend = c("calcul séquentiel","calcul séquentiel par blocs"), col=c("blue","red"),lty=1,text.font=2)
