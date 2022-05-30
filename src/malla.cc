#include "aux.h"
#include "malla.h"
#include <algorithm>

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato(int modo)
{
  // habilitar uso de un array de vértices
  glEnableClientState( GL_VERTEX_ARRAY);

  // indicar el formato y la dirección de memoria del array de vértices
  // (son tuplas de 3 valores float, sin espacio entre ellas)
  glVertexPointer( 3, GL_FLOAT, 0, v.data());

  if(glIsEnabled(GL_LIGHTING)){
     glEnableClientState(GL_NORMAL_ARRAY);
     glNormalPointer(GL_FLOAT, 0, nv.data());
  }

  if(textura != nullptr && !ct.empty()){
     glEnableClientState(GL_TEXTURE_COORD_ARRAY);
     glTexCoordPointer(2, GL_FLOAT, 0, ct.data());
  }

  // visualizar, indicando: tipo de primitiva, número de índices,
  // tipo de los índices, y dirección de la tabla de índices
  switch(modo){
   case 0:
      glColorPointer(3, GL_FLOAT, 0, blanco.data() );
      dibujarf(false);
      break;

   case 1:
      glColorPointer(3, GL_FLOAT, 0, negro.data() );
      dibujarf(false);
      break;

   case 2:
      glColorPointer(3, GL_FLOAT, 0, colorArray.data() );
      dibujarf(false);
      break;

   case 3:
      glColorPointer(3, GL_FLOAT, 0, blanco.data() );
      dibujarf2(false);
      glColorPointer(3, GL_FLOAT, 0, negro.data() );
      dibujarf1(false);
      break;

   case 4:
      glColorPointer(3, GL_FLOAT, 0, c_selec.data());
      dibujarf(false);
      break;
   
   case 5:
      glColorPointer(3, GL_FLOAT, 0, c_seleccionado.data());
      dibujarf(false);
      break;
  }

  //deshabilitar array de vértices
  glDisableClientState( GL_VERTEX_ARRAY);
  if(glIsEnabled(GL_LIGHTING)){
     glDisableClientState(GL_NORMAL_ARRAY);
  }
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido(int modo)
{
   if(id_vbo_ver == 0)
      id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, v.size()*3*sizeof(float), v.data());
   if(id_vbo_col1 == 0)
      id_vbo_col1 = CrearVBO(GL_ARRAY_BUFFER, v.size()*3*sizeof(float), blanco.data());
   if(id_vbo_col2 == 0)
      id_vbo_col2 = CrearVBO(GL_ARRAY_BUFFER, v.size()*3*sizeof(float), negro.data());
   if(id_vbo_c_selec == 0)
      id_vbo_c_selec = CrearVBO(GL_ARRAY_BUFFER, c_selec.size()*3*sizeof(float), c_selec.data());
   if(id_vbo_c_selec == 0)
      id_vbo_c_seleccionado = CrearVBO(GL_ARRAY_BUFFER, c_seleccionado.size()*3*sizeof(float), c_seleccionado.data());

   if(modo != 3){
      if(id_vbo_tri == 0)
         id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f.size()*3*sizeof(int), f.data());
      if(id_vbo_col == 0){
         std::vector<Tupla3f> colorArrayInvertido = colorArray;
         std::reverse(colorArrayInvertido.begin(), colorArrayInvertido.end());
         id_vbo_col = CrearVBO(GL_ARRAY_BUFFER, v.size()*3*sizeof(float), colorArrayInvertido.data());
      }
   }else{
      if(id_vbo_tri1 == 0)
         id_vbo_tri1 = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f1.size()*3*sizeof(int), f1.data());
      if(id_vbo_tri2 == 0)
         id_vbo_tri2 = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f2.size()*3*sizeof(int), f2.data());
   }
   if(glIsEnabled(GL_LIGHTING)){
      if(id_vbo_norm == 0)
         id_vbo_norm = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, nv.size()*3*sizeof(float), nv.data());
   }
   if(textura != nullptr && !ct.empty()){
      if(id_vbo_text == 0)
         id_vbo_text = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, ct.size()*2*sizeof(float), ct.data());
   }

   // especificar localización y formato de la tabla de vértices, habilitar tabla

   glBindBuffer( GL_ARRAY_BUFFER, id_vbo_ver);     // activar VBO de vértices
   glVertexPointer( 3, GL_FLOAT, 0, 0 );           // especifica formato y offset (=0)
   glBindBuffer( GL_ARRAY_BUFFER, 0 );             // desactivar VBO de vértices
   glEnableClientState( GL_VERTEX_ARRAY );         // habilitar tabla de vértices

   if(glIsEnabled(GL_LIGHTING)){
     glEnableClientState(GL_NORMAL_ARRAY);
     glBindBuffer(GL_ARRAY_BUFFER, id_vbo_norm);
     glNormalPointer(GL_FLOAT, 0, 0);
     glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  if(!ct.empty()){
     glEnableClientState(GL_TEXTURE_COORD_ARRAY);
     glBindBuffer(GL_ARRAY_BUFFER, id_vbo_text);
     glTexCoordPointer(2, GL_FLOAT, 0, 0);
     glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
   // visualizar triángulos con glDrawElements (puntero a tabla == 0)
   switch(modo){
      case 0:
         glBindBuffer(GL_ARRAY_BUFFER, id_vbo_col2);
         glEnableClientState(GL_COLOR_ARRAY);
         glColorPointer(3, GL_FLOAT, 0, 0);
         glBindBuffer(GL_ARRAY_BUFFER, 0);
         glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri);
         dibujarf(true);
         glDisableClientState(GL_COLOR_ARRAY);
         break;

      case 1:
         glBindBuffer(GL_ARRAY_BUFFER, id_vbo_col1);
         glEnableClientState(GL_COLOR_ARRAY);
         glColorPointer(3, GL_FLOAT, 0, 0);
         glBindBuffer(GL_ARRAY_BUFFER, 0);
         glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri);
         dibujarf(true);
         glDisableClientState(GL_COLOR_ARRAY);
         break;

      case 2:
         glBindBuffer(GL_ARRAY_BUFFER, id_vbo_col);
         glEnableClientState(GL_COLOR_ARRAY);
         glColorPointer(3, GL_FLOAT, 0, 0);
         glBindBuffer(GL_ARRAY_BUFFER, 0);
         glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri);
         dibujarf(true);
         glDisableClientState(GL_COLOR_ARRAY);
         break;

      case 3:
         glBindBuffer(GL_ARRAY_BUFFER, id_vbo_col1);
         glEnableClientState(GL_COLOR_ARRAY);
         glColorPointer(3, GL_FLOAT, 0, 0);
         glBindBuffer(GL_ARRAY_BUFFER, 0);
         glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri1);
         dibujarf1(true);
         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); 
         glBindBuffer(GL_ARRAY_BUFFER, id_vbo_col2);
         glColorPointer(3, GL_FLOAT, 0, 0);
         glBindBuffer(GL_ARRAY_BUFFER, 0);
         glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri2);
         dibujarf2(true);
         glDisableClientState(GL_COLOR_ARRAY);
         break;
      case 4:
         glBindBuffer(GL_ARRAY_BUFFER, id_vbo_c_selec);
         glEnableClientState(GL_COLOR_ARRAY);
         glColorPointer(3, GL_FLOAT, 0, 0);
         glBindBuffer(GL_ARRAY_BUFFER, 0);
         glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri);
         dibujarf(true);
         glDisableClientState(GL_COLOR_ARRAY);
         break;
      case 5:
         glBindBuffer(GL_ARRAY_BUFFER, id_vbo_c_seleccionado);
         glEnableClientState(GL_COLOR_ARRAY);
         glColorPointer(3, GL_FLOAT, 0, 0);
         glBindBuffer(GL_ARRAY_BUFFER, 0);
         glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri);
         dibujarf(true);
         glDisableClientState(GL_COLOR_ARRAY);
         break;
   }

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);         // desactivar VBO de triángulos

   if(glIsEnabled(GL_LIGHTING)){
     glDisableClientState(GL_NORMAL_ARRAY);
  }
   // desactivar uso de array de vértices
   glDisableClientState(GL_VERTEX_ARRAY);

   glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

GLuint Malla3D::CrearVBO( GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram){
      GLuint id_vbo;                   // resultado: identificador de VBO
      glGenBuffers(1, & id_vbo);       // crear nuevo VBO, obtener identificador (nunca 0)
      glBindBuffer(tipo_vbo, id_vbo);  // activar el VBO usando su identificador

      // esta instrucción hace la transferencia de datos desde RAM hacia GPU
      glBufferData( tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW);

      glBindBuffer( tipo_vbo, 0);      // desactivación del VBO (activar  0)
      return id_vbo;                   // devolver el identificador resultado
   }
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::cambiar_a_inmediato(bool b){
   modo_inmediato = b;
}

void Malla3D::draw(int modo)
{
   if(modo == 5)
      m_seleccionado.aplicar();
   else
   m.aplicar();
   glShadeModel(GL_SMOOTH);

   if(textura != nullptr && !ct.empty() && modo != 4)
      textura->activar();

   if(modo_inmediato)
      draw_ModoInmediato(modo);
   else
      draw_ModoDiferido(modo);
   
   glDisable(GL_TEXTURE_2D);
}

void Malla3D::calcularAjedrez(){
   for(int i = 0; i < f.size(); i++){
      if(i%2 == 0)
         f1.push_back(f[i]);
      else 
         f2.push_back(f[i]);
   }
}

void Malla3D::dibujarf(bool diferido){
   if(!diferido)
      glDrawElements (GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, f.data());
   else 
      glDrawElements (GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0);
}

void Malla3D::dibujarf1(bool diferido){
   if(!diferido)
      glDrawElements (GL_TRIANGLES, 3*f1.size(), GL_UNSIGNED_INT, f1.data());
   else 
      glDrawElements (GL_TRIANGLES, 3*f1.size(), GL_UNSIGNED_INT, 0);
}

void Malla3D::dibujarf2(bool diferido){
   if(!diferido)
      glDrawElements (GL_TRIANGLES, 3*f2.size(), GL_UNSIGNED_INT, f2.data());
   else 
      glDrawElements (GL_TRIANGLES, 3*f2.size(), GL_UNSIGNED_INT, 0);
}

void Malla3D::calcular_normales(){
   nf.resize(f.size());
   for (int i = 0 ; i < f.size() ; i++){
      Tupla3f p = v[f[i](X)];
      Tupla3f q = v[f[i](Y)];
      Tupla3f r = v[f[i](Z)];

      Tupla3f a = q - p;
      Tupla3f b = r - p;
      Tupla3f m = a.cross(b);

      if (m.lengthSq() > 0){
         Tupla3f n = m.normalized();
         nf[i] = n;
      }
   }

   std::vector<Tupla3f> m(v.size());

   for (int i = 0 ; i < f.size() ; i++){
      int v1 = f[i](X);
      int v2 = f[i](Y);
      int v3 = f[i](Z);

      m[v1] = m[v1] + nf[i];
      m[v2] = m[v2] + nf[i];
      m[v3] = m[v3] + nf[i];
   }
   
   nv.resize(v.size());

   for (int i = 0 ; i < v.size() ; i++){
      if (m[i].lengthSq() > 0){
         Tupla3f n = m[i].normalized();
         nv[i] = n;
      }
   }
}

void Malla3D::setMaterial(Material mat){
   m = mat;
}

void Malla3D::setTextura(std::string archivo){
   textura = new Textura(archivo);
   calcularTexturas();
}

void Malla3D::calcularTexturas(){
   for(int i = 0; i < nv.size()/4; i++){
      ct.push_back({0,0});
      ct.push_back({1,0});
      ct.push_back({0,1});
      ct.push_back({1,1});
   }
}

void Malla3D::setColorSeleccion(color col){
   c_selec.resize(nv.size());
   c_seleccionado.resize(nv.size());
   for (int i = 0 ; i < nv.size() ; i++){
      if (col == SEL1){
         c_selec[i] = colorSel1;
      }
      else if (col == SEL2){
         c_selec[i] = colorSel2;
      }
      else if (col == SEL3){
         c_selec[i] = colorSel3;
      }
      else if (col == SEL4){
         c_selec[i] = colorSel4;
      }
      else if (col == SEL5){
         c_selec[i] = colorSel5;
      }

      c_seleccionado[i] = colorAmarillo;
   }
}

void Malla3D::calcularCentro(const GLfloat * v_mat){
   GLfloat v_matrix[16];

   for (int i = 0; i < 16; i++){
      v_matrix[i] = v_mat[i];
   }

   GLfloat m_matrix[16];
   glGetFloatv(GL_MODELVIEW_MATRIX, m_matrix);

   float cx, cy, cz;
   float x, y, z;
   //(CÓDIGO OBTENIDO DE LA IMPLEMENTACIÓN DE MESA DE LA BIBLIOTECA GLU)
   GLfloat inv[16], det;
    inv[0] = v_matrix[5]  * v_matrix[10] * v_matrix[15] -
             v_matrix[5]  * v_matrix[11] * v_matrix[14] -
             v_matrix[9]  * v_matrix[6]  * v_matrix[15] +
             v_matrix[9]  * v_matrix[7]  * v_matrix[14] +
             v_matrix[13] * v_matrix[6]  * v_matrix[11] -
             v_matrix[13] * v_matrix[7]  * v_matrix[10];

    inv[4] = -v_matrix[4]  * v_matrix[10] * v_matrix[15] +
              v_matrix[4]  * v_matrix[11] * v_matrix[14] +
              v_matrix[8]  * v_matrix[6]  * v_matrix[15] -
              v_matrix[8]  * v_matrix[7]  * v_matrix[14] -
              v_matrix[12] * v_matrix[6]  * v_matrix[11] +
              v_matrix[12] * v_matrix[7]  * v_matrix[10];

    inv[8] = v_matrix[4]  * v_matrix[9] * v_matrix[15] -
             v_matrix[4]  * v_matrix[11] * v_matrix[13] -
             v_matrix[8]  * v_matrix[5] * v_matrix[15] +
             v_matrix[8]  * v_matrix[7] * v_matrix[13] +
             v_matrix[12] * v_matrix[5] * v_matrix[11] -
             v_matrix[12] * v_matrix[7] * v_matrix[9];

    inv[12] = -v_matrix[4]  * v_matrix[9] * v_matrix[14] +
               v_matrix[4]  * v_matrix[10] * v_matrix[13] +
               v_matrix[8]  * v_matrix[5] * v_matrix[14] -
               v_matrix[8]  * v_matrix[6] * v_matrix[13] -
               v_matrix[12] * v_matrix[5] * v_matrix[10] +
               v_matrix[12] * v_matrix[6] * v_matrix[9];

    inv[1] = -v_matrix[1]  * v_matrix[10] * v_matrix[15] +
              v_matrix[1]  * v_matrix[11] * v_matrix[14] +
              v_matrix[9]  * v_matrix[2] * v_matrix[15] -
              v_matrix[9]  * v_matrix[3] * v_matrix[14] -
              v_matrix[13] * v_matrix[2] * v_matrix[11] +
              v_matrix[13] * v_matrix[3] * v_matrix[10];

    inv[5] = v_matrix[0]  * v_matrix[10] * v_matrix[15] -
             v_matrix[0]  * v_matrix[11] * v_matrix[14] -
             v_matrix[8]  * v_matrix[2] * v_matrix[15] +
             v_matrix[8]  * v_matrix[3] * v_matrix[14] +
             v_matrix[12] * v_matrix[2] * v_matrix[11] -
             v_matrix[12] * v_matrix[3] * v_matrix[10];

    inv[9] = -v_matrix[0]  * v_matrix[9] * v_matrix[15] +
              v_matrix[0]  * v_matrix[11] * v_matrix[13] +
              v_matrix[8]  * v_matrix[1] * v_matrix[15] -
              v_matrix[8]  * v_matrix[3] * v_matrix[13] -
              v_matrix[12] * v_matrix[1] * v_matrix[11] +
              v_matrix[12] * v_matrix[3] * v_matrix[9];

    inv[13] = v_matrix[0]  * v_matrix[9] * v_matrix[14] -
              v_matrix[0]  * v_matrix[10] * v_matrix[13] -
              v_matrix[8]  * v_matrix[1] * v_matrix[14] +
              v_matrix[8]  * v_matrix[2] * v_matrix[13] +
              v_matrix[12] * v_matrix[1] * v_matrix[10] -
              v_matrix[12] * v_matrix[2] * v_matrix[9];

    inv[2] = v_matrix[1]  * v_matrix[6] * v_matrix[15] -
             v_matrix[1]  * v_matrix[7] * v_matrix[14] -
             v_matrix[5]  * v_matrix[2] * v_matrix[15] +
             v_matrix[5]  * v_matrix[3] * v_matrix[14] +
             v_matrix[13] * v_matrix[2] * v_matrix[7] -
             v_matrix[13] * v_matrix[3] * v_matrix[6];

    inv[6] = -v_matrix[0]  * v_matrix[6] * v_matrix[15] +
              v_matrix[0]  * v_matrix[7] * v_matrix[14] +
              v_matrix[4]  * v_matrix[2] * v_matrix[15] -
              v_matrix[4]  * v_matrix[3] * v_matrix[14] -
              v_matrix[12] * v_matrix[2] * v_matrix[7] +
              v_matrix[12] * v_matrix[3] * v_matrix[6];

    inv[10] = v_matrix[0]  * v_matrix[5] * v_matrix[15] -
              v_matrix[0]  * v_matrix[7] * v_matrix[13] -
              v_matrix[4]  * v_matrix[1] * v_matrix[15] +
              v_matrix[4]  * v_matrix[3] * v_matrix[13] +
              v_matrix[12] * v_matrix[1] * v_matrix[7] -
              v_matrix[12] * v_matrix[3] * v_matrix[5];

    inv[14] = -v_matrix[0]  * v_matrix[5] * v_matrix[14] +
               v_matrix[0]  * v_matrix[6] * v_matrix[13] +
               v_matrix[4]  * v_matrix[1] * v_matrix[14] -
               v_matrix[4]  * v_matrix[2] * v_matrix[13] -
               v_matrix[12] * v_matrix[1] * v_matrix[6] +
               v_matrix[12] * v_matrix[2] * v_matrix[5];

    inv[3] = -v_matrix[1] * v_matrix[6] * v_matrix[11] +
              v_matrix[1] * v_matrix[7] * v_matrix[10] +
              v_matrix[5] * v_matrix[2] * v_matrix[11] -
              v_matrix[5] * v_matrix[3] * v_matrix[10] -
              v_matrix[9] * v_matrix[2] * v_matrix[7] +
              v_matrix[9] * v_matrix[3] * v_matrix[6];

    inv[7] = v_matrix[0] * v_matrix[6] * v_matrix[11] -
             v_matrix[0] * v_matrix[7] * v_matrix[10] -
             v_matrix[4] * v_matrix[2] * v_matrix[11] +
             v_matrix[4] * v_matrix[3] * v_matrix[10] +
             v_matrix[8] * v_matrix[2] * v_matrix[7] -
             v_matrix[8] * v_matrix[3] * v_matrix[6];

    inv[11] = -v_matrix[0] * v_matrix[5] * v_matrix[11] +
               v_matrix[0] * v_matrix[7] * v_matrix[9] +
               v_matrix[4] * v_matrix[1] * v_matrix[11] -
               v_matrix[4] * v_matrix[3] * v_matrix[9] -
               v_matrix[8] * v_matrix[1] * v_matrix[7] +
               v_matrix[8] * v_matrix[3] * v_matrix[5];

    inv[15] = v_matrix[0] * v_matrix[5] * v_matrix[10] -
              v_matrix[0] * v_matrix[6] * v_matrix[9] -
              v_matrix[4] * v_matrix[1] * v_matrix[10] +
              v_matrix[4] * v_matrix[2] * v_matrix[9] +
              v_matrix[8] * v_matrix[1] * v_matrix[6] -
              v_matrix[8] * v_matrix[2] * v_matrix[5];

    det = v_matrix[0] * inv[0] + v_matrix[1] * inv[4] + v_matrix[2] * inv[8] + v_matrix[3] * inv[12];

    det = 1.0 / det;

    for (int i = 0; i < 16; i++)
      v_matrix[i] = inv[i] * det;

   centro = {0.0f, 0.0f, 0.0f};

   for (int i = 0 ; i < v.size() ; i++){
      centro = centro + v[i];
   }

   centro = centro / v.size();

   x = m_matrix[0] * centro(X) + m_matrix[4] * centro(Y) + m_matrix[8] * centro(Z) + m_matrix[12];
   y = m_matrix[1] * centro(X) + m_matrix[5] * centro(Y) + m_matrix[9] * centro(Z) + m_matrix[13];
   z = m_matrix[2] * centro(X) + m_matrix[6] * centro(Y) + m_matrix[10] * centro(Z) + m_matrix[14];

   centro = {x, y, z};

   x = v_matrix[0] * centro(X) + v_matrix[4] * centro(Y) + v_matrix[8] * centro(Z) + v_matrix[12];
   y = v_matrix[1] * centro(X) + v_matrix[5] * centro(Y) + v_matrix[9] * centro(Z) + v_matrix[13];
   z = v_matrix[2] * centro(X) + v_matrix[6] * centro(Y) + v_matrix[10] * centro(Z) + v_matrix[14];

   centro = {x, y, z};
}

void Malla3D::setMaterialSeleccionado(Material mat){
   m_seleccionado = mat;
}

Tupla3f Malla3D::getCentro(){
   return centro;
}
