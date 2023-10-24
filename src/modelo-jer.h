#ifndef IG_MODELOJER_HPP
#define IG_MODELOJER_HPP

#include "grafo-escena.h"

class Helicoptero : public NodoGrafoEscena{
    protected:
        glm::mat4 * giro_helices_superiores = nullptr, * giro_helices_traseras = nullptr, * altura_helicoptero = nullptr;
    public:
        /*
            Animaciones:
                -Giro Hélices Superiores (0)
                -Giro Hélices Traseras  (1)
                -Elevar Helicóptero (2)
        */
        Helicoptero(const float giro_superior_inicial, const float giro_atras_inicial, const float h_inicial);
        unsigned leerNumParametros() const ;
        void actualizarEstadoParametro( const unsigned iParam, const float t_sec );
        void girar_helices_superiores( const float giro_superior_nuevo );
        void girar_helices_traseras( const float giro_atras_nuevo);
        void elevar_helicoptero( const float h_nuevo );
        unsigned calcula_lineal(const float t_sec);
        unsigned calcula_oscilante(const float t_sec);
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
