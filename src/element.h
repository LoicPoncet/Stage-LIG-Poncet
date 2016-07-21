#ifndef ELEMENT_H_INCLUDED
#define ELEMENT_H_INCLUDED

#define ZERO_ELEMENT 0.0

typedef double Element;

#define additionElement(x,y) ((x)+(y)) //Renvoie l'addition de a et b
#define multiplicationElement(x,y) ((x)*(y))

#define equalElement(x,y) ((x)==(y))

Element randomElement();//Renvoie un element

#endif //ELEMENT_H_INCLUDED
