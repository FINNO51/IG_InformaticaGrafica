// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Luzposicional.h

//
// #############################################################################

#ifndef LUZPOSICIONAL_H_INCLUDED
#define LUZPOSICIONAL_H_INCLUDED

#include "luz.h"

class LuzPosicional : public Luz {
    public:
        LuzPosicional( const Tupla3f & posicion, GLenum idLuz, Tupla4f ambiente, Tupla4f difuso, Tupla4f especular );
        void animar();

        float giroLuz = 0.0;
};

#endif