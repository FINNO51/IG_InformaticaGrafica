// #############################################################################
//
// Informática Gráfica (Grado Informática)
// Archivo: camara.h
// Declaraciones de clase Camara
//
// #############################################################################

#ifndef CAMARA_H_INCLUDED
#define CAMARA_H_INCLUDED

#include "aux.h"

typedef enum {
   ORTOGONAL, PERSPECTIVA
} TipoCamara;

typedef enum{
   MOVIENDO_CAMARA_FIRSTPERSON, MOVIENDO_CAMARA_EXAMINAR, QUIETA
} estadoRaton;

class Camara{
private:
   Tupla3f eye;
   Tupla3f at;
   Tupla3f up;

   TipoCamara tipo;
   float left, right, bottom, top, near, far;

   int objetoSelec = 0;

   const float PI = atan(1)*4.0;

public:
   Camara(Tupla3f e, Tupla3f a, Tupla3f u, float l, float r, float b, float t, float n, float f, TipoCamara tip);

   void rotarXExaminar(float angle);
   void rotarYExaminar(float angle);

   void rotarXFirstPerson(float angle);
   void rotarYFirstPerson(float angle);

   void mover(float x, float y, float z);
   void zoom(float factor);
   void girar(float x, float y);

   void setObserver();
   void setProyeccion();

   void setLeft(float valor);
   void setRight(float valor);
   void setAt(Tupla3f valor);
   float getBottom();
   float getTop();

   void setObjetoSelec(int obj);
   int getObjetoSelec();
   void redimensionar(int Width, int Height);
};

#endif
