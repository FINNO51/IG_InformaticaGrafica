#include "objply.h"
#include "ply_reader.h"
 

// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************

ObjPLY::ObjPLY( const std::string & nombre_archivo )
{
   // leer la lista de caras y vértices
   ply::read( nombre_archivo, this->v, this->f );
   for(int i = 0; i < v.size(); i++){
      colorArray.push_back(Tupla3f(0,0,0));
      negro.push_back(Tupla3f(0,0,0));
      blanco.push_back(Tupla3f(0.8,0.8,0.8));
    }

    calcularAjedrez();
    calcular_normales();
    Material mat(goma[0], goma[1], goma[2], goma_brillo);
    setMaterial(mat);
}


