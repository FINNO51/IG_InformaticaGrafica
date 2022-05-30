#include "material.h"

Material::Material(){
    difuso = {0.2, 0.2, 0.2, 1.0};
    especular = {0.0, 0.0, 0.0, 1.0};
    ambiente = {0.8, 0.8, 0.8, 1.0};
    brillo = 0.0;
}

Material::Material(Tupla4f mdifuso, Tupla4f mespecular, Tupla4f mambiente, float bri){
    difuso = mdifuso;
    especular = mespecular;
    ambiente = mambiente;
    brillo = bri;
}

void Material::aplicar(){
    glMaterialfv(GL_FRONT, GL_DIFFUSE, difuso);
    glMaterialfv(GL_FRONT, GL_SPECULAR, especular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
    glMaterialf(GL_FRONT, GL_SHININESS, brillo);
}