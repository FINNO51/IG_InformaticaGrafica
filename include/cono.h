// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cono.h

//
// #############################################################################

#ifndef CONO_H_INCLUDED
#define CONO_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************


class Cono : public ObjRevolucion
{
   public:
   Cono( const int num_instancias_perf,
         const float altura,
         const float radio,
         const char eje);

} ;




#endif 
