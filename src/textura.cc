#include "textura.h"

Textura::Textura(std::string archivo){
    //declara puntero a imagen (pimg)
    jpg::Imagen * pimg = nullptr;
    //cargar la imagen (una sola vez!)
    pimg = new jpg::Imagen(archivo);

    //usar con:
    width = pimg->tamX();       //núm. columnas (unsigned)
    height = pimg->tamY();      //núm. filas (unsigned)
    for (int i = height - 1; i >= 0; i--){
        for(int j = 0; j < width; j++){
            unsigned char * pixel = pimg->leerPixel(j, i);
            data.push_back(pixel[0]);
            data.push_back(pixel[1]);
            data.push_back(pixel[2]);
        }
    }

}

void Textura::activar(){
    glEnable( GL_TEXTURE_2D );

    if(textura_id == 0){
        glGenTextures(1, &textura_id);
        glBindTexture(GL_TEXTURE_2D, textura_id);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data.data());
    }else{
        glBindTexture(GL_TEXTURE_2D, textura_id);
    }
}