#include "luzposicional.h"

LuzPosicional::LuzPosicional(const Tupla3f & posi, GLenum idLuz, Tupla4f ambiente, Tupla4f difuso, Tupla4f especular){
    posicion = {posi(X), posi(Y), posi(Z), 1};
    id = idLuz;
    colorAmbiente = ambiente;
    colorDifuso = difuso;
    colorEspecular = especular;
}

void LuzPosicional::animar(){
    giroLuz += 1.0;
    if(giroLuz >= 360.0)
        giroLuz = 0.0;
    else if(giroLuz <= 0.0)
        giroLuz = 360.0;
}