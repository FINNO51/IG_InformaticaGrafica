#include "musicbox.h"

MusicBox::MusicBox(){
    cajainf = new Caja(0.4);
    cajasup = new Caja(1);
    manivela = new Manivela();
    empunadura = new Cilindro(45,5,1.3,'X');
    base = new Cilindro(45,2.8,1.8,'Y');
    leon = new ObjPLY("plys/leon.ply");
    alaizq = new ObjPLY("plys/alaizq.ply");
    alader = new ObjPLY("plys/alader.ply");

    Material mat1(bronce[0], bronce[1], bronce[2], bronce_brillo);
    cajainf->setMaterial(mat1);
    cajasup->setMaterial(mat1);
    base->setMaterial(mat1);

    Material mat2(rubi[0], rubi[1], rubi[2], rubi_brillo);
    leon->setMaterial(mat2);
    alaizq->setMaterial(mat2);
    alader->setMaterial(mat2);

    Material mat3(metal[0], metal[1], metal[2], metal_brillo);
    manivela->setMaterial(mat3);

    Material mat4(goma[0], goma[1], goma[2], goma_brillo);
    empunadura->setMaterial(mat4);

    cajainf->setTextura("texturas/text-madera.jpg");
    cajasup->setTextura("texturas/text-madera.jpg");
    base->setTextura("texturas/text-madera.jpg");

    abrirCaja = 1.0;
    velocidadCaja = 0.0;

    girarFigura = 0.0;
    velocidadFigura = 0.0;

    girarAlas = 0.5;
    velocidadAlas = 0.0;

}

void MusicBox::draw(int modo){
    glPushMatrix();
        glPushMatrix();
            glScalef(10.0,10.0,10.0);

            glPushMatrix();
                cajainf->draw(modo);
            glPopMatrix();

            glPushMatrix();
                glRotatef(180.0,0.0,1.0,0.0);
                glRotatef(180.0+90.0*abrirCaja,1.0,0.0,0.0);
                cajasup->draw(modo);
            glPopMatrix();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0,25.0*abrirCaja,35.0);

            glPushMatrix();
                glTranslatef(0.0,-15.0,0.0);
                glRotatef(-90.0,1.0,0.0,0.0);
                glRotatef(360.0*girarFigura,0.0,0.0,1.0);
                leon->draw(modo);
            glPopMatrix();

            glPushMatrix();
                glRotatef(360.0*girarFigura,0.0,1.0,0.0);

                glPushMatrix();
                    glTranslatef(0.0,-43.0,0.0);
                    glScalef(10.0,10.0,10.0);
                    base->draw(modo);
                glPopMatrix();

                glPushMatrix();
                    glTranslatef(0.0,0.0,-5.0);

                    glPushMatrix();
                        glRotatef(15.0-40.0*girarAlas,0.0,0.0,1.0);
                        glTranslatef(10.0,0.0,0.0);
                        glRotatef(10.0,0.0,1.0,0.0);
                        glRotatef(-20.0,1.0,0.0,0.0);
                        alaizq->draw(modo);
                    glPopMatrix();

                    glPushMatrix();
                        glRotatef(-15.0+40.0*girarAlas,0.0,0.0,1.0);
                        glTranslatef(-10.0,0.0,0.0);
                        glRotatef(-10.0,0.0,1.0,0.0);
                        glRotatef(-20.0,1.0,0.0,0.0);
                        alader->draw(modo);
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    
        glPushMatrix();
            glTranslatef(-50.0,-35.0,35.0);
            glRotatef(360.0*girarFigura,1.0,0.0,0.0);
            glScalef(2.0,2.0,2.0);

            glPushMatrix();
                manivela->draw(modo);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(-15.0,4.0,0.0);
                empunadura->draw(modo);
            glPopMatrix();

        glPopMatrix();
    glPopMatrix();
    
}

void MusicBox::cambiar_a_inmediato(bool b){
    cajainf->cambiar_a_inmediato(b);
    cajasup->cambiar_a_inmediato(b);
    manivela->cambiar_a_inmediato(b);
    empunadura->cambiar_a_inmediato(b);
    base->cambiar_a_inmediato(b);
    leon->cambiar_a_inmediato(b);
    alaizq->cambiar_a_inmediato(b);
    alader->cambiar_a_inmediato(b);
}

void MusicBox::modificaAbrirCaja(float valor){
    abrirCaja += valor;
    if (abrirCaja >= 1.0){
        abrirCaja = 1.0;
    }
    else if (abrirCaja <= 0.0){
        abrirCaja = 0.0;
    }
}

void MusicBox::modificaGirarFigura(float valor){
    girarFigura += valor;
    if (girarFigura >= 1.0){
        girarFigura = girarFigura - 1;
    }
    else if (girarFigura <= 0.0){
        girarFigura = girarFigura + 1;
    }
}

void MusicBox::modificaGirarAlas(float valor){
    girarAlas += valor;
    if (girarAlas >= 1.0){
        girarAlas = 1.0;
    }
    else if (girarAlas <= 0.0){
        girarAlas = 0.0;
    }
}

void MusicBox::velocidadAbrirCaja(float valor){
    velocidadCaja += valor;
    if (velocidadCaja >= 1.0){
        velocidadCaja = 1.0;
    }
    else if (velocidadCaja <= 0.0){
        velocidadCaja = 0.0;
    }
}

void MusicBox::velocidadGirarFigura(float valor){
    velocidadFigura += valor;
    if (velocidadFigura >= 1.0){
        velocidadFigura = 1.0;
    }
    else if (velocidadFigura <= 0.0){
        velocidadFigura = 0.0;
    }
}

void MusicBox::velocidadGirarAlas(float valor){
    velocidadAlas += valor;
    if (velocidadAlas >= 1.0){
        velocidadAlas = 1.0;
    }
    else if (velocidadAlas <= 0.0){
        velocidadAlas = 0.0;
    }
}

void MusicBox::animar(){

    modificaGirarFigura(0.004 + 0.04*velocidadFigura);

    if(!sentidoCaja)
        modificaAbrirCaja(-0.003 - 0.03*velocidadCaja);
    else
        modificaAbrirCaja(0.003 + 0.03*velocidadCaja);
    if(abrirCaja >= 1.0 || abrirCaja <= 0.4)
        sentidoCaja = !sentidoCaja;

    if(!sentidoAlas)
        modificaGirarAlas(-0.02 - 0.2*velocidadAlas);
    else
        modificaGirarAlas(0.02 + 0.2*velocidadAlas);
    if(girarAlas >= 1.0 || girarAlas <= 0.0)
        sentidoAlas = !sentidoAlas;
}

void MusicBox::setColorSeleccion(color col){
    cajainf->setColorSeleccion(col);
    cajasup->setColorSeleccion(col);
    manivela->setColorSeleccion(col);
    empunadura->setColorSeleccion(col);
    base->setColorSeleccion(col);
    leon->setColorSeleccion(col);
    alaizq->setColorSeleccion(col);
    alader->setColorSeleccion(col);
}

void MusicBox::calcularCentro(const GLfloat * v_matrix){
    leon->calcularCentro(v_matrix);
}

Tupla3f MusicBox::getCentro(){
    return leon->getCentro();
}