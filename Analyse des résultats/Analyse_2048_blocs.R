#script R permettant d'analyser les résultats du produit matriciel par blocs sur des matrices de taille 2048 avec différents nombres de threads


#extraction des données
setwd("~/Stage-LIG-Poncet/Mesures/Blocs")
data <- read.csv2("mesures_2048_seq.csv")
data2 <- read.csv2("mesures_2048_2.csv")
data4 <- read.csv2("mesures_2048_4.csv")
data8 <- read.csv2("mesures_2048_8.csv")
data16 <- read.csv2("mesures_2048_8.csv")

abs <- c(16,32,64,128)

#construction de nos vecteurs contenant les temps de calcul
result_seq <- subset(data, data$Taille_blocs == abs, select = Time, drop = FALSE)
result_seq <- as.numeric(as.character(result_seq$Time))

result_2 <- subset(data2, data2$Taille_blocs == abs, select = Time, drop = FALSE)
result_2 <- as.numeric(as.character(result_2$Time))

result_4 <- subset(data4, data4$Taille_blocs == abs, select = Time, drop = FALSE)
result_4 <- as.numeric(as.character(result_4$Time))

result_8 <- subset(data8, data8$Taille_blocs == abs, select = Time, drop = FALSE)
result_8 <- as.numeric(as.character(result_8$Time))

result_16 <- subset(data16, data16$Taille_blocs == abs, select = Time, drop = FALSE)
result_16 <- as.numeric(as.character(result_16$Time))

acceleration2 <- result_seq/result_2
acceleration4 <- result_seq/result_4
acceleration8 <- result_seq/result_8
acceleration16 <- result_seq/result_16


# tracé des résultats obtenus
plot(abs,acceleration8,ylim=c(0,10),xlab="Taille des blocs", ylab="facteur d'accélération")
rect(par("usr")[1], par("usr")[3], par("usr")[2], par("usr")[4], col = "lightgrey")
abline(h = c(0,2,4,6,8,10), v = c(20,40,60,80,100,120), col = "grey40")
points(abs,acceleration8,type="o",col="red",pch=18)
points(abs,acceleration2,type="o",pch=18)
points(abs,acceleration4,type="o",col="blue",pch=18)


