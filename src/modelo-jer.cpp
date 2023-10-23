#include <iostream>
#include <modelo-jer.h>
#include <malla-revol.h>

using namespace std;

// -----------------------------------------------------------------------------

Helicoptero::Helicoptero(){
    agregar( new HeliceSuperior() );
    agregar( new HeliceTrasera() );
    agregar( new Cabina() );
    agregar( new Base() );
}

// -----------------------------------------------------------------------------

HeliceSuperior::HeliceSuperior(){
    Cubo * aspa = new Cubo();
    aspa->ponerColor({0.1, 0.1, 0.1 });

    NodoGrafoEscena * helice = new NodoGrafoEscena();
    helice->agregar( glm::translate( glm::vec3(0.0, 2.0, 0.0) ) );
    helice->agregar( glm::scale( glm::vec3(3.0, 0.1, 0.2) ));
    helice->agregar( aspa );

    agregar(helice);
    agregar( glm::rotate( float(glm::radians(90.0)), glm::vec3( 0.0, 1.0, 0.0)));
    agregar(helice);
}

// -----------------------------------------------------------------------------

HeliceTrasera::HeliceTrasera(){
    Cubo * aspa = new Cubo();
    aspa->ponerColor({0.1, 0.1, 0.1 });

    NodoGrafoEscena * helice1 = new NodoGrafoEscena();
    helice1->agregar( glm::translate( glm::vec3(-3.6, 0.8, 0.3) ) );
    helice1->agregar( glm::scale( glm::vec3(0.05, 0.4, 0.05) ));
    helice1->agregar( aspa );

    NodoGrafoEscena * helice2 = new NodoGrafoEscena();
    helice2->agregar( glm::translate( glm::vec3(-3.6, 0.8, 0.3) ) );
    helice2->agregar( glm::scale( glm::vec3(0.4, 0.05, 0.05) ));
    helice2->agregar( aspa );
    
    agregar(helice1);
    agregar(helice2);
}

// -----------------------------------------------------------------------------

Cabina::Cabina(){
    Cilindro * eje = new Cilindro(6,15);
    eje->ponerColor({0.15, 0.15, 0.15 });

    Cubo * ala = new Cubo();
    ala->ponerColor({0.7, 0.1, 0.1});

    Esfera * principal = new Esfera(20, 20);
    principal->ponerColor({0.7, 0.1, 0.1});

    Cubo * frente = new Cubo();
    frente->ponerColor({0.1, 0.7, 0.9});

    NodoGrafoEscena * ejeHelicesSup = new NodoGrafoEscena();
    ejeHelicesSup->agregar( glm::translate( glm::vec3(0.0, 1.7, 0.0) ) );
    ejeHelicesSup->agregar( glm::scale( glm::vec3(0.1, 0.5, 0.1) ));
    ejeHelicesSup->agregar( eje );

    NodoGrafoEscena * cabina = new NodoGrafoEscena();
    cabina->agregar( glm::translate( glm::vec3(0.0, 0.7, 0.0) ) );
    cabina->agregar( glm::scale( glm::vec3(2.0, 1.0, 1.0) ));
    cabina->agregar( principal );

    NodoGrafoEscena * cuerpo = new NodoGrafoEscena();
    cuerpo->agregar( glm::translate( glm::vec3(-1.5, 0.7, 0.0) ) );
    cuerpo->agregar( glm::scale( glm::vec3(2.0, 0.2, 0.2) ));
    cuerpo->agregar( ala );

    NodoGrafoEscena * extremo = new NodoGrafoEscena();
    extremo->agregar( glm::translate( glm::vec3(-3.7, 0.8, 0.0) ) );
    extremo->agregar( glm::scale( glm::vec3(0.2, 0.5, 0.2) ));
    extremo->agregar( ala );

    NodoGrafoEscena * ejeHelicesTra = new NodoGrafoEscena();
    ejeHelicesTra->agregar( glm::translate( glm::vec3(-3.6, 0.8, 0.0) ) );
    ejeHelicesTra->agregar( glm::scale( glm::vec3(0.05, 0.05, 0.4) ));
    ejeHelicesTra->agregar( glm::rotate( float(glm::radians(90.0)), glm::vec3( 1.0, 0.0, 0.0)) );
    ejeHelicesTra->agregar( eje );

    NodoGrafoEscena * ventana = new NodoGrafoEscena();
    ventana->agregar( glm::translate( glm::vec3(1.8, 0.8, 0.0) ) );
    ventana->agregar( glm::scale( glm::vec3(0.2, 0.3, 0.4) ));
    ventana->agregar( frente );

    agregar(ejeHelicesSup);
    agregar(ejeHelicesTra);
    agregar(cuerpo);
    agregar(extremo);
    agregar(cabina);
    agregar(ventana);
}

// -----------------------------------------------------------------------------

Base::Base(){
    Cilindro * cilindro = new Cilindro(6,15);
    cilindro->ponerColor({0.2, 0.2, 0.2 });

    NodoGrafoEscena * apoyo1 = new NodoGrafoEscena();
    apoyo1->agregar( glm::translate( glm::vec3(1.0, -0.8, 0.5) ) );
    apoyo1->agregar( glm::scale( glm::vec3(2.0, 0.15, 0.15) ));
    apoyo1->agregar( glm::rotate( float(glm::radians(90.0)), glm::vec3( 0.0, 0.0, 1.0)) );
    apoyo1->agregar( cilindro );

    NodoGrafoEscena * apoyo2 = new NodoGrafoEscena();
    apoyo2->agregar( glm::translate( glm::vec3(1.0, -0.8, -0.5) ) );
    apoyo2->agregar( glm::scale( glm::vec3(2.0, 0.15, 0.15) ));
    apoyo2->agregar( glm::rotate( float(glm::radians(90.0)), glm::vec3( 0.0, 0.0, 1.0)) );
    apoyo2->agregar( cilindro );

    NodoGrafoEscena * conexion1 = new NodoGrafoEscena();
    conexion1->agregar( glm::translate( glm::vec3(0.4, -0.8, 0.5) ) );
    conexion1->agregar( glm::rotate( float(glm::radians(20.0)), glm::vec3( -1.0, 0.0, 0.0)) );
    conexion1->agregar( glm::scale( glm::vec3(0.1, 0.7, 0.1) ));
    conexion1->agregar( cilindro );

    NodoGrafoEscena * conexion2 = new NodoGrafoEscena();
    conexion2->agregar( glm::translate( glm::vec3(-0.4, -0.8, 0.5) ) );
    conexion2->agregar( glm::rotate( float(glm::radians(20.0)), glm::vec3( -1.0, 0.0, 0.0)) );
    conexion2->agregar( glm::scale( glm::vec3(0.1, 0.7, 0.1) ));
    conexion2->agregar( cilindro );

    NodoGrafoEscena * conexion3 = new NodoGrafoEscena();
    conexion3->agregar( glm::translate( glm::vec3(0.4, -0.8, -0.5) ) );
    conexion3->agregar( glm::rotate( float(glm::radians(-20.0)), glm::vec3( -1.0, 0.0, 0.0)) );
    conexion3->agregar( glm::scale( glm::vec3(0.1, 0.7, 0.1) ));
    conexion3->agregar( cilindro );

    NodoGrafoEscena * conexion4 = new NodoGrafoEscena();
    conexion4->agregar( glm::translate( glm::vec3(-0.4, -0.8, -0.5) ) );
    conexion4->agregar( glm::rotate( float(glm::radians(-20.0)), glm::vec3( -1.0, 0.0, 0.0)) );
    conexion4->agregar( glm::scale( glm::vec3(0.1, 0.7, 0.1) ));
    conexion4->agregar( cilindro );
    
    agregar(apoyo1);
    agregar(apoyo2);
    agregar(conexion1);
    agregar(conexion2);
    agregar(conexion3);
    agregar(conexion4);
}

// -----------------------------------------------------------------------------

unsigned Helicoptero::leerNumParametros() const{

} 

// -----------------------------------------------------------------------------

void Helicoptero::actualizarEstadoParametro( const unsigned iParam, const float t_sec ){
    switch (iParam)
    {
        case 0:
            break;
        case 1:
            break;
        default:
            break;
    }
}

// -----------------------------------------------------------------------------

void Helicoptero::girar_helices_superiores( const float alpha_nuevo ){
    *giro_helices_superiores = glm::rotate( alpha_nuevo, glm::vec3(0.0, 1.0, 0.0));
}

// -----------------------------------------------------------------------------

void Helicoptero::girar_helices_traseras( const float alpha_nuevo ){

}

// -----------------------------------------------------------------------------

void Helicoptero::elevar_helicoptero( const float h_nuevo ){

}

// -----------------------------------------------------------------------------

