#include "aux.h"
#include "malla.h"
#include "manivela.h"

Manivela::Manivela()
{

   // inicializar la tabla de vértices

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   v.push_back(Tupla3f(0,-0.5,-0.5));
   v.push_back(Tupla3f(0,-0.5,0.5));
   v.push_back(Tupla3f(0,0.5,0.5));
   v.push_back(Tupla3f(0,0.5,-0.5));
   v.push_back(Tupla3f(-6,0.5,-0.5));
   v.push_back(Tupla3f(-6,0.5,0.5));
   v.push_back(Tupla3f(-6,4.5,0.5));
   v.push_back(Tupla3f(-6,4.5,-0.5));
   v.push_back(Tupla3f(-10,4.5,-0.5));
   v.push_back(Tupla3f(-10,4.5,0.5));
   v.push_back(Tupla3f(-10,3.5,0.5));
   v.push_back(Tupla3f(-10,3.5,-0.5));
   v.push_back(Tupla3f(-7,3.5,-0.5));
   v.push_back(Tupla3f(-7,3.5,0.5));
   v.push_back(Tupla3f(-7,-0.5,0.5));
   v.push_back(Tupla3f(-7,-0.5,-0.5));
   
   f.push_back(Tupla3i(0,2,1));
   f.push_back(Tupla3i(0,3,2));
   f.push_back(Tupla3i(3,4,5));
   f.push_back(Tupla3i(3,5,2));
   f.push_back(Tupla3i(5,4,6));
   f.push_back(Tupla3i(4,7,6));
   f.push_back(Tupla3i(7,8,9));
   f.push_back(Tupla3i(7,9,6));
   f.push_back(Tupla3i(8,10,9));
   f.push_back(Tupla3i(8,11,10));
   f.push_back(Tupla3i(11,12,13));
   f.push_back(Tupla3i(10,11,13));
   f.push_back(Tupla3i(12,14,13));
   f.push_back(Tupla3i(12,15,14));
   f.push_back(Tupla3i(15,1,14));
   f.push_back(Tupla3i(15,0,1));
   f.push_back(Tupla3i(1,2,14));
   f.push_back(Tupla3i(2,5,14));
   f.push_back(Tupla3i(14,5,13));
   f.push_back(Tupla3i(5,6,13));
   f.push_back(Tupla3i(6,9,13));
   f.push_back(Tupla3i(13,9,10));
   f.push_back(Tupla3i(15,3,0));
   f.push_back(Tupla3i(15,4,3));
   f.push_back(Tupla3i(15,12,4));
   f.push_back(Tupla3i(4,12,7));
   f.push_back(Tupla3i(7,12,11));
   f.push_back(Tupla3i(7,11,8));

   for(int i = 0; i < v.size(); i++){
      colorArray.push_back(Tupla3f(0,0,float(i)/float(v.size())));
      negro.push_back(Tupla3f(0,0,0));
      blanco.push_back(Tupla3f(0.8,0.8,0.8));
    }

    calcularAjedrez();
    calcular_normales();
    Material mat2(amarillo[0], amarillo[1], amarillo[2], amarillo_brillo);
    setMaterialSeleccionado(mat2);

}

