#ifndef IG_MODELOJER_HPP
#define IG_MODELOJER_HPP

#include "grafo-escena.h"

class Helicoptero : public NodoGrafoEscena{
    // Constructor
    public:
        Helicoptero();
};

class HeliceSuperior : public NodoGrafoEscena{
    // Constructor
    public:
        HeliceSuperior();
};

class Cabina : public NodoGrafoEscena{
    // Constructor
    public:
        Cabina();
};

class HeliceTrasera : public NodoGrafoEscena{
    // Constructor
    public:
        HeliceTrasera();
};

class Base : public NodoGrafoEscena{
    // Constructor
    public:
        Base();
};

#endif
