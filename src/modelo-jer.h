#ifndef IG_MODELOJER_HPP
#define IG_MODELOJER_HPP

#include "grafo-escena.h"

class Helicoptero : public NodoGrafoEscena{
    protected:
        glm::mat4 * giro_helices_superiores = nullptr, * giro_helices_traseras = nullptr, * altura_lanzadera = nullptr;
    public:
        Helicoptero();
        unsigned leerNumParametros() const ;
        void actualizarEstadoParametro( const unsigned iParam, const float t_sec );
        void girar_helices_superiores( const float alpha_nuevo );
        void girar_helices_traseras( const float alpha_nuevo );
        void elevar_helicoptero( const float h_nuevo );
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
