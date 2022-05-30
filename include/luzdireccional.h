// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Luzdireccional.h

//
// #############################################################################

#ifndef LUZDIRECCIONAL_H_INCLUDED
#define LUZDIRECCIONAL_H_INCLUDED

#include "luz.h"

class LuzDireccional : public Luz
{
    protected:
        float alpha;
        float beta;
    
    public:
        // inicializar la fuente de luz
        LuzDireccional(const Tupla2f & orientacion, GLenum idLuz, Tupla4f ambiente, Tupla4f difuso, Tupla4f especular);

        // Cambiar ángulo:
        void variarAnguloAlpha( float incremento );
        void variarAnguloBeta( float incremento );
};

#endif