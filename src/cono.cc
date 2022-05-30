#include "aux.h"
#include "malla.h"
#include "cono.h"

Cono::Cono(const int num_instancias_perf, const float altura, const float radio, const char eje)
{
    std::vector<Tupla3f> perfil;
    perfil.resize(2);

    switch(toupper(eje)){
      case 'X':
        perfil[0] = {0.0, radio, 0.0};
        perfil[1] = {altura, 0.0, 0.0};
        break;

      case 'Y':
        perfil[0] = {radio, 0.0, 0.0};
        perfil[1] = {0, altura, 0.0};
        break;

      case 'Z':
        perfil[0] = {0.0, radio, 0.0};
        perfil[1] = {0.0, 0.0, altura};
        break;
    }

    crearMalla(perfil, num_instancias_perf, tapaInf, tapaSup, eje);

    for(int i = 0; i < v.size(); i++){
      colorArray.push_back(Tupla3f(float(i)/float(v.size()),float(i)/float(v.size()),0));
      negro.push_back(Tupla3f(0,0,0));
      blanco.push_back(Tupla3f(0.8,0.8,0.8));
    }

    calcularAjedrez();
    calcular_normales();
    Material mat2(amarillo[0], amarillo[1], amarillo[2], amarillo_brillo);
    setMaterialSeleccionado(mat2);
}