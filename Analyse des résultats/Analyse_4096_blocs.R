#script R permettant d'analyser les résultats du produit matriciel par blocs sur des matrices de taille 4096 avec 4 threads

#extraction des données
setwd("~/Stage-LIG-Poncet/Mesures/Blocs")
data <- read.csv2("mesures_4096.csv")

abs <- seq(16,512,16)

#construction de notre vecteur contenant les temps de calcul
result <- subset(data, data$Taile_blocs == abs, select = Time, drop = FALSE)
result <- as.numeric(as.character(result$Time))


# tracé des résultats obtenus
plot(abs,result,type="o",xlab="Taille des blocs", ylab="temps de calcul (s)")
rect(par("usr")[1], par("usr")[3], par("usr")[2], par("usr")[4], col = "lightgrey")
abline(h = c(15,20,25,30,35), v = c(100,200,300,400,500), col = "grey40")
points(abs,result,type="o",pch=18,col = "blue")

