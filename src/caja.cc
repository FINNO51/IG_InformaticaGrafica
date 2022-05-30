#include "aux.h"
#include "malla.h"
#include "caja.h"

Caja::Caja(float profundidad)
{

   // inicializar la tabla de vértices

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   v.push_back(Tupla3f(-5, 0, 0));
   v.push_back(Tupla3f(5, 0, 0));
   v.push_back(Tupla3f(5, -5, 0));
   v.push_back(Tupla3f(-5, -5, 0));
   v.push_back(Tupla3f(-5, -5, 7));
   v.push_back(Tupla3f(5, -5, 7));
   v.push_back(Tupla3f(5, 0, 7));
   v.push_back(Tupla3f(-5, 0, 7));
   v.push_back(Tupla3f(-4, 0, 6));
   v.push_back(Tupla3f(4, 0, 6));
   v.push_back(Tupla3f(4, -4*profundidad, 6));
   v.push_back(Tupla3f(-4, -4*profundidad, 6));
   v.push_back(Tupla3f(-4, -4*profundidad, 1));
   v.push_back(Tupla3f(4, -4*profundidad, 1));
   v.push_back(Tupla3f(4, 0, 1));
   v.push_back(Tupla3f(-4, 0, 1));
   //Duplicando los puntos para aplicar texturas
   v.push_back(Tupla3f(-5, 0, 0));
   v.push_back(Tupla3f(5, 0, 0));
   v.push_back(Tupla3f(5, -5, 0));
   v.push_back(Tupla3f(-5, -5, 0));
   v.push_back(Tupla3f(-5, -5, 7));
   v.push_back(Tupla3f(5, -5, 7));
   v.push_back(Tupla3f(5, 0, 7));
   v.push_back(Tupla3f(-5, 0, 7));
   v.push_back(Tupla3f(-4, 0, 6));
   v.push_back(Tupla3f(4, 0, 6));
   v.push_back(Tupla3f(4, -4*profundidad, 6));
   v.push_back(Tupla3f(-4, -4*profundidad, 6));
   v.push_back(Tupla3f(-4, -4*profundidad, 1));
   v.push_back(Tupla3f(4, -4*profundidad, 1));
   v.push_back(Tupla3f(4, 0, 1));
   v.push_back(Tupla3f(-4, 0, 1));
         
   
   f.push_back(Tupla3i(0,1,2));
   f.push_back(Tupla3i(0,2,3));
   f.push_back(Tupla3i(0,3,7));
   f.push_back(Tupla3i(3,4,7));
   f.push_back(Tupla3i(7,4,6));
   f.push_back(Tupla3i(6,4,5));
   f.push_back(Tupla3i(6,2,1));
   f.push_back(Tupla3i(6,5,2));
   f.push_back(Tupla3i(19,21,20));
   f.push_back(Tupla3i(19,18,21));
   f.push_back(Tupla3i(16,31,17));
   f.push_back(Tupla3i(31,30,17));
   f.push_back(Tupla3i(16,23,24));
   f.push_back(Tupla3i(16,24,31));
   f.push_back(Tupla3i(23,25,24));
   f.push_back(Tupla3i(23,22,25));
   f.push_back(Tupla3i(22,17,30));
   f.push_back(Tupla3i(22,30,25));
   f.push_back(Tupla3i(15,12,14));
   f.push_back(Tupla3i(12,13,14));
   f.push_back(Tupla3i(8,11,12));
   f.push_back(Tupla3i(8,12,15));
   f.push_back(Tupla3i(8,9,10));
   f.push_back(Tupla3i(8,10,11));
   f.push_back(Tupla3i(14,13,9));
   f.push_back(Tupla3i(13,10,9));
   f.push_back(Tupla3i(27,29,28));
   f.push_back(Tupla3i(27,26,29));

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

void Caja::calcularTexturas(){
   ct.push_back({1,1});
   ct.push_back({0,1});
   ct.push_back({0,0});
   ct.push_back({1,0});
   ct.push_back({0,0});
   ct.push_back({1,0});
   ct.push_back({1,1});
   ct.push_back({0,1});
   ct.push_back({0,1});
   ct.push_back({1,1});
   ct.push_back({1,0});
   ct.push_back({0,0});
   ct.push_back({1,0});
   ct.push_back({0,0});
   ct.push_back({0,1});
   ct.push_back({1,1});

   ct.push_back({1,0});
   ct.push_back({1,1});
   ct.push_back({0,0});
   ct.push_back({1,0});
   ct.push_back({1,1});
   ct.push_back({0,1});
   ct.push_back({1,1});
   ct.push_back({1,0});
   ct.push_back({0.1,0.1});
   ct.push_back({0.1,0.9});
   ct.push_back({0,0});
   ct.push_back({1,0});
   ct.push_back({1,1});
   ct.push_back({0,1});
   ct.push_back({0.1,0.9});
   ct.push_back({0.1,0.1});
}

