// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Caja.h

//
// #############################################################################

#ifndef CAJA_H_INCLUDED
#define CAJA_H_INCLUDED

#include "aux.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

class Caja : public Malla3D
{
   public:
   Caja(float profundidad) ;
   void calcularTexturas() override;
   

} ;




#endif
