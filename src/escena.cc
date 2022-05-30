

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

using namespace std;

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    Front_plane       = 50.0;
    Back_plane        = 2000.0;
    Xraton = 0.0;
    Yraton = 0.0;
    Observer_distance = 4*Front_plane;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;

    ejes.changeAxisSize( 5000 );

    // crear los objetos de la escena....
    // .......completar: ...
    // .....
    
    musicbox = new MusicBox();
    mesa = new Cubo(200);
    peon1 = new ObjRevolucion("plys/peon.ply", 45, true, true);
    peon2 = new ObjRevolucion("plys/peon.ply", 45, true, true);
    lata = new Cilindro(45, 60, 18, 'Y');
    tapa = new Cilindro(45, 2, 18, 'Y');
    skybox = new Esfera(100, 100, 1500);

    Material mat3(bronce[0], bronce[1], bronce[2], bronce_brillo);
    peon1->setMaterial(mat3);
   // mesa->setMaterial(mat3);

    Material mat1(goma[0], goma[1], goma[2], goma_brillo);
    peon2->setMaterial(mat1);

    Material mat2(metal[0], metal[1], metal[2], metal_brillo);
    lata->setMaterial(mat2);
    tapa->setMaterial(mat2);
    skybox->setMaterial(mat2);

    lata->setTextura("texturas/text-lata-1.jpg");
    mesa->setTextura("texturas/text-madera.jpg");
    skybox->setTextura("texturas/habitacion.jpg");

    luzposicional = new LuzPosicional({100.0, 100.0, 100.0}, GL_LIGHT0, {0.0, 0.0, 0.0, 1.0}, {1.0, 1.0, 1.0, 1.0}, {0.0, 0.0, 0.0, 1.0});
    luzdireccional = new LuzDireccional({0.0, 100.0}, GL_LIGHT1, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0});

    camaras.push_back(Camara({0.0, 10.0, 300.0}, {0.0, 30.0, 35.0}, {0.0, 1.0, 0.0}, -50.0, 50.0, -50.0, 50.0, 100.0, 2000.0, PERSPECTIVA));
    camaras.push_back(Camara({-75.0, 100.0, 300.0}, {0.0, 30.0, 35.0}, {0.0, 1.0, 0.0}, -100.0, 100.0, -100.0, 100.0, 100.0, 2000.0, ORTOGONAL));
    camaras.push_back(Camara({0.0, 30.0, 200.0}, {0.0, 30.0, 35.0}, {0.0, 1.0, 0.0}, -30.0, 30.0, -30.0, 30.0, 1.0, 2000.0, ORTOGONAL));

    musicbox->setColorSeleccion(SEL1);
    mesa->setColorSeleccion(SEL2);
    peon1->setColorSeleccion(SEL3);
    peon2->setColorSeleccion(SEL4);
    lata->setColorSeleccion(SEL5);
    tapa->setColorSeleccion(SEL5);

}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer
   glEnable(GL_NORMALIZE);

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );

   SDL_Init(SDL_INIT_AUDIO);
   Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048);
   Mix_VolumeMusic(VOLUMEN);
   musica = Mix_LoadMUS("musica/musica.ogg");
   Mix_PlayMusic(musica,-1);
   Mix_PauseMusic();

}



// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::eligeObjetos(int modo, objetoEscena obj){
   if (obj == MESA){
      if (mesa != nullptr){
         mesa->draw(modo);
         if (modo == 4)
            mesa->calcularCentro(m_vista);
      }
   }
   else if (obj == LATA){
      if (lata != nullptr){
         lata->draw(modo);

         if (modo == 4){
            lata->calcularCentro(m_vista);
            tapa->calcularCentro(m_vista);
         }
      }
   }
   else if (obj == TAPA){
      if (tapa != nullptr)
         tapa->draw(modo);
   }
   else if (obj == PEONPRIMERO){
      if (peon1 != nullptr){
         peon1->draw(modo);

         if (modo == 4)
            peon1->calcularCentro(m_vista);
      }
   }
   else if (obj == PEONSEGUNDO){
      if (peon2 != nullptr){
         peon2->draw(modo);

         if (modo == 4)
            peon2->calcularCentro(m_vista);
      }
   }
   else if (obj == CAJAMUSICA){
      if (musicbox != nullptr){
         musicbox->draw(modo);

         if (modo == 4)
            musicbox->calcularCentro(m_vista);
      }
   }
   
}

void Escena::dibujaObjetos(objetoEscena obj){
  
   if (seleccionvisible){
      glPolygonMode(GL_FRONT, GL_FILL);
      eligeObjetos(4, obj);
   }
   else {
      if (camaras[camaraActiva].getObjetoSelec() == obj){
         glPolygonMode(GL_FRONT, GL_FILL);
         eligeObjetos(5, obj);
      }
      else{
         if (modos_visualizacion[0]){
            glPolygonMode(GL_FRONT, GL_POINT);
            glPointSize(5); 
            eligeObjetos(0, obj);
         }

         if (modos_visualizacion[1]){
            glPolygonMode(GL_FRONT, GL_LINE);
            eligeObjetos(1, obj);
         }

         if (modos_visualizacion[2]){
            glPolygonMode(GL_FRONT, GL_FILL);
            eligeObjetos(2, obj);
         }

         if (modos_visualizacion[3]){
            glPolygonMode(GL_FRONT, GL_FILL);
            eligeObjetos(3, obj);
         }


      }
   }

}

void Escena::posicionaObjetos(){
   glPushMatrix();
      glTranslatef(-70.0,-50.0,100.0); //colocar peón en su posición
      glScalef(10.0,10.0,10.0);
      glTranslatef(0.0,1.4,0.0);       //reposar base del peón sobre la mesa
      dibujaObjetos(PEONPRIMERO);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(-30.0,-50.0,110.0); //colocar peón en su posición
      glScalef(10.0,10.0,10.0);
      glTranslatef(0.0,1.4,0.0);       //reposar base del peón sobre la mesa
      dibujaObjetos(PEONSEGUNDO);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(0.0,-150.0,50.0);
      dibujaObjetos(MESA);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(50.0,-50.0,100.0);
      dibujaObjetos(LATA);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(50.0,10.0,100.0);
      dibujaObjetos(TAPA);
   glPopMatrix();

   dibujaObjetos(CAJAMUSICA);

}

void Escena::animarModeloJerarquico(){
   if(animacion){
      musicbox->animar();
   }
   if(animacionluz)
      luzposicional->animar();

}

void Escena::dibujar()
{
   glEnable(GL_CULL_FACE);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();

   glFrontFace(GL_CW);
   skybox->draw(2);
   glFrontFace(GL_CCW);

   glDisable(GL_LIGHTING);
    ejes.draw();
   
   if(iluminacion){
      glEnable(GL_LIGHTING);
   }

   if(modo_dibujado == INMEDIATO){
       musicbox->cambiar_a_inmediato(true);
    }else{
       musicbox->cambiar_a_inmediato(false);
    }

   posicionaObjetos();

   if(posicional){
      glPushMatrix();
         glRotatef(luzposicional->giroLuz, 0.0, 1.0, 0.0);
         luzposicional->activar();
      glPopMatrix();
   }
   else{
      glDisable(GL_LIGHT0);
   }
   if(direccional){
      luzdireccional->activar();
   }
   else{
      glDisable(GL_LIGHT1);
   }

}

void Escena::dibujaSeleccion(){
   glDisable(GL_DITHER);   // Deshabilita el degradado para tener colores homogeneos
   glDisable(GL_LIGHTING); // Deshabilita luces
   glDisable(GL_TEXTURE_2D);  // Deshabilita texturas

   seleccionvisible = true;
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	change_observer();

   posicionaObjetos();

   glEnable(GL_DITHER);
   glEnable(GL_LIGHTING);
   glEnable(GL_TEXTURE_2D);

   seleccionvisible = false;
}

void Escena::objetoSeleccionado(GLfloat * pixeles){
   Tupla3f p;
   for (int i = 0 ; i <= 2 ; i++)
      p(i) = pixeles[i];

   if (comparaColores(p, colorSel1)){
      cout << "Objeto seleccionado: Caja de música" << endl;
      if (camaras[camaraActiva].getObjetoSelec() != CAJAMUSICA){
         enfocarObjeto(CAJAMUSICA);
         camaras[camaraActiva].setObjetoSelec(CAJAMUSICA);
      }
   }
   else if (comparaColores(p, colorSel2)){
      cout << "Objeto seleccionado: Mesa" << endl;
      if (camaras[camaraActiva].getObjetoSelec() != MESA){
         enfocarObjeto(MESA);
         camaras[camaraActiva].setObjetoSelec(MESA);
      }
   }
   else if (comparaColores(p, colorSel3)){
      cout << "Objeto seleccionado: Peon 1" << endl;
      if (camaras[camaraActiva].getObjetoSelec() != PEONPRIMERO){
         enfocarObjeto(PEONPRIMERO);
         camaras[camaraActiva].setObjetoSelec(PEONPRIMERO);
      }
   }
   else if (comparaColores(p, colorSel4)){
      cout << "Objeto seleccionado: Peon 2" << endl;
      if (camaras[camaraActiva].getObjetoSelec() != PEONSEGUNDO){
         enfocarObjeto(PEONSEGUNDO);
         camaras[camaraActiva].setObjetoSelec(PEONSEGUNDO);
      }
   }
   else if (comparaColores(p, colorSel5)){
      cout << "Objeto seleccionado: Lata" << endl;
      if (camaras[camaraActiva].getObjetoSelec() != LATA){
         enfocarObjeto(LATA);
         camaras[camaraActiva].setObjetoSelec(LATA);
      }
   }
   else{
      cout << "Objeto seleccionado: Fondo (deselecciona cualquier objeto)." << endl;
      enfocarObjeto(NINGUNO);
      camaras[camaraActiva].setObjetoSelec(NINGUNO);
   }
}

bool Escena::comparaColores(Tupla3f c1, Tupla3f c2){
   return (fabs(c1(X) - c2(X)) < 0.003) && (fabs(c1(Y) - c2(Y)) < 0.003) && (fabs(c1(Z) - c2(Z)) < 0.003);
}
//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir=false;
   switch( toupper(tecla) )
   {
      case 'Q' :
         if(modoMenu==SELILUMINACION){
            modoMenu=SELVISUALIZACION;
            cout<< "Saliendo del menu" << endl;
         }else if (modoMenu!=NADA){
            modoMenu=NADA;   
            cout << "Saliendo del menu" << endl;
         }         
         else {
            salir=true ;
         }
      break ;
      case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         if(modoMenu==NADA){
            modoMenu=SELVISUALIZACION; 
            cout <<"Menu de visualizacion" << endl;
         }
      break ;
      case 'D' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         if(modoMenu==NADA){
            modoMenu=SELDIBUJADO; 
            cout <<"Menu de dibujado" << endl;
         }
      break ;
      // COMPLETAR con los diferentes opciones de teclado
      case 'M' :
         if (modoMenu==NADA){
            modoMenu=SELMOVIMIENTO;
            cout <<"Menu de movimiento manual" << endl;
         }
      break;

      case 'P' :
         if (modoMenu == SELVISUALIZACION){
            modos_visualizacion[0] = !modos_visualizacion[0];
            if(modos_visualizacion[0]){
               iluminacion = false;
               cout << "Modo puntos activando" << endl;
               modos_visualizacion[3] = false;
            }
         }
         if (modoMenu == SELILUMINACION){
            animacionluz = !animacionluz;
            cout << "Activando/Desactivando animación luz puntual" << endl;
         }
         break;

      case 'L' :
         if (modoMenu == SELVISUALIZACION){
            modos_visualizacion[1] = !modos_visualizacion[1];
            if (modos_visualizacion[1]){
               iluminacion = false;
               cout << "Modo lineas activado" << endl;
               modos_visualizacion[3] = false;
            }
         }
         break;

      case 'S' :
         if(modoMenu == SELVISUALIZACION){
            modos_visualizacion[2] = !modos_visualizacion[2];
            if(modos_visualizacion[2]){
               iluminacion = false;
               cout << "Modo solido activado" << endl;
               modos_visualizacion[3] = false;
            }
         }
         break;

      case 'A' :
         if (modoMenu == SELVISUALIZACION){
            modos_visualizacion[3] = !modos_visualizacion[3];
            if(modos_visualizacion[3]){
               iluminacion = false;
               cout << "Modo ajedrez activado" << endl;
               modos_visualizacion[0] = false;
               modos_visualizacion[1] = false;
               modos_visualizacion[2] = false;
            }
         }
         else if (modoMenu == SELILUMINACION){
            anguloalpha = true;
            angulobeta = false;
            cout << "Modo variación ángulo alpha" << endl;
         }
         else if (modoMenu == NADA){
            modoMenu=SELANIMACION;
            animacion = true;
            if(Mix_PausedMusic() == 1){
               Mix_ResumeMusic();
            }
            cout <<"Menu de animación" << endl;
         }else if (modoMenu == SELANIMACION){
            animacion = !animacion;
            if(Mix_PausedMusic() == 1){
               Mix_ResumeMusic();
            }else if(Mix_PlayingMusic() == 1){
               Mix_PauseMusic();
            }
         }

         break;

      case 'I' :
         if (modoMenu == SELVISUALIZACION){
            iluminacion = !iluminacion;
            modoMenu=SELILUMINACION; 
            modos_visualizacion[0] = false;
            modos_visualizacion[1] = false;
            modos_visualizacion[2] = true;
            modos_visualizacion[3] = false;
            cout <<"Menu de luces" << endl;
         }
         else if(modoMenu == SELILUMINACION){
            iluminacion = !iluminacion;
         }
         break ;

      case 'B' :
         if (modoMenu == SELILUMINACION){
            anguloalpha = false;
            angulobeta = true;
            cout << "Modo variación ángulo beta" << endl;
         }
         break;

      case 'C' :
         if (modoMenu == NADA){
            modoMenu = SELCAMARAS;
            cout << "Menú de cámaras" << endl;
         }
         break;

      case '0' :
         if(modoMenu == SELMOVIMIENTO || modoMenu == SELANIMACION){
            movcaja = !movcaja;
            if(movcaja){
               cout << "Abrir caja seleccionado" << endl;
            } else{
               cout << "Abrir caja no seleccionado" << endl;
            }
         }
         if(modoMenu == SELCAMARAS){
            camaraActiva = 0;
            cout << "Cámara 0, perspectiva" << endl;

            change_projection(1);
            change_observer();
         }
      break;

      case '1' :
         if (modoMenu == SELDIBUJADO){
            modo_dibujado = INMEDIATO;
            cout << "Modo de dibujado inmediato" << endl;
         }
         if(modoMenu == SELILUMINACION){
            cout << "Luz 0 activada (posicional)" << endl;
            posicional = !posicional;
         }
         if(modoMenu == SELMOVIMIENTO || modoMenu == SELANIMACION){
            movfigura = !movfigura;
            if(movfigura){
               cout << "Giro de figura seleccionado" << endl;
            } else{
               cout << "Giro de figura no seleccionado" << endl;
            }
         }
         if(modoMenu == SELCAMARAS){
            camaraActiva = 1;
            cout << "Cámara 1, ortogonal" << endl;
            change_projection(1);

            change_observer();
         }
         break;

      case '2' :
         if (modoMenu == SELDIBUJADO){
            modo_dibujado = DIFERIDO;
            cout << "Modo de dibujado diferido" << endl;
         }
         if(modoMenu == SELILUMINACION){
            cout << "Luz 1 activada (direccional)" << endl;
            direccional = !direccional;
         }
         if(modoMenu == SELMOVIMIENTO || modoMenu == SELANIMACION){
            movalas = !movalas;
            if(movalas){
               cout << "Giro de alas seleccionado" << endl;
            } else{
               cout << "Giro de alas no seleccionado" << endl;
            }
         }
         if(modoMenu == SELCAMARAS){
            camaraActiva = 2;
            cout << "Cámara 2, ortogonal" << endl;
            change_projection(1);
            change_observer();
         }
         break;
         
      case '>' :
         if(modoMenu == SELILUMINACION){
            if(anguloalpha){
               luzdireccional->variarAnguloAlpha(0.1);
               luzdireccional->activar();
            }
            else if(angulobeta){
               luzdireccional->variarAnguloBeta(0.1);
               luzdireccional->activar();
            }
         }
         break;

      case '<' :
         if(modoMenu == SELILUMINACION){
            if(anguloalpha){
               luzdireccional->variarAnguloAlpha(-0.1);
               luzdireccional->activar();
            }
            else if(angulobeta){
               luzdireccional->variarAnguloBeta(-0.1);
               luzdireccional->activar();
            }
         }
         break;   

      case '+' :
         if(modoMenu == SELMOVIMIENTO){
            if(movcaja)
               musicbox->modificaAbrirCaja(0.05);
            if(movfigura)
               musicbox->modificaGirarFigura(0.05);
            if(movalas)
               musicbox->modificaGirarAlas(0.05);
         }
         if(modoMenu == SELANIMACION){
            if(movcaja)
               musicbox->velocidadAbrirCaja(0.05);
            if(movfigura)
               musicbox->velocidadGirarFigura(0.05);
            if(movalas)
               musicbox->velocidadGirarAlas(0.05);
         }
      break;

      case '-' :
         if(modoMenu == SELMOVIMIENTO){
            if(movcaja)
               musicbox->modificaAbrirCaja(-0.05);
            if(movfigura)
               musicbox->modificaGirarFigura(-0.05);
            if(movalas)
               musicbox->modificaGirarAlas(-0.05);
         }
         if(modoMenu == SELANIMACION){
            if(movcaja)
               musicbox->velocidadAbrirCaja(-0.05);
            if(movfigura)
               musicbox->velocidadGirarFigura(-0.05);
            if(movalas)
               musicbox->velocidadGirarAlas(-0.05);
         }
      break;
   }
   return salir;
}
//**************************************************************************

void Escena::teclaEspecial(int Tecla1, int x, int y){
   switch (Tecla1){
	   case GLUT_KEY_LEFT:
         camaras[camaraActiva].rotarYExaminar(-0.1);
         break;

	   case GLUT_KEY_RIGHT:
         camaras[camaraActiva].rotarYExaminar(0.1);
         break;

	   case GLUT_KEY_UP:
         camaras[camaraActiva].rotarXExaminar(0.1);
         break;

	   case GLUT_KEY_DOWN:
         camaras[camaraActiva].rotarXExaminar(-0.1);
         break;

	   case GLUT_KEY_PAGE_UP:
         camaras[camaraActiva].zoom(0.9);
         change_projection(1);
         break;

	   case GLUT_KEY_PAGE_DOWN:
         camaras[camaraActiva].zoom(1.1);
         change_projection(1);
         break;

      case 3:
         camaras[camaraActiva].zoom(0.9);
         change_projection(1);
         break;

      case 4:
         camaras[camaraActiva].zoom(1.1);
         change_projection(1);
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

void Escena::ratonMovido(int x, int y){
   if (estadoR == MOVIENDO_CAMARA_FIRSTPERSON && camaras[camaraActiva].getObjetoSelec() == NINGUNO){
      camaras[camaraActiva].girar(x - Xraton, y - Yraton);
   }
   else if (estadoR == MOVIENDO_CAMARA_EXAMINAR && camaras[camaraActiva].getObjetoSelec() != NINGUNO){
      camaras[camaraActiva].rotarXExaminar((y - Yraton)*(PI/180.0));
      camaras[camaraActiva].rotarYExaminar((x - Xraton)*(PI/180.0));
   }

   Xraton = x;
   Yraton = y;
}

void Escena::clickRaton(int boton, int estado, int x, int y){
   // Click derecho del ratón para mover la cámara en primera persona
	if (boton == GLUT_RIGHT_BUTTON){
		actualizarPosicionRaton(x, y);

		// Se pulsa el botón, por lo que se entra en el estado "moviendo cámara"
		if (estado == GLUT_DOWN){
 			actualizarEstadoRaton(MOVIENDO_CAMARA_FIRSTPERSON);

         if (camaras[camaraActiva].getObjetoSelec() != NINGUNO)
            actualizarEstadoRaton(MOVIENDO_CAMARA_EXAMINAR);
		}
		// Se levanta el botón, por lo que se sale del estado "moviendo cámara"
		else if (estado == GLUT_UP){
			actualizarEstadoRaton(QUIETA);
		}
	}
	// Click izquierdo del raton selecciona objetos
	else if (boton == GLUT_LEFT_BUTTON){
		if (estado == GLUT_DOWN){
         dibujaSeleccion();

   		// Leer el pixel dado por la función gestora del evento de ratón
   		GLint viewport[4];
   		GLfloat pixeles[3];
   		glGetIntegerv(GL_VIEWPORT, viewport);
   		glReadPixels(x, viewport[3]-y, 1, 1, GL_RGB, GL_FLOAT, (void *)pixeles);

   		// Averiguar a qué objeto hemos asignado el color de dicho píxel
   		objetoSeleccionado(pixeles);
      }
	}
	// Scroll del raton
	else if (boton == 3 || boton == 4){
		teclaEspecial(boton, x, y);
	}
}

void Escena::enfocarObjeto(objetoEscena obj){
   Tupla3f enfoque = {0, 35, 35};

   if (obj == MESA){
      enfoque = mesa->getCentro();
   }
   else if (obj == LATA || obj == TAPA){
      enfoque = lata->getCentro();
   }
   else if (obj == PEONPRIMERO){
      enfoque = peon1->getCentro();
   }
   else if (obj == PEONSEGUNDO){
      enfoque = peon2->getCentro();
   }
   else if (obj == CAJAMUSICA){
      enfoque = musicbox->getCentro();
   }

   camaras[camaraActiva].setAt(enfoque);
}

//**************************************************************************

void Escena::actualizarPosicionRaton(int x, int y){
	Xraton = x;
	Yraton = y;
}

void Escena::actualizarEstadoRaton(estadoRaton estado){
   estadoR = estado;
}
//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   /*glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wx = float(Height)*ratio_xy ;
   glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );*/

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   camaras[camaraActiva].setProyeccion();
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   int variacionw = newWidth/10 - Width;
   int variacionh = newHeight/10 - Height;
   Width  = newWidth/10;
   Height = newHeight/10;
   for (int i =  0; i < camaras.size(); i++)
      camaras[i].redimensionar(variacionw, variacionh);
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   /*glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );*/

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   camaras[camaraActiva].setObserver();
   glGetFloatv(GL_MODELVIEW_MATRIX, m_vista);
}
