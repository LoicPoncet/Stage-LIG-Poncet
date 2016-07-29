#script R permettant d'analyser l'accélération des calculs parallèles sur des matrices de taille 1500*1500 avec différents nombres de threads


#extraction des données
setwd("~/Stage-LIG-Poncet/Mesures")
data <- read.csv2("mesures_acceleration_1500.csv")
data_seq <- read.csv2("mesures_500_4000_1_seq.csv")

abs <- seq(2,16)

#construction de nos vecteurs contenant les temps de calcul
result_seq <- subset(data_seq, data_seq$Taille_mat == 1500, select = Time, drop = FALSE)
result_seq <- as.numeric(as.character(result_seq$Time))

result <- subset(data, data$Nb_threads == abs, select = Time, drop = FALSE)
result <- as.numeric(as.character(result$Time))

result <- result_seq/result

# tracé des résultats obtenus
plot(abs,result,ylim=c(0,16),xlab="Nombre de threads", ylab="facteur d'accélération")
rect(par("usr")[1], par("usr")[3], par("usr")[2], par("usr")[4], col = "lightgrey")
abline(h = seq(0,16,2), v = seq(2,16,2), col = "grey40")
lines(abs,abs)
points(abs,result,type="o",col="red",pch=18)
