#include "aux.h"
#include "objrevolucion.h"
#include <algorithm>
#include "ply_reader.h"




// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
   ply::read_vertices(archivo, this->v);
   std::vector<Tupla3f> perfil = this->v;
   numVerticesPerfil = v.size();

   crearMalla(perfil, num_instancias, tapa_sup, tapa_inf);

   for(int i = 0; i < v.size(); i++){
      colorArray.push_back(Tupla3f(1,0,0));
      negro.push_back(Tupla3f(0,0,0));
      blanco.push_back(Tupla3f(0.8,0.8,0.8));
    }

    calcularAjedrez();
    calcular_normales();
    Material mat2(amarillo[0], amarillo[1], amarillo[2], amarillo_brillo);
    setMaterialSeleccionado(mat2);
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
    std::vector<Tupla3f> perfil = archivo;

    crearMalla(perfil, num_instancias, tapa_sup, tapa_inf);

    for(int i = 0; i < v.size(); i++){
      colorArray.push_back(Tupla3f(1,0,0));
      negro.push_back(Tupla3f(0,0,0));
      blanco.push_back(Tupla3f(0.8,0.8,0.8));
    }

    calcularAjedrez();
    calcular_normales();
    Material mat2(amarillo[0], amarillo[1], amarillo[2], amarillo_brillo);
    setMaterialSeleccionado(mat2);
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, bool tapa_inf, bool tapa_sup, char eje) {
   bool perfil_ascendente;
   Tupla3f polo_sur, polo_norte, v_rot;
   float x,y,z;
   numInstancias = num_instancias;
   numVerticesPerfil = perfil_original.size();

   distanciasPerfil.push_back(0.0);
   for (int i = 1; i < numVerticesPerfil; i++){
      Tupla3f p = perfil_original[i] - perfil_original[i-1];
      distanciasPerfil.push_back(distanciasPerfil[i-1] + p.lengthSq());
   }


   v.clear();
   f.clear();

   switch (toupper(eje)){
      case 'X':
         perfil_ascendente = (perfil_original.front()(X) < perfil_original.back()(X));
         break;

      case 'Y':
         perfil_ascendente = (perfil_original.front()(Y) < perfil_original.back()(Y));
         break;

      case 'Z':
         perfil_ascendente = (perfil_original.front()(Z) < perfil_original.back()(Z));
         break;
   }

   if(!perfil_ascendente){
      std::reverse(perfil_original.begin(), perfil_original.end());
   }

   bool original_inf, original_sup;

   switch(toupper(eje)){
      case 'X':
         original_inf = abs(perfil_original.front()(Y)) <= CERO && abs(perfil_original.front()(Z)) <= CERO;
         original_sup = abs(perfil_original.back()(Y)) <= CERO && abs(perfil_original.back()(Z)) <= CERO;
         break;

      case 'Y':
         original_inf = abs(perfil_original.front()(X)) <= CERO && abs(perfil_original.front()(Z)) <= CERO;
         original_sup = abs(perfil_original.back()(X)) <= CERO && abs(perfil_original.back()(Z)) <= CERO;
         break;

      case 'Z':
         original_inf = abs(perfil_original.front()(X)) <= CERO && abs(perfil_original.front()(Y)) <= CERO;
         original_sup = abs(perfil_original.back()(X)) <= CERO && abs(perfil_original.back()(Y)) <= CERO;
         break;
   }

   if(!original_inf){
      switch(toupper(eje)){
         case 'X':
            x = perfil_original.front()(X);
            y = 0;
            z = 0;
            break;

         case 'Y':
            x = 0;
            y = perfil_original.front()(Y);
            z = 0;
            break;

         case 'Z':
            x = 0;
            y = 0;
            z = perfil_original.front()(Z);
            break;
      }
      polo_sur = {x,y,z};
   }else{
      polo_sur = perfil_original.front();
      perfil_original.erase(perfil_original.begin());
   }
   
   if(!original_sup){
      switch(toupper(eje)){
         case 'X':
            x = perfil_original.back()(X);
            y = 0;
            z = 0;
            break;

         case 'Y':
            x = 0;
            y = perfil_original.back()(Y);
            z = 0;
            break;

         case 'Z':
            x = 0;
            y = 0;
            z = perfil_original.back()(Z);
            break;
      }
      polo_norte = {x,y,z};
   }else{
      polo_norte = perfil_original.back();
      perfil_original.pop_back();
   }

   numVerticesPerfil = perfil_original.size();

   for (int i = 0; i <= numInstancias; i++){
      for (int j = 0; j < numVerticesPerfil; j++){

         switch(toupper(eje)){
            case 'X':
               x = perfil_original[j](X);
               y = cos(2.0*M_PI*i/numInstancias)*perfil_original[j](Y) - sin(2.0*M_PI*i/numInstancias)*perfil_original[j](Z);
               z = sin(2.0*M_PI*i/numInstancias)*perfil_original[j](Y) + cos(2.0*M_PI*i/numInstancias)*perfil_original[j](Z);
               break;

            case 'Y':
               x = cos(2.0*M_PI*i/numInstancias)*perfil_original[j](X) + sin(2.0*M_PI*i/numInstancias)*perfil_original[j](Z);
               y = perfil_original[j](Y);
               z = -sin(2.0*M_PI*i/numInstancias)*perfil_original[j](X) + cos(2.0*M_PI*i/numInstancias)*perfil_original[j](Z);
               break;

            case 'Z':
               x = cos(2.0*M_PI*i/numInstancias)*perfil_original[j](X) - sin(2.0*M_PI*i/numInstancias)*perfil_original[j](Y);
               y = sin(2.0*M_PI*i/numInstancias)*perfil_original[j](X) + cos(2.0*M_PI*i/numInstancias)*perfil_original[j](Y);
               z = perfil_original[j](Z); 
               break;
         }
         
         v_rot = {x,y,z};
         v.push_back(v_rot);
      }
   }

   for (int i = 0; i < numInstancias; i++){
      for (int j = 0; j < numVerticesPerfil - 1; j++){
         int a = numVerticesPerfil * i + j;
         int b = (numVerticesPerfil * (i +1) + j);

         Tupla3i t1 = {a, b, b+1};
         f.push_back(t1);
         Tupla3i t2 = {a, b+1, a+1};
         f.push_back(t2);
      }
   }

   v.push_back(polo_sur);
   v.push_back(polo_norte);

   if(tapa_inf){
      tapaInf = true;
      int i_sur = v.size() - 2;

      for (int i = 0 ; i < numInstancias ; i++){
         f.push_back({(numVerticesPerfil * (i+1) )%i_sur, numVerticesPerfil * i, i_sur});
      }
   }

   if(tapa_sup){
      tapaSup = true;
      int i_norte = v.size() - 1;

      for (int i = 0 ; i < numInstancias - 1 ; i++){
         f.push_back({i_norte, numVerticesPerfil * (i+1) - 1, (numVerticesPerfil * (i+1) - 1) + numVerticesPerfil});
      }

      f.push_back({i_norte, numVerticesPerfil * numInstancias - 1, numVerticesPerfil - 1});
   }

}

void ObjRevolucion::dibujarf(bool diferido){
   if(!tapaSup && !tapaInf){
      if(!diferido)
         glDrawElements (GL_TRIANGLES, 3*f.size() - (3*numInstancias)*2, GL_UNSIGNED_INT, f.data());
      else 
         glDrawElements (GL_TRIANGLES, 3*f.size() - (3*numInstancias)*2, GL_UNSIGNED_INT, 0);
   }
   else{
      if(!diferido)
         glDrawElements (GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, f.data());
      else 
         glDrawElements (GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0);
   }
}

void ObjRevolucion::dibujarf1(bool diferido){
   if(!tapaSup && !tapaInf){
      if(!diferido)
         glDrawElements (GL_TRIANGLES, 3*f1.size() - (3*numInstancias), GL_UNSIGNED_INT, f1.data());
      else 
         glDrawElements (GL_TRIANGLES, 3*f1.size() - (3*numInstancias), GL_UNSIGNED_INT, 0);
   }
   else{
      if(!diferido)
         glDrawElements (GL_TRIANGLES, 3*f1.size(), GL_UNSIGNED_INT, f1.data());
      else 
         glDrawElements (GL_TRIANGLES, 3*f1.size(), GL_UNSIGNED_INT, 0);
   }
}

void ObjRevolucion::dibujarf2(bool diferido){
   if(!tapaSup && !tapaInf){
      if(!diferido)
         glDrawElements (GL_TRIANGLES, 3*f2.size() - (3*numInstancias), GL_UNSIGNED_INT, f2.data());
      else 
         glDrawElements (GL_TRIANGLES, 3*f2.size() - (3*numInstancias), GL_UNSIGNED_INT, 0);
   }
   else{
      if(!diferido)
         glDrawElements (GL_TRIANGLES, 3*f2.size(), GL_UNSIGNED_INT, f2.data());
      else 
         glDrawElements (GL_TRIANGLES, 3*f2.size(), GL_UNSIGNED_INT, 0);
   }
}

void ObjRevolucion::toggleTapas(){
   tapaInf = !tapaInf;
   tapaSup = !tapaSup;
}

void ObjRevolucion::calcularTexturas(){
   float s, t;
   for(int i = 0; i <= numInstancias; i++){
      s = (float)i/(numInstancias);
      for(int j = 0; j < numVerticesPerfil; j++){
         t = distanciasPerfil[j]/distanciasPerfil[numVerticesPerfil-1];
         ct.push_back({s,t});
      }
   }

   /*s=1;
   for(int i = 0; i < numVerticesPerfil; i++){
      t = distanciasPerfil[i]/distanciasPerfil[numVerticesPerfil-1];
      ct.push_back({s,t});
   }*/
}