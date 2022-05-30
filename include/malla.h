// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"
#include "material.h"
#include "textura.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

typedef enum {INMEDIATO, DIFERIDO} dibujado;
typedef enum{AMARILLO ,SEL1, SEL2, SEL3, SEL4, SEL5} color;
const Tupla3f colorAmarillo = {1.0, 0.8, 0.0};
const Tupla3f colorSel1 = {1.0, 0.0, 0.0};
const Tupla3f colorSel2 = {0.0, 1.0, 0.0};
const Tupla3f colorSel3 = {0.0, 0.0, 1.0};
const Tupla3f colorSel4 = {0.0, 1.0, 1.0};
const Tupla3f colorSel5 = {1.0, 0.0, 1.0};

class Malla3D
{
   public:

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato(int modo);

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido(int modo);

   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   void draw(int modo) ;

   virtual void dibujarf(bool diferido);
   virtual void dibujarf1(bool diferido);
   virtual void dibujarf2(bool diferido);

   void cambiar_a_inmediato(bool b);

   void calcularAjedrez();

   void setMaterial(Material mat);

   void setTextura(std::string archivo);
   virtual void calcularTexturas();

   void setColorSeleccion(color col);

   void setMaterialSeleccionado(Material mat);
   void calcularCentro(const GLfloat * v_matrix);
   Tupla3f getCentro();

   protected:

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)

   std::vector<Tupla3f> v ; // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f ; // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3i> f1; // vectores para el modo ajedrez
   std::vector<Tupla3i> f2;
   std::vector<Tupla3f> nf; // tabla de normales de caras
   std::vector<Tupla3f> nv; // tabla de normales de vértices
   std::vector<Tupla2f> ct; // tabla de coordenadas de textura
   std::vector<Tupla3f> colorArray;
   std::vector<Tupla3f> negro;
   std::vector<Tupla3f> blanco;
   std::vector<Tupla3f> c_selec;
   std::vector<Tupla3f> c_seleccionado;
   
   
   Tupla3f centro;

   Material m;
   Material m_seleccionado;
   Textura * textura = nullptr;

   std::vector<Tupla4f> bronce = {{0.714, 0.4284, 0.18144, 1.0}, {0.393548, 0.271906, 0.166721, 1.0}, {0.2125, 0.1275, 0.054, 1.0 }};
   float bronce_brillo = 25.6;
   std::vector<Tupla4f> rubi = {{0.61424, 0.04136, 0.04136, 0.55}, {0.727811, 0.626959, 0.626959, 0.55}, {0.1745, 0.01175, 0.01175, 0.55}};
   float rubi_brillo = 78.8;
   std::vector<Tupla4f> goma = {{0.01, 0.01, 0.01, 1.0},{0.4, 0.4, 0.4, 1.0},{0.02, 0.02, 0.02, 1.0}};
   float goma_brillo = 10.0;
   std::vector<Tupla4f> amarillo = {{0.0, 0.0, 0.0, 1.0}, {0.5, 0.5, 0.0, 1.0}, {0.6, 0.6, 0.5, 1.0}};
   float amarillo_brillo = 0.25;

   bool modo_inmediato = true;

   GLuint id_vbo_ver = 0;
   GLuint id_vbo_tri = 0;
   GLuint id_vbo_col = 0;
   GLuint id_vbo_tri1 = 0;
   GLuint id_vbo_tri2 = 0;
   GLuint id_vbo_col1 = 0;
   GLuint id_vbo_col2 = 0;
   GLuint id_vbo_norm = 0;
   GLuint id_vbo_text = 0;
   GLuint id_vbo_c_selec = 0;
   GLuint id_vbo_c_seleccionado = 0;

   GLuint CrearVBO( GLuint tipo_vbo, GLuint tamanio_bytes,
                      GLvoid * puntero_ram);
} ;


#endif
