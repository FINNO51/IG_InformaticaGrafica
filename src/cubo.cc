#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{

   // inicializar la tabla de vértices

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   v.push_back(Tupla3f(-lado/2, -lado/2, -lado/2));      //negro
   v.push_back(Tupla3f(-lado/2, -lado/2, lado/2));       //blanco
   v.push_back(Tupla3f(lado/2, -lado/2, lado/2));        //rojo
   v.push_back(Tupla3f(lado/2, -lado/2, -lado/2));       //verde
   v.push_back(Tupla3f(-lado/2, lado/2, -lado/2));       //azul
   v.push_back(Tupla3f(-lado/2, lado/2, lado/2));        //amarillo
   v.push_back(Tupla3f(lado/2, lado/2, lado/2));         //cian
   v.push_back(Tupla3f(lado/2, lado/2, -lado/2));        //magenta
   
   f.push_back(Tupla3i(0,3,1));  f1.push_back(Tupla3i(0,3,1));
   f.push_back(Tupla3i(3,2,1));  f2.push_back(Tupla3i(3,2,1));
   f.push_back(Tupla3i(5,1,2));  f1.push_back(Tupla3i(5,1,2));
   f.push_back(Tupla3i(6,5,2));  f2.push_back(Tupla3i(6,5,2));
   f.push_back(Tupla3i(4,0,1));  f1.push_back(Tupla3i(4,0,1));
   f.push_back(Tupla3i(5,4,1));  f2.push_back(Tupla3i(5,4,1));
   f.push_back(Tupla3i(7,3,0));  f1.push_back(Tupla3i(7,3,0));
   f.push_back(Tupla3i(4,7,0));  f2.push_back(Tupla3i(4,7,0));
   f.push_back(Tupla3i(6,2,3));  f1.push_back(Tupla3i(6,2,3));
   f.push_back(Tupla3i(7,6,3));  f2.push_back(Tupla3i(7,6,3));
   f.push_back(Tupla3i(4,5,7));  f1.push_back(Tupla3i(4,5,7));
   f.push_back(Tupla3i(7,5,6));  f2.push_back(Tupla3i(7,5,6));

   colorArray.push_back(Tupla3f(0,0,0));       //punto 0
   colorArray.push_back(Tupla3f(0.9,0.9,0.9)); //punto 1
   colorArray.push_back(Tupla3f(1,0,0));       //punto 2
   colorArray.push_back(Tupla3f(0,1,0));       //punto 3
   colorArray.push_back(Tupla3f(0,0,1));       //punto 4
   colorArray.push_back(Tupla3f(1,1,0));       //punto 5
   colorArray.push_back(Tupla3f(0,1,1));       //punto 6
   colorArray.push_back(Tupla3f(1,0,1));       //punto 7

   for(int i = 0; i < v.size(); i++){
      negro.push_back(Tupla3f(0,0,0));
      blanco.push_back(Tupla3f(0.8,0.8,0.8));
   }

   calcular_normales();
   Material mat2(amarillo[0], amarillo[1], amarillo[2], amarillo_brillo);
   setMaterialSeleccionado(mat2);

}

