#include "latapeones.h"

Lata::Lata(string textura) {

    // Materiales y Texturas
    Textura * textura_pcue = new Textura(textura);
    Material * material_pcue = new Material(textura_pcue, 1.0, 1.0, 1.0, 100.0);

    Material * material_pinf = new Material(0.75, 0.5, 0.70, 50.0);

    Material * material_psup = new Material(0.75, 0.5, 0.70, 50.0);

    // Objetos
    MallaRevolPLY * cuerpo_lata = new MallaRevolPLY("lata-pcue.ply", 100);
    MallaRevolPLY * tapa_inferior_lata = new MallaRevolPLY("lata-pinf.ply", 100);
    MallaRevolPLY * tapa_superior_lata = new MallaRevolPLY("lata-psup.ply", 100);

    // Nodos
    NodoGrafoEscena * lata_pcue = new NodoGrafoEscena();
    lata_pcue->agregar(material_pcue);
    lata_pcue->agregar(cuerpo_lata);

    NodoGrafoEscena * lata_pinf = new NodoGrafoEscena();
    lata_pinf->agregar(material_pinf);
    lata_pinf->agregar(tapa_inferior_lata);

    NodoGrafoEscena * lata_psup = new NodoGrafoEscena();
    lata_psup->agregar(material_psup);
    lata_psup->agregar(tapa_superior_lata);

    agregar(lata_psup);
    agregar(lata_pinf);
    agregar(lata_pcue);
}

LataPeones::LataPeones() {

    ponerNombre( std::string("Grafo LataPeones") );

    // Identificadores
    int ident_lata_cola = 1;
    int ident_peon_madera = 2;
    int ident_peon_blanco = 3;
    int ident_peon_negro = 4;

    // Materiales y Texturas
    Material * material_blanco = new Material(0.1, 1.0, 0.0, 1.0);

    Material * material_negro = new Material(1.0, 0.3, 1.0, 5.0);

    Textura * textura_madera = new TexturaXY("text-madera.jpg");
    Material * material_madera = new Material(textura_madera, 0.25, 0.75, 1.0, 50.0);

    // Objetos
    MallaRevolPLY * peon = new MallaRevolPLY("peon.ply", 20);

    // Nodos
    NodoGrafoEscena * lata_cola = new Lata("lata-coke.jpg");
    lata_cola->ponerNombre("Lata de Coca-Cola");
    lata_cola->ponerIdentificador(ident_lata_cola);

    NodoGrafoEscena * peon_blanco = new NodoGrafoEscena();
    peon_blanco->ponerColor({1,1,1});
    peon_blanco->agregar(glm::translate(glm::vec3(0.5,0,1)));
    peon_blanco->agregar(glm::scale(glm::vec3(0.20,0.20,0.20)));
    peon_blanco->agregar(glm::translate(glm::vec3(0,1.4,0)));
    peon_blanco->agregar(material_blanco);
    peon_blanco->agregar(peon);
    peon_blanco->ponerNombre("Peón blanco");
    peon_blanco->ponerIdentificador(ident_peon_blanco);

    NodoGrafoEscena * peon_negro = new NodoGrafoEscena();
    peon_negro->ponerColor({0,0,0});
    peon_negro->agregar(glm::translate(glm::vec3(1,0,1)));
    peon_negro->agregar(glm::scale(glm::vec3(0.20,0.20,0.20)));
    peon_negro->agregar(glm::translate(glm::vec3(0,1.4,0)));
    peon_negro->agregar(material_negro);
    peon_negro->agregar(peon);
    peon_negro->ponerNombre("Peón negro");
    peon_negro->ponerIdentificador(ident_peon_negro);

    NodoGrafoEscena * peon_madera = new NodoGrafoEscena();
    peon_madera->agregar(glm::translate(glm::vec3(0,0,1)));
    peon_madera->agregar(glm::scale(glm::vec3(0.20,0.20,0.20)));
    peon_madera->agregar(glm::translate(glm::vec3(0,1.4,0)));
    peon_madera->agregar(material_madera);
    peon_madera->agregar(peon);
    peon_madera->ponerNombre("Peón de madera");
    peon_madera->ponerIdentificador(ident_peon_madera);
    
    agregar(peon_blanco);
    agregar(peon_negro);
    agregar(lata_cola);
    agregar(peon_madera);
}