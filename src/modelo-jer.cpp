// Nombre: Juan Manuel, Apellidos: Aneas Franco, Titulación: (GIADE).
// email: juanmanuelaf@correo.ugr.es, DNI o pasaporte: 74542495R

#include <iostream>
#include <modelo-jer.h>
#include <malla-revol.h>

using namespace std;

// -----------------------------------------------------------------------------

Helicoptero::Helicoptero(const float giro_superior, const float giro_atras, const float h, const float orient){
    giro_sup = giro_superior;
    giro_at = giro_atras;
    altura = h;
    orientacion = orient;

    unsigned ind4 = agregar( glm::scale(glm::vec3(1.1, 1.1, 1.1) ));
    orientacion_helicoptero = leerPtrMatriz(ind4);

    unsigned ind3 = agregar( glm::scale(glm::vec3(1.1, 1.1, 1.1) ));
    altura_helicoptero = leerPtrMatriz(ind3);

    NodoGrafoEscena * helice_sup = new NodoGrafoEscena();
    unsigned ind1 = helice_sup->agregar( glm::scale(glm::vec3(1.1, 1.1, 1.1) ));
    giro_helices_superiores = helice_sup->leerPtrMatriz(ind1);
    helice_sup->agregar( new HeliceSuperior() );

    NodoGrafoEscena * helice_trasera = new NodoGrafoEscena();
    helice_trasera->agregar( glm::translate( glm::vec3(-3.6, 0.8, 0.3) ) );
    unsigned ind2 = helice_trasera->agregar( glm::scale(glm::vec3(1.1, 1.1, 1.1) ));
    giro_helices_traseras = helice_trasera->leerPtrMatriz(ind2);
    helice_trasera->agregar( new HeliceTrasera() );

    agregar( new Cuerpo() );
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

Cuerpo::Cuerpo(){
    Cilindro * eje = new Cilindro(6,15);
    eje->ponerColor({0.15, 0.15, 0.15 });

    Cubo * ala = new Cubo();
    ala->ponerColor({0.6, 0.0, 0.0});

    Esfera * principal = new Esfera(20, 20);
    principal->ponerColor({0.6, 0.0, 0.0});

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

    NodoGrafoEscena * aleron = new NodoGrafoEscena();
    aleron->agregar( glm::translate( glm::vec3(-2.5, 0.7, 0.0) ) );
    aleron->agregar( glm::scale( glm::vec3(1.0, 0.2, 0.2) ));
    aleron->agregar( ala );

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
    agregar(aleron);
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
    conexion1->agregar( glm::rotate( float(glm::radians(-20.0)), glm::vec3( 1.0, 0.0, 0.0)) );
    conexion1->agregar( glm::scale( glm::vec3(0.1, 0.7, 0.1) ));
    conexion1->agregar( cilindro );

    NodoGrafoEscena * conexion2 = new NodoGrafoEscena();
    conexion2->agregar( glm::translate( glm::vec3(-0.4, -0.8, 0.5) ) );
    conexion2->agregar( glm::rotate( float(glm::radians(-20.0)), glm::vec3( 1.0, 0.0, 0.0)) );
    conexion2->agregar( glm::scale( glm::vec3(0.1, 0.7, 0.1) ));
    conexion2->agregar( cilindro );

    NodoGrafoEscena * conexion3 = new NodoGrafoEscena();
    conexion3->agregar( glm::translate( glm::vec3(0.4, -0.8, -0.5) ) );
    conexion3->agregar( glm::rotate( float(glm::radians(20.0)), glm::vec3( 1.0, 0.0, 0.0)) );
    conexion3->agregar( glm::scale( glm::vec3(0.1, 0.7, 0.1) ));
    conexion3->agregar( cilindro );

    NodoGrafoEscena * conexion4 = new NodoGrafoEscena();
    conexion4->agregar( glm::translate( glm::vec3(-0.4, -0.8, -0.5) ) );
    conexion4->agregar( glm::rotate( float(glm::radians(20.0)), glm::vec3( 1.0, 0.0, 0.0)) );
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
    return 4;
} 

// -----------------------------------------------------------------------------

void Helicoptero::actualizarEstadoParametro( const unsigned iParam, const float t_sec ){

    switch (iParam)
    {
        case 0: // Girar Helices Sup
            girar_helices_superiores(calcula_lineal_superior(t_sec));
            break;
        case 1: // Girar Helices Tra
            girar_helices_traseras(calcula_lineal_atras(t_sec));
            break;
        case 2: // Elevar Helicoptero
            elevar_helicoptero(calcula_oscilante_eleva(t_sec));
            break;
        case 3: // Orientar Helicóptero
            orientar_helicoptero(calcula_oscilante_orienta(t_sec));
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

void Helicoptero::orientar_helicoptero( const float orientacion_nueva ){
    *orientacion_helicoptero = glm::rotate( float(glm::radians(orientacion_nueva)), glm::vec3(0.0, 1.0, 0.0));
}

// -----------------------------------------------------------------------------

float Helicoptero::calcula_lineal_superior(const float t_sec){
    // a = vinicial
    // b = 2pi*w
    // w = velocidad angulan (ciclos/s)
    unsigned w = giro_sup;
    unsigned a = 0;
    unsigned b = 2 * M_PI * w;

    return a+b*t_sec;
}

// -----------------------------------------------------------------------------

float Helicoptero::calcula_lineal_atras(const float t_sec){
    // a = vinicial
    // b = 2pi*w
    // w = velocidad angulan (ciclos/s)
    unsigned w = giro_at;
    unsigned a = 0;
    unsigned b = 2 * M_PI * w;

    return a+b*t_sec;
}

// -----------------------------------------------------------------------------

float Helicoptero::calcula_oscilante_eleva(const float t_sec){
    // a = (vmax + vmin)/2
    // b = (vmin - vmax)/2
    // v = a + b*sin(2pint)
    float vmax = float(altura);
    float vmin = 0.0f;
    float n = 0.5f;

    float a = (vmax + vmin)/2.0;
    float b = (vmin - vmax)/2.0;

    return a+b*(sin(2*M_PI*n*t_sec));
}

// -----------------------------------------------------------------------------

float Helicoptero::calcula_oscilante_orienta(const float t_sec){
    // a = (vmax + vmin)/2
    // b = (vmin - vmax)/2
    // v = a + b*sin(2pint)

    float vmax = float(orientacion);
    float vmin = -float(orientacion);
    float n = 1.0f;

    float a = (vmax + vmin)/2.0;
    float b = (vmin - vmax)/2.0;

    return a+b*(sin(2*M_PI*n*t_sec));
}

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

HelicopteroP4::HelicopteroP4(const float giro_superior, const float giro_atras, const float h, const float orient){
    giro_sup = giro_superior;
    giro_at = giro_atras;
    altura = h;
    orientacion = orient;

    unsigned ind4 = agregar( glm::scale(glm::vec3(1.1, 1.1, 1.1) ));
    orientacion_helicoptero = leerPtrMatriz(ind4);

    unsigned ind3 = agregar( glm::scale(glm::vec3(1.1, 1.1, 1.1) ));
    altura_helicoptero = leerPtrMatriz(ind3);

    NodoGrafoEscena * helice_sup = new NodoGrafoEscena();
    unsigned ind1 = helice_sup->agregar( glm::scale(glm::vec3(1.1, 1.1, 1.1) ));
    giro_helices_superiores = helice_sup->leerPtrMatriz(ind1);
    helice_sup->agregar( new HeliceSuperiorP4() );

    NodoGrafoEscena * helice_trasera = new NodoGrafoEscena();
    helice_trasera->agregar( glm::translate( glm::vec3(-3.6, 0.8, 0.3) ) );
    unsigned ind2 = helice_trasera->agregar( glm::scale(glm::vec3(1.1, 1.1, 1.1) ));
    giro_helices_traseras = helice_trasera->leerPtrMatriz(ind2);
    helice_trasera->agregar( new HeliceTraseraP4() );

    agregar( new CuerpoP4() );
    agregar( new BaseP4() );
    agregar( helice_sup );
    agregar( helice_trasera );
}

// -----------------------------------------------------------------------------

HeliceSuperiorP4::HeliceSuperiorP4(){
    Cubo24 * aspa = new Cubo24();
    aspa->ponerColor({0.1, 0.1, 0.1 });

    Textura * textura_helice = new Textura("textura-helice.jpg");
    Material * material_helice = new Material(textura_helice, 0.25, 0.75, 1.0, 50.0);

    NodoGrafoEscena * helice = new NodoGrafoEscena();
    helice->agregar( glm::translate( glm::vec3(0.0, 2.0, 0.0) ) );
    helice->agregar( glm::scale( glm::vec3(3.0, 0.1, 0.2) ));
    helice->agregar(material_helice);
    helice->agregar( aspa );

    agregar(helice);
    agregar( glm::rotate( float(glm::radians(90.0)), glm::vec3( 0.0, 1.0, 0.0)));
    agregar(helice);
}

// -----------------------------------------------------------------------------

HeliceTraseraP4::HeliceTraseraP4(){
    Cubo24 * aspa = new Cubo24();
    aspa->ponerColor({0.1, 0.1, 0.1 });

    Textura * textura_helice = new Textura("textura-helice.jpg");
    Material * material_helice = new Material(textura_helice, 0.25, 0.75, 1.0, 50.0);

    NodoGrafoEscena * helice1 = new NodoGrafoEscena();
    helice1->agregar( glm::scale( glm::vec3(0.05, 0.4, 0.05) ));
    helice1->agregar(material_helice);
    helice1->agregar( aspa );

    NodoGrafoEscena * helice2 = new NodoGrafoEscena();
    helice2->agregar( glm::scale( glm::vec3(0.4, 0.05, 0.05) ));
    helice2->agregar(material_helice);
    helice2->agregar( aspa );
    
    agregar(helice1);
    agregar(helice2);
}

// -----------------------------------------------------------------------------

CuerpoP4::CuerpoP4(){
    CilindroP4 * eje = new CilindroP4(6,15);
    eje->ponerColor({0.15, 0.15, 0.15 });

    Cubo24 * ala = new Cubo24();
    ala->ponerColor({0.6, 0.0, 0.0});

    Esfera * principal = new Esfera(20, 20);
    principal->ponerColor({0.6, 0.0, 0.0});

    Cubo24 * frente = new Cubo24();
    frente->ponerColor({0.1, 0.7, 0.9});

    Textura * textura_eje = new Textura("textura-eje.jpg");
    Material * material_eje = new Material(textura_eje, 0.25, 0.75, 1.0, 50.0);

    NodoGrafoEscena * ejeHelicesSup = new NodoGrafoEscena();
    ejeHelicesSup->agregar( glm::translate( glm::vec3(0.0, 1.7, 0.0) ) );
    ejeHelicesSup->agregar( glm::scale( glm::vec3(0.1, 0.5, 0.1) ));
    ejeHelicesSup->agregar(material_eje);
    ejeHelicesSup->agregar( eje );

    Textura * textura_cabina = new TexturaXY("textura-cuerpo.jpg");
    Material * material_cabina = new Material(textura_cabina, 0.25, 0.75, 1.0, 50.0);

    NodoGrafoEscena * cabina = new NodoGrafoEscena();
    cabina->agregar( glm::translate( glm::vec3(0.0, 0.7, 0.0) ) );
    cabina->agregar( glm::scale( glm::vec3(2.0, 1.0, 1.0) ));
    cabina->agregar ( material_cabina );
    cabina->agregar( principal );

    Textura * textura_ala = new Textura("textura-ala.jpg");
    Material * material_ala = new Material(textura_ala, 0.25, 0.75, 1.0, 50.0);

    NodoGrafoEscena * aleron = new NodoGrafoEscena();
    aleron->agregar( glm::translate( glm::vec3(-2.5, 0.7, 0.0) ) );
    aleron->agregar( glm::scale( glm::vec3(1.0, 0.2, 0.2) ));
    aleron->agregar ( material_ala );
    aleron->agregar( ala );

    NodoGrafoEscena * extremo = new NodoGrafoEscena();
    extremo->agregar( glm::translate( glm::vec3(-3.7, 0.8, 0.0) ) );
    extremo->agregar( glm::scale( glm::vec3(0.2, 0.5, 0.2) ));
    extremo->agregar( material_ala );
    extremo->agregar( ala );

    NodoGrafoEscena * ejeHelicesTra = new NodoGrafoEscena();
    ejeHelicesTra->agregar( glm::translate( glm::vec3(-3.6, 0.8, 0.0) ) );
    ejeHelicesTra->agregar( glm::scale( glm::vec3(0.05, 0.05, 0.4) ));
    ejeHelicesTra->agregar( glm::rotate( float(glm::radians(90.0)), glm::vec3( 1.0, 0.0, 0.0)) );
    ejeHelicesTra->agregar(material_eje);
    ejeHelicesTra->agregar( eje );

    Textura * textura_ventana = new Textura("textura-ventana.jpg");
    Material * material_ventana = new Material(textura_ventana , 1.0, 1.0, 1.0, 50.0);

    NodoGrafoEscena * ventana = new NodoGrafoEscena();
    ventana->agregar( glm::translate( glm::vec3(1.8, 0.8, 0.0) ) );
    ventana->agregar( glm::scale( glm::vec3(0.2, 0.3, 0.4) ));
    ventana->agregar( material_ventana );
    ventana->agregar( frente );

    agregar(ejeHelicesSup);
    agregar(ejeHelicesTra);
    agregar(aleron);
    agregar(extremo);
    agregar(cabina);
    agregar(ventana);
}

// -----------------------------------------------------------------------------

BaseP4::BaseP4(){
    Textura * textura_base = new TexturaXY("textura-base.jpg");
    Material * material_base = new Material(textura_base, 0.25, 0.75, 1.0, 50.0);

    CilindroP4 * cilindro = new CilindroP4(6,15);
    cilindro->ponerColor({0.1, 0.2, 0.2 });

    NodoGrafoEscena * apoyo1 = new NodoGrafoEscena();
    apoyo1->agregar( glm::translate( glm::vec3(1.0, -0.8, 0.5) ) );
    apoyo1->agregar( glm::scale( glm::vec3(2.0, 0.15, 0.15) ));
    apoyo1->agregar( glm::rotate( float(glm::radians(90.0)), glm::vec3( 0.0, 0.0, 1.0)) );
    apoyo1->agregar( material_base );
    apoyo1->agregar( cilindro );

    NodoGrafoEscena * apoyo2 = new NodoGrafoEscena();
    apoyo2->agregar( glm::translate( glm::vec3(1.0, -0.8, -0.5) ) );
    apoyo2->agregar( glm::scale( glm::vec3(2.0, 0.15, 0.15) ));
    apoyo2->agregar( glm::rotate( float(glm::radians(90.0)), glm::vec3( 0.0, 0.0, 1.0)) );
    apoyo2->agregar( material_base );
    apoyo2->agregar( cilindro );

    NodoGrafoEscena * conexion1 = new NodoGrafoEscena();
    conexion1->agregar( glm::translate( glm::vec3(0.4, -0.8, 0.5) ) );
    conexion1->agregar( glm::rotate( float(glm::radians(-20.0)), glm::vec3( 1.0, 0.0, 0.0)) );
    conexion1->agregar( glm::scale( glm::vec3(0.1, 0.7, 0.1) ));
    conexion1->agregar( material_base );
    conexion1->agregar( cilindro );

    NodoGrafoEscena * conexion2 = new NodoGrafoEscena();
    conexion2->agregar( glm::translate( glm::vec3(-0.4, -0.8, 0.5) ) );
    conexion2->agregar( glm::rotate( float(glm::radians(-20.0)), glm::vec3( 1.0, 0.0, 0.0)) );
    conexion2->agregar( glm::scale( glm::vec3(0.1, 0.7, 0.1) ));
    conexion2->agregar( material_base );
    conexion2->agregar( cilindro );

    NodoGrafoEscena * conexion3 = new NodoGrafoEscena();
    conexion3->agregar( glm::translate( glm::vec3(0.4, -0.8, -0.5) ) );
    conexion3->agregar( glm::rotate( float(glm::radians(20.0)), glm::vec3( 1.0, 0.0, 0.0)) );
    conexion3->agregar( glm::scale( glm::vec3(0.1, 0.7, 0.1) ));
    conexion3->agregar( material_base );
    conexion3->agregar( cilindro );

    NodoGrafoEscena * conexion4 = new NodoGrafoEscena();
    conexion4->agregar( glm::translate( glm::vec3(-0.4, -0.8, -0.5) ) );
    conexion4->agregar( glm::rotate( float(glm::radians(20.0)), glm::vec3( 1.0, 0.0, 0.0)) );
    conexion4->agregar( glm::scale( glm::vec3(0.1, 0.7, 0.1) ));
    conexion4->agregar( material_base );
    conexion4->agregar( cilindro );
    
    agregar(apoyo1);
    agregar(apoyo2);
    agregar(conexion1);
    agregar(conexion2);
    agregar(conexion3);
    agregar(conexion4);
}

// -----------------------------------------------------------------------------

unsigned HelicopteroP4::leerNumParametros() const{
    return 4;
} 

// -----------------------------------------------------------------------------

void HelicopteroP4::actualizarEstadoParametro( const unsigned iParam, const float t_sec ){

    switch (iParam)
    {
        case 0: // Girar Helices Sup
            girar_helices_superiores(calcula_lineal_superior(t_sec));
            break;
        case 1: // Girar Helices Tra
            girar_helices_traseras(calcula_lineal_atras(t_sec));
            break;
        case 2: // Elevar Helicoptero
            elevar_helicoptero(calcula_oscilante_eleva(t_sec));
            break;
        case 3: // Orientar Helicóptero
            orientar_helicoptero(calcula_oscilante_orienta(t_sec));
            break;
        default:
            break;
    }
}

// -----------------------------------------------------------------------------

void HelicopteroP4::girar_helices_superiores( const float giro_superior_nuevo ){
    *giro_helices_superiores = glm::rotate( giro_superior_nuevo, glm::vec3(0.0, 1.0, 0.0));
}

// -----------------------------------------------------------------------------

void HelicopteroP4::girar_helices_traseras( const float giro_atras_nuevo ){
    *giro_helices_traseras = glm::rotate( giro_atras_nuevo, glm::vec3(0.0, 0.0, 1.0));
}

// -----------------------------------------------------------------------------

void HelicopteroP4::elevar_helicoptero( const float h_nuevo ){
    *altura_helicoptero = glm::translate( glm::vec3(0.0, h_nuevo, 0.0) );
}

// -----------------------------------------------------------------------------

void HelicopteroP4::orientar_helicoptero( const float orientacion_nueva ){
    *orientacion_helicoptero = glm::rotate( float(glm::radians(orientacion_nueva)), glm::vec3(0.0, 1.0, 0.0));
}

// -----------------------------------------------------------------------------

float HelicopteroP4::calcula_lineal_superior(const float t_sec){
    // a = vinicial
    // b = 2pi*w
    // w = velocidad angulan (ciclos/s)
    unsigned w = giro_sup;
    unsigned a = 0;
    unsigned b = 2 * M_PI * w;

    return a+b*t_sec;
}

// -----------------------------------------------------------------------------

float HelicopteroP4::calcula_lineal_atras(const float t_sec){
    // a = vinicial
    // b = 2pi*w
    // w = velocidad angulan (ciclos/s)
    unsigned w = giro_at;
    unsigned a = 0;
    unsigned b = 2 * M_PI * w;

    return a+b*t_sec;
}

// -----------------------------------------------------------------------------

float HelicopteroP4::calcula_oscilante_eleva(const float t_sec){
    // a = (vmax + vmin)/2
    // b = (vmin - vmax)/2
    // v = a + b*sin(2pint)
    float vmax = float(altura);
    float vmin = 0.0f;
    float n = 0.5f;

    float a = (vmax + vmin)/2.0;
    float b = (vmin - vmax)/2.0;

    return a+b*(sin(2*M_PI*n*t_sec));
}

// -----------------------------------------------------------------------------

float HelicopteroP4::calcula_oscilante_orienta(const float t_sec){
    // a = (vmax + vmin)/2
    // b = (vmin - vmax)/2
    // v = a + b*sin(2pint)

    float vmax = float(orientacion);
    float vmin = -float(orientacion);
    float n = 1.0f;

    float a = (vmax + vmin)/2.0;
    float b = (vmin - vmax)/2.0;

    return a+b*(sin(2*M_PI*n*t_sec));
}

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

HelicopteroP5::HelicopteroP5(const float giro_superior, const float giro_atras, const float h, const float orient){
    giro_sup = giro_superior;
    giro_at = giro_atras;
    altura = h;
    orientacion = orient;

    // Identificadores
    int ident_helice_sup = 1;
    int ident_helice_tra = 2;
    int ident_cuerpo = 3;
    int ident_base = 4;

    unsigned ind4 = agregar( glm::scale(glm::vec3(1.1, 1.1, 1.1) ));
    orientacion_helicoptero = leerPtrMatriz(ind4);

    unsigned ind3 = agregar( glm::scale(glm::vec3(1.1, 1.1, 1.1) ));
    altura_helicoptero = leerPtrMatriz(ind3);

    NodoGrafoEscena * helice_sup = new NodoGrafoEscena();
    unsigned ind1 = helice_sup->agregar( glm::scale(glm::vec3(1.1, 1.1, 1.1) ));
    giro_helices_superiores = helice_sup->leerPtrMatriz(ind1);
    helice_sup->ponerNombre("Hélice Superior");
    helice_sup->ponerIdentificador(ident_helice_sup);
    helice_sup->agregar( new HeliceSuperiorP4() );

    NodoGrafoEscena * helice_trasera = new NodoGrafoEscena();
    helice_trasera->agregar( glm::translate( glm::vec3(-3.6, 0.8, 0.3) ) );
    unsigned ind2 = helice_trasera->agregar( glm::scale(glm::vec3(1.1, 1.1, 1.1) ));
    giro_helices_traseras = helice_trasera->leerPtrMatriz(ind2);
    helice_trasera->ponerNombre("Hélice Trasera");
    helice_trasera->ponerIdentificador(ident_helice_tra);
    helice_trasera->agregar( new HeliceTraseraP4() );

    NodoGrafoEscena * cuerpo = new NodoGrafoEscena();
    cuerpo->ponerNombre("Cuerpo");
    cuerpo->ponerIdentificador(ident_cuerpo);
    cuerpo->agregar( new CuerpoP5() );

    NodoGrafoEscena * base = new NodoGrafoEscena();
    base->ponerNombre("Base");
    base->ponerIdentificador(ident_base);
    base->agregar( new BaseP5() );

    agregar( cuerpo );
    agregar( base );
    agregar( helice_sup );
    agregar( helice_trasera );
}

// -----------------------------------------------------------------------------

HeliceSuperiorP5::HeliceSuperiorP5(){
    Cubo24 * aspa = new Cubo24();
    aspa->ponerColor({0.1, 0.1, 0.1 });

    Textura * textura_helice = new Textura("textura-helice.jpg");
    Material * material_helice = new Material(textura_helice, 0.25, 0.75, 1.0, 50.0);

    NodoGrafoEscena * helice = new NodoGrafoEscena();
    helice->agregar( glm::translate( glm::vec3(0.0, 2.0, 0.0) ) );
    helice->agregar( glm::scale( glm::vec3(3.0, 0.1, 0.2) ));
    helice->agregar(material_helice);
    helice->agregar( aspa );

    agregar(helice);
    agregar( glm::rotate( float(glm::radians(90.0)), glm::vec3( 0.0, 1.0, 0.0)));
    agregar(helice);
}

// -----------------------------------------------------------------------------

HeliceTraseraP5::HeliceTraseraP5(){
    Cubo24 * aspa = new Cubo24();
    aspa->ponerColor({0.1, 0.1, 0.1 });

    Textura * textura_helice = new Textura("textura-helice.jpg");
    Material * material_helice = new Material(textura_helice, 0.25, 0.75, 1.0, 50.0);

    NodoGrafoEscena * helice1 = new NodoGrafoEscena();
    helice1->agregar( glm::scale( glm::vec3(0.05, 0.4, 0.05) ));
    helice1->agregar(material_helice);
    helice1->agregar( aspa );

    NodoGrafoEscena * helice2 = new NodoGrafoEscena();
    helice2->agregar( glm::scale( glm::vec3(0.4, 0.05, 0.05) ));
    helice2->agregar(material_helice);
    helice2->agregar( aspa );
    
    agregar(helice1);
    agregar(helice2);
}

// -----------------------------------------------------------------------------

CuerpoP5::CuerpoP5(){
    CilindroP4 * eje = new CilindroP4(6,15);
    eje->ponerColor({0.15, 0.15, 0.15 });

    Cubo24 * ala = new Cubo24();
    ala->ponerColor({0.6, 0.0, 0.0});

    Esfera * principal = new Esfera(20, 20);
    principal->ponerColor({0.6, 0.0, 0.0});

    Cubo24 * frente = new Cubo24();
    frente->ponerColor({0.1, 0.7, 0.9});

    Textura * textura_eje = new Textura("textura-eje.jpg");
    Material * material_eje = new Material(textura_eje, 0.25, 0.75, 1.0, 50.0);

    NodoGrafoEscena * ejeHelicesSup = new NodoGrafoEscena();
    ejeHelicesSup->agregar( glm::translate( glm::vec3(0.0, 1.7, 0.0) ) );
    ejeHelicesSup->agregar( glm::scale( glm::vec3(0.1, 0.5, 0.1) ));
    ejeHelicesSup->agregar(material_eje);
    ejeHelicesSup->agregar( eje );

    Textura * textura_cabina = new TexturaXY("textura-cuerpo.jpg");
    Material * material_cabina = new Material(textura_cabina, 0.25, 0.75, 1.0, 50.0);

    NodoGrafoEscena * cabina = new NodoGrafoEscena();
    cabina->agregar( glm::translate( glm::vec3(0.0, 0.7, 0.0) ) );
    cabina->agregar( glm::scale( glm::vec3(2.0, 1.0, 1.0) ));
    cabina->agregar ( material_cabina );
    cabina->agregar( principal );

    Textura * textura_ala = new Textura("textura-ala.jpg");
    Material * material_ala = new Material(textura_ala, 0.25, 0.75, 1.0, 50.0);

    NodoGrafoEscena * aleron = new NodoGrafoEscena();
    aleron->agregar( glm::translate( glm::vec3(-2.5, 0.7, 0.0) ) );
    aleron->agregar( glm::scale( glm::vec3(1.0, 0.2, 0.2) ));
    aleron->agregar ( material_ala );
    aleron->agregar( ala );

    NodoGrafoEscena * extremo = new NodoGrafoEscena();
    extremo->agregar( glm::translate( glm::vec3(-3.7, 0.8, 0.0) ) );
    extremo->agregar( glm::scale( glm::vec3(0.2, 0.5, 0.2) ));
    extremo->agregar( material_ala );
    extremo->agregar( ala );

    NodoGrafoEscena * ejeHelicesTra = new NodoGrafoEscena();
    ejeHelicesTra->agregar( glm::translate( glm::vec3(-3.6, 0.8, 0.0) ) );
    ejeHelicesTra->agregar( glm::scale( glm::vec3(0.05, 0.05, 0.4) ));
    ejeHelicesTra->agregar( glm::rotate( float(glm::radians(90.0)), glm::vec3( 1.0, 0.0, 0.0)) );
    ejeHelicesTra->agregar(material_eje);
    ejeHelicesTra->agregar( eje );

    Textura * textura_ventana = new Textura("textura-ventana.jpg");
    Material * material_ventana = new Material(textura_ventana , 1.0, 1.0, 1.0, 50.0);

    NodoGrafoEscena * ventana = new NodoGrafoEscena();
    ventana->agregar( glm::translate( glm::vec3(1.8, 0.8, 0.0) ) );
    ventana->agregar( glm::scale( glm::vec3(0.2, 0.3, 0.4) ));
    ventana->agregar( material_ventana );
    ventana->agregar( frente );

    agregar(ejeHelicesSup);
    agregar(ejeHelicesTra);
    agregar(aleron);
    agregar(extremo);
    agregar(cabina);
    agregar(ventana);
}

// -----------------------------------------------------------------------------

BaseP5::BaseP5(){
    Textura * textura_base = new TexturaXY("textura-base.jpg");
    Material * material_base = new Material(textura_base, 0.25, 0.75, 1.0, 50.0);

    CilindroP4 * cilindro = new CilindroP4(6,15);
    cilindro->ponerColor({0.1, 0.2, 0.2 });

    NodoGrafoEscena * apoyo1 = new NodoGrafoEscena();
    apoyo1->agregar( glm::translate( glm::vec3(1.0, -0.8, 0.5) ) );
    apoyo1->agregar( glm::scale( glm::vec3(2.0, 0.15, 0.15) ));
    apoyo1->agregar( glm::rotate( float(glm::radians(90.0)), glm::vec3( 0.0, 0.0, 1.0)) );
    apoyo1->agregar( material_base );
    apoyo1->agregar( cilindro );

    NodoGrafoEscena * apoyo2 = new NodoGrafoEscena();
    apoyo2->agregar( glm::translate( glm::vec3(1.0, -0.8, -0.5) ) );
    apoyo2->agregar( glm::scale( glm::vec3(2.0, 0.15, 0.15) ));
    apoyo2->agregar( glm::rotate( float(glm::radians(90.0)), glm::vec3( 0.0, 0.0, 1.0)) );
    apoyo2->agregar( material_base );
    apoyo2->agregar( cilindro );

    NodoGrafoEscena * conexion1 = new NodoGrafoEscena();
    conexion1->agregar( glm::translate( glm::vec3(0.4, -0.8, 0.5) ) );
    conexion1->agregar( glm::rotate( float(glm::radians(-20.0)), glm::vec3( 1.0, 0.0, 0.0)) );
    conexion1->agregar( glm::scale( glm::vec3(0.1, 0.7, 0.1) ));
    conexion1->agregar( material_base );
    conexion1->agregar( cilindro );

    NodoGrafoEscena * conexion2 = new NodoGrafoEscena();
    conexion2->agregar( glm::translate( glm::vec3(-0.4, -0.8, 0.5) ) );
    conexion2->agregar( glm::rotate( float(glm::radians(-20.0)), glm::vec3( 1.0, 0.0, 0.0)) );
    conexion2->agregar( glm::scale( glm::vec3(0.1, 0.7, 0.1) ));
    conexion2->agregar( material_base );
    conexion2->agregar( cilindro );

    NodoGrafoEscena * conexion3 = new NodoGrafoEscena();
    conexion3->agregar( glm::translate( glm::vec3(0.4, -0.8, -0.5) ) );
    conexion3->agregar( glm::rotate( float(glm::radians(20.0)), glm::vec3( 1.0, 0.0, 0.0)) );
    conexion3->agregar( glm::scale( glm::vec3(0.1, 0.7, 0.1) ));
    conexion3->agregar( material_base );
    conexion3->agregar( cilindro );

    NodoGrafoEscena * conexion4 = new NodoGrafoEscena();
    conexion4->agregar( glm::translate( glm::vec3(-0.4, -0.8, -0.5) ) );
    conexion4->agregar( glm::rotate( float(glm::radians(20.0)), glm::vec3( 1.0, 0.0, 0.0)) );
    conexion4->agregar( glm::scale( glm::vec3(0.1, 0.7, 0.1) ));
    conexion4->agregar( material_base );
    conexion4->agregar( cilindro );
    
    agregar(apoyo1);
    agregar(apoyo2);
    agregar(conexion1);
    agregar(conexion2);
    agregar(conexion3);
    agregar(conexion4);
}

// -----------------------------------------------------------------------------

unsigned HelicopteroP5::leerNumParametros() const{
    return 4;
} 

// -----------------------------------------------------------------------------

void HelicopteroP5::actualizarEstadoParametro( const unsigned iParam, const float t_sec ){

    switch (iParam)
    {
        case 0: // Girar Helices Sup
            girar_helices_superiores(calcula_lineal_superior(t_sec));
            break;
        case 1: // Girar Helices Tra
            girar_helices_traseras(calcula_lineal_atras(t_sec));
            break;
        case 2: // Elevar Helicoptero
            elevar_helicoptero(calcula_oscilante_eleva(t_sec));
            break;
        case 3: // Orientar Helicóptero
            orientar_helicoptero(calcula_oscilante_orienta(t_sec));
            break;
        default:
            break;
    }
}

// -----------------------------------------------------------------------------

void HelicopteroP5::girar_helices_superiores( const float giro_superior_nuevo ){
    *giro_helices_superiores = glm::rotate( giro_superior_nuevo, glm::vec3(0.0, 1.0, 0.0));
}

// -----------------------------------------------------------------------------

void HelicopteroP5::girar_helices_traseras( const float giro_atras_nuevo ){
    *giro_helices_traseras = glm::rotate( giro_atras_nuevo, glm::vec3(0.0, 0.0, 1.0));
}

// -----------------------------------------------------------------------------

void HelicopteroP5::elevar_helicoptero( const float h_nuevo ){
    *altura_helicoptero = glm::translate( glm::vec3(0.0, h_nuevo, 0.0) );
}

// -----------------------------------------------------------------------------

void HelicopteroP5::orientar_helicoptero( const float orientacion_nueva ){
    *orientacion_helicoptero = glm::rotate( float(glm::radians(orientacion_nueva)), glm::vec3(0.0, 1.0, 0.0));
}

// -----------------------------------------------------------------------------

float HelicopteroP5::calcula_lineal_superior(const float t_sec){
    // a = vinicial
    // b = 2pi*w
    // w = velocidad angulan (ciclos/s)
    unsigned w = giro_sup;
    unsigned a = 0;
    unsigned b = 2 * M_PI * w;

    return a+b*t_sec;
}

// -----------------------------------------------------------------------------

float HelicopteroP5::calcula_lineal_atras(const float t_sec){
    // a = vinicial
    // b = 2pi*w
    // w = velocidad angulan (ciclos/s)
    unsigned w = giro_at;
    unsigned a = 0;
    unsigned b = 2 * M_PI * w;

    return a+b*t_sec;
}

// -----------------------------------------------------------------------------

float HelicopteroP5::calcula_oscilante_eleva(const float t_sec){
    // a = (vmax + vmin)/2
    // b = (vmin - vmax)/2
    // v = a + b*sin(2pint)
    float vmax = float(altura);
    float vmin = 0.0f;
    float n = 0.5f;

    float a = (vmax + vmin)/2.0;
    float b = (vmin - vmax)/2.0;

    return a+b*(sin(2*M_PI*n*t_sec));
}

// -----------------------------------------------------------------------------

float HelicopteroP5::calcula_oscilante_orienta(const float t_sec){
    // a = (vmax + vmin)/2
    // b = (vmin - vmax)/2
    // v = a + b*sin(2pint)

    float vmax = float(orientacion);
    float vmin = -float(orientacion);
    float n = 1.0f;

    float a = (vmax + vmin)/2.0;
    float b = (vmin - vmax)/2.0;

    return a+b*(sin(2*M_PI*n*t_sec));
}

// -----------------------------------------------------------------------------