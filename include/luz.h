// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Luz.h

//
// #############################################################################

#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include "aux.h"

class Luz{
    protected:
        Tupla4f posicion;
        GLenum id;
        Tupla4f colorAmbiente,
                colorDifuso,
                colorEspecular;

    public:
        void activar();
};

#endif