// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Musicbox.h

//
// #############################################################################

#ifndef MUSICBOX_H_INCLUDED
#define MUSICBOX_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "caja.h"
#include "manivela.h"
#include "cilindro.h"
#include "objply.h"

class MusicBox{
private:
    Caja * cajainf = nullptr;
    Caja * cajasup = nullptr;
    Manivela * manivela = nullptr;
    Cilindro * empunadura = nullptr;
    Cilindro * base = nullptr;
    ObjPLY * leon = nullptr;
    ObjPLY * alaizq = nullptr;
    ObjPLY * alader = nullptr;

    float abrirCaja, girarFigura, girarAlas;
    float velocidadCaja, velocidadFigura, velocidadAlas;
    bool sentidoCaja = false;
    bool sentidoAlas = false;

   std::vector<Tupla4f> bronce = {{0.714, 0.4284, 0.18144, 1.0}, {0.393548, 0.271906, 0.166721, 1.0}, {0.2125, 0.1275, 0.054, 1.0 }};
   float bronce_brillo = 25.6;
   std::vector<Tupla4f> rubi = {{0.61424, 0.04136, 0.04136, 0.55}, {0.727811, 0.626959, 0.626959, 0.55}, {0.1745, 0.01175, 0.01175, 0.55}};
   float rubi_brillo = 78.8;
   std::vector<Tupla4f> goma = {{0.01, 0.01, 0.01, 1.0},{0.4, 0.4, 0.4, 1.0},{0.02, 0.02, 0.02, 1.0}};
   float goma_brillo = 10.0;
   std::vector<Tupla4f> metal = {{0.19225f, 0.19225f, 0.19225f, 1.0f},{0.50754f, 0.50754f, 0.50754f, 1.0f},{0.508273f, 0.508273f, 0.508273f, 1.0f}};
   float metal_brillo = 51.2;

public:
    MusicBox();

    void draw(int modo);
    void cambiar_a_inmediato(bool b);
    void modificaAbrirCaja(float valor);
    void modificaGirarFigura(float valor);
    void modificaGirarAlas(float valor);

    void velocidadAbrirCaja(float valor);
    void velocidadGirarFigura(float valor);
    void velocidadGirarAlas(float valor);
    void animar();

    void setColorSeleccion(color col);
    void setColorSeleccionado();
    void calcularCentro(const GLfloat * v_matrix);
    Tupla3f getCentro();
};

#endif