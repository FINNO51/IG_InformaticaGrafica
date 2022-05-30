#include "luzdireccional.h"

LuzDireccional::LuzDireccional(const Tupla2f & orientacion, GLenum idLuz, Tupla4f ambiente, Tupla4f difuso, Tupla4f especular){
    posicion = {orientacion(X), orientacion(Y), 1, 0};
    id = idLuz;
    colorAmbiente = ambiente;
    colorDifuso = difuso;
    colorEspecular = especular;

    float radio = sqrt(pow(posicion(X), 2.0) + pow(posicion(Y), 2.0) + pow(posicion(Z), 2.0));
    alpha = acos(posicion(Z) / radio);
    beta = atan2(posicion(Y), posicion(Z));
}

void LuzDireccional::variarAnguloAlpha(float incremento){
    alpha += incremento;

    float radio = sqrt(pow(posicion(X), 2.0) + pow(posicion(Y), 2.0) + pow(posicion(Z), 2.0));
    posicion(X) = radio * sin(alpha) * cos(beta);
    posicion(Y) = radio * sin(alpha) * sin(beta);
    posicion(Z) = radio * cos(alpha);
}

void LuzDireccional::variarAnguloBeta(float incremento){
    beta += incremento;

    float radio = sqrt(pow(posicion(X), 2.0) + pow(posicion(Y), 2.0) + pow(posicion(Z), 2.0));
    posicion(X) = radio * sin(alpha) * cos(beta);
    posicion(Y) = radio * sin(alpha) * sin(beta);
    posicion(Z) = radio * cos(alpha);
}