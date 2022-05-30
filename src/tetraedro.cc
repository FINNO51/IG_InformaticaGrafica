#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro(float lado)
{

   // inicializar la tabla de vértices

    
   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
   v.push_back(Tupla3f(0.0, 0.0, 0.0));
   v.push_back(Tupla3f(lado, 0.0, 0.0));
   v.push_back(Tupla3f(cos(M_PI/3)*lado, 0.0, sin(M_PI/3)*lado));
   v.push_back(Tupla3f(lado/2, lado*sqrt(6)/3, lado*sqrt(3)/6));

   f.push_back(Tupla3i(0,1,2));  f1.push_back(Tupla3i(0,1,2));
   f.push_back(Tupla3i(0,2,3));  f2.push_back(Tupla3i(0,2,3));
   f.push_back(Tupla3i(1,3,2));  f1.push_back(Tupla3i(1,3,2));
   f.push_back(Tupla3i(3,1,0));  f2.push_back(Tupla3i(3,1,0));

   colorArray.push_back(Tupla3f(1,0,0.5));
   colorArray.push_back(Tupla3f(1,0,0.5));
   colorArray.push_back(Tupla3f(1,0,0.5));
   colorArray.push_back(Tupla3f(0,0,0.5));

   for(int i = 0; i < v.size(); i++){
      negro.push_back(Tupla3f(0,0,0));
      blanco.push_back(Tupla3f(0.8,0.8,0.8));
   }

   calcular_normales();
   Material mat2(amarillo[0], amarillo[1], amarillo[2], amarillo_brillo);
    setMaterialSeleccionado(mat2);
}

