#ifndef LATAPEONES_HPP
#define LATAPEONES_HPP

#include "grafo-escena.h"
#include "malla-revol.h"
#include "malla-ind.h"

using namespace std;

class Lata : public NodoGrafoEscena {
    public:
        Lata(string textura);
};

class LataPeones : public NodoGrafoEscena {
    public:
        LataPeones();
};

#endif