# script R permettant de comparer les temps de calcul des produits de matrices carrées 
# pour des tailles variant de 1 à 100

# extraction des données
setwd("~/Stage-LIG-Poncet/Mesures")
data_seq <- read.csv2("mesures_1_100_128_sequentiel.csv",header= T) 
data_para <- read.csv2("mesures_1_100_128_parallele.csv",header= T)

# déclaration de nos vecteurs
abs <- seq(1:100)
ord_seq <- rep(0,100)
ord_seq_align <- rep(0,100)
ord_para <- seq(1:100)

# Calcul des temps moyens de calcul parallèle pour n allant de 1 à 100
for (i in 1:100){
  result <- subset(data_para, data_para$Taille_mat == i, select = Time, drop = FALSE)
  result <- as.numeric(as.character(result$Time))
  ord_para[i] <- mean(result)
} 

# Calcul des temps moyens de calcul séquentiel pour n allant de 14 à 100 (entre 1 et 14, le temps est infiniment petit)
for (i in (14:100)){
  result <- subset(data_seq, data_seq$Taille_mat == i, select = Time, drop = FALSE)
  result <- as.numeric(as.character(result$Time))
  ord_seq[i] <- mean(result)
}


# tracé des résultats obtenus
plot(abs,ord_seq, xlab="Taille des matrices", ylab="temps de calcul (s)")
rect(par("usr")[1], par("usr")[3], par("usr")[2], par("usr")[4], col = "lightgrey")
abline(h = seq(0,0.030,0.005), v = c(0,20,40,60,80,100), col = "grey40")
lines(abs,ord_seq,col="blue")
lines(abs,ord_para,col="red")
legend("topleft", legend = c("calcul séquentiel","calcul parallèle"), col=c("blue","red"),lty=1,text.font=2)
     