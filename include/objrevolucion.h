// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cubo.h

//
// #############################################################################

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "aux.h"
#include "malla.h"

const float CERO = 0.00001;

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad por defecto
// (tiene 9 vertices y 6 caras)

class ObjRevolucion : public Malla3D
{
   public:
       ObjRevolucion();
   ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup=true, bool tapa_inf=true) ;
   ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup=true, bool tapa_inf=true) ;

   void toggleTapas();
protected:
    void crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, bool tapa_inf, bool tapa_sup, char eje='Y');

    void dibujarf(bool diferido) override;
    void dibujarf1(bool diferido) override;
    void dibujarf2(bool diferido) override;
    void calcularTexturas() override;

    int numInstancias;
    int numVerticesPerfil;
    bool tapaInf = true;
    bool tapaSup = true;
    std::vector<float> distanciasPerfil;

} ;




#endif
