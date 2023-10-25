#include <iostream>
#include <modelo-jer.h>
#include <malla-revol.h>

using namespace std;

// -----------------------------------------------------------------------------

Helicoptero::Helicoptero(const float giro_superior_inicial, const float giro_atras_inicial, const float h_inicial){
    unsigned ind3 = agregar(glm::translate(glm::vec3( 0.0, h_inicial, 0.0)));
    altura_helicoptero = leerPtrMatriz(ind3);

    NodoGrafoEscena * helice_sup = new NodoGrafoEscena();
    unsigned ind1 = helice_sup->agregar( glm::rotate( float(glm::radians(giro_superior_inicial)), glm::vec3( 0.0, 1.0, 0.0)));
    giro_helices_superiores = helice_sup->leerPtrMatriz(ind1);
    helice_sup->agregar( new HeliceSuperior() );

    NodoGrafoEscena * helice_trasera = new NodoGrafoEscena();
    helice_trasera->agregar( glm::translate( glm::vec3(-3.6, 0.8, 0.3) ) );
    unsigned ind2 = helice_trasera->agregar( glm::rotate( float(glm::radians(giro_atras_inicial)), glm::vec3( 0.0, 0.0, 1.0)));
    giro_helices_traseras = helice_trasera->leerPtrMatriz(ind2);
    helice_trasera->agregar( new HeliceTrasera() );

    agregar( new Cabina() );
    agregar( new Base() );
    agregar( helice_sup );
    agregar( helice_trasera );
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
    helice1->agregar( glm::scale( glm::vec3(0.05, 0.4, 0.05) ));
    helice1->agregar( aspa );

    NodoGrafoEscena * helice2 = new NodoGrafoEscena();
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
    return 3;
} 

// -----------------------------------------------------------------------------

void Helicoptero::actualizarEstadoParametro( const unsigned iParam, const float t_sec ){

    switch (iParam)
    {
        unsigned v;
        case 0: // Girar Helices Sup
            v = calcula_oscilante(t_sec);
            girar_helices_superiores(v);
            break;
        case 1: // Girar Helices Tra
            v = calcula_oscilante(t_sec);
            girar_helices_traseras(v);
            break;
        case 2: // Elevar Helicoptero
            v = calcula_lineal(t_sec);
            elevar_helicoptero(v);
            break;
        default:
            break;
    }
}

// -----------------------------------------------------------------------------

void Helicoptero::girar_helices_superiores( const float giro_superior_nuevo ){
    *giro_helices_superiores = glm::rotate( giro_superior_nuevo, glm::vec3(0.0, 1.0, 0.0));
}

// -----------------------------------------------------------------------------

void Helicoptero::girar_helices_traseras( const float giro_atras_nuevo ){
    *giro_helices_traseras = glm::rotate( giro_atras_nuevo, glm::vec3(0.0, 0.0, 1.0));
}

// -----------------------------------------------------------------------------

void Helicoptero::elevar_helicoptero( const float h_nuevo ){
    *altura_helicoptero = glm::translate( glm::vec3(0.0, h_nuevo, 0.0) );
}

// -----------------------------------------------------------------------------

unsigned Helicoptero::calcula_lineal(const float t_sec){
    // a = vinicial
    // b = 2pi*w
    // w = velocidad angulan (ciclos/s)
    unsigned w = 0.2;
    unsigned a = 0;
    unsigned b = 2 * M_PI * w;

    return a+b*t_sec;
}

// -----------------------------------------------------------------------------

unsigned Helicoptero::calcula_oscilante(const float t_sec){
    // a = (vmax + vmin)/2
    // b = (vmin - vmax)/2
    // v = a + b*sin(2pint)
    unsigned vmax = 1.0;
    unsigned vmin = 0.1;
    float n = 10;

    unsigned a = (vmax + vmin)/2.0;
    unsigned b = (vmin - vmax)/2.0;

    return a+b*(sin(2*M_PI*n*t_sec));
}

// -----------------------------------------------------------------------------
