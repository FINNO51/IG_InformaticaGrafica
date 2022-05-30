#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "objply.h"
#include "objrevolucion.h"
#include "cilindro.h"
#include "cono.h"
#include "esfera.h"
#include "luzdireccional.h"
#include "luzposicional.h"
#include "musicbox.h"
#include "camara.h"

const int VOLUMEN = 30;

typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO,SELILUMINACION,SELMOVIMIENTO,SELANIMACION,SELCAMARAS} menu;
typedef enum {NINGUNO, MESA, LATA, TAPA, PEONPRIMERO, PEONSEGUNDO, CAJAMUSICA} objetoEscena;
class Escena
{

   private:

   

 // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)
       
       // variables que definen la posicion de la camara en coordenadas polares
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;

   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();
    


   void clear_window();

   menu modoMenu=NADA;
   dibujado modo_dibujado = INMEDIATO;
                               //puntos,líneas,sólido,ajedrez,tapas
   bool modos_visualizacion[5] = {false, false, true, false,true};
   bool iluminacion = true,
        posicional = true,
        direccional = true,
        angulobeta = false,
        anguloalpha = false,
        animacion = false,
        animacionluz = true,
        movcaja = false,
        movfigura = false,
        movalas = false,
        seleccionvisible = false;
   // Objetos de la escena
   Ejes ejes;
   MusicBox * musicbox = nullptr ;
   Cubo * mesa = nullptr ;
   ObjRevolucion * peon1 = nullptr;
   ObjRevolucion * peon2 = nullptr;
   Cilindro * lata = nullptr;
   Cilindro * tapa = nullptr;
   Esfera * skybox = nullptr;
   LuzPosicional * luzposicional = nullptr ;
   LuzDireccional * luzdireccional = nullptr ;

   std::vector<Tupla4f> bronce = {{0.714, 0.4284, 0.18144, 1.0}, {0.393548, 0.271906, 0.166721, 1.0}, {0.2125, 0.1275, 0.054, 1.0 }};
   float bronce_brillo = 25.6;
   std::vector<Tupla4f> rubi = {{0.61424, 0.04136, 0.04136, 0.30}, {0.727811, 0.626959, 0.626959, 0.30}, {0.1745, 0.01175, 0.01175, 0.30}};
   float rubi_brillo = 78.8;
   std::vector<Tupla4f> goma = {{0.01, 0.01, 0.01, 1.0},{0.4, 0.4, 0.4, 1.0},{0.02, 0.02, 0.02, 1.0}};
   float goma_brillo = 10.0;
   std::vector<Tupla4f> metal = {{0.19225f, 0.19225f, 0.19225f, 1.0f},{0.50754f, 0.50754f, 0.50754f, 1.0f},{0.508273f, 0.508273f, 0.508273f, 1.0f}};
   float metal_brillo = 51.2;

   std::vector<Camara> camaras;
   int camaraActiva = 0;

   int Xraton, Yraton;
   estadoRaton estadoR = QUIETA;

   GLfloat m_vista[16];

   Mix_Music * musica;

   objetoEscena objetoSelec = NINGUNO;

   const float PI = atan(1)*4.0;
   
   public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

    void animarModeloJerarquico();

	// Dibujar
    void dibujar_objetos_visibles(int modo) ;
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

    void ratonMovido(int x, int y);
    void clickRaton(int boton, int estado, int x, int y);
    void actualizarPosicionRaton(int x, int y);
    void actualizarEstadoRaton(estadoRaton estado);

    void eligeObjetos(int modo, objetoEscena obj);
    void dibujaObjetos(objetoEscena obj);
    void posicionaObjetos();
    void dibujaSeleccion();
    void objetoSeleccionado(GLfloat * pixeles);
    bool comparaColores(Tupla3f c1, Tupla3f c2);
    void enfocarObjeto(objetoEscena obj);


};
#endif
