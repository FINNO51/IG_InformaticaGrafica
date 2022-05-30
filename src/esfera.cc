 #include "aux.h"
#include "malla.h"
#include "esfera.h"

Esfera::Esfera(const int num_vert_perfil, const int num_instancias_perf, const float radio)
{
    float x, y, z;
    std::vector<Tupla3f> perfil;

    for (int i = 0; i < num_vert_perfil; i++){
        x = -sin(M_PI*i/num_vert_perfil)*(-radio);
        y = cos(M_PI*i/num_vert_perfil)*(-radio);
        z = 0;

        perfil.push_back({x, y, z});
    }

    crearMalla(perfil, num_instancias_perf, tapaInf, tapaSup, 'Y');

    for(int i = 0; i < v.size(); i++){
      colorArray.push_back(Tupla3f(0,float(i)/float(v.size()),0));
      negro.push_back(Tupla3f(0,0,0));
      blanco.push_back(Tupla3f(0.8,0.8,0.8));
    }

    calcularAjedrez();
    calcular_normales();
    Material mat2(amarillo[0], amarillo[1], amarillo[2], amarillo_brillo);
    setMaterialSeleccionado(mat2);
}