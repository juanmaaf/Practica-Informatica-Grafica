#include <iostream>
#include <modelo-jer.h>
#include <malla-revol.h>

using namespace std;

// -----------------------------------------------------------------------------

Helicoptero::Helicoptero(){
    agregar( new HeliceSuperior() );
    agregar( new HeliceTrasera() );
    agregar( new Cabina() );
}

// -----------------------------------------------------------------------------

HeliceSuperior::HeliceSuperior(){
    NodoGrafoEscena * helice = new NodoGrafoEscena();
    helice->agregar( glm::translate( glm::vec3(0.0, 2.0, 0.0) ) );
    helice->agregar( glm::scale( glm::vec3(3.0, 0.1, 0.2) ));
    helice->agregar( new Cubo() );

    agregar(helice);
    agregar( glm::rotate( float(glm::radians(90.0)), glm::vec3( 0.0, 1.0, 0.0)));
    agregar(helice);
}

// -----------------------------------------------------------------------------

HeliceTrasera::HeliceTrasera(){
    NodoGrafoEscena * helice1 = new NodoGrafoEscena();
    helice1->agregar( glm::translate( glm::vec3(-3.5, 0.8, 0.3) ) );
    helice1->agregar( glm::scale( glm::vec3(0.05, 0.4, 0.05) ));
    helice1->agregar( new Cubo() );

    NodoGrafoEscena * helice2 = new NodoGrafoEscena();
    helice2->agregar( glm::translate( glm::vec3(-3.5, 0.8, 0.3) ) );
    helice2->agregar( glm::scale( glm::vec3(0.4, 0.05, 0.05) ));
    helice2->agregar( new Cubo() );
    
    agregar(helice1);
    agregar(helice2);
}

// -----------------------------------------------------------------------------

Cabina::Cabina(){
    NodoGrafoEscena * eje = new NodoGrafoEscena();
    eje->agregar( glm::translate( glm::vec3(0.0, 1.7, 0.0) ) );
    eje->agregar( glm::scale( glm::vec3(0.1, 0.5, 0.1) ));
    eje->agregar( new Cubo() );

    NodoGrafoEscena * cabina = new NodoGrafoEscena();
    cabina->agregar( glm::translate( glm::vec3(0.0, 0.7, 0.0) ) );
    cabina->agregar( glm::scale( glm::vec3(2.0, 1.0, 1.0) ));
    cabina->agregar( new Esfera(20, 20) );

    NodoGrafoEscena * cuerpo = new NodoGrafoEscena();
    cuerpo->agregar( glm::translate( glm::vec3(-2.0, 0.7, 0.0) ) );
    cuerpo->agregar( glm::scale( glm::vec3(2.0, 0.2, 0.2) ));
    cuerpo->agregar( new Cubo() );

    agregar(eje);
    agregar(cuerpo);
    agregar(cabina);
}

// -----------------------------------------------------------------------------