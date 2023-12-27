// Nombre: Juan Manuel, Apellidos: Aneas Franco, Titulación: (GIADE).
// email: juanmanuelaf@correo.ugr.es, DNI o pasaporte: 74542495R

#ifndef IG_MODELOJER_HPP
#define IG_MODELOJER_HPP

#include "grafo-escena.h"

class Helicoptero : public NodoGrafoEscena{
        
    protected:
        glm::mat4 * giro_helices_superiores = nullptr, * giro_helices_traseras = nullptr, * altura_helicoptero = nullptr, * orientacion_helicoptero = nullptr;
        float giro_sup;
        float giro_at;
        float altura;
        float orientacion;
    public:
        /*
            Animaciones:
                -Giro Hélices Superiores (0)
                -Giro Hélices Traseras  (1)
                -Elevar Helicóptero (2)
        */
        Helicoptero(const float giro_superior, const float giro_atras, const float h, const float orient);
        unsigned leerNumParametros() const ;
        void actualizarEstadoParametro( const unsigned iParam, const float t_sec );
        void girar_helices_superiores( const float giro_superior_nuevo );
        void girar_helices_traseras( const float giro_atras_nuevo);
        void elevar_helicoptero( const float h_nuevo );
        void orientar_helicoptero( const float orientacion_nueva );
        float calcula_lineal_superior(const float t_sec);
        float calcula_lineal_atras(const float t_sec);
        float calcula_oscilante_eleva(const float t_sec);
        float calcula_oscilante_orienta(const float t_sec);
};

class HeliceSuperior : public NodoGrafoEscena{
    // Constructor
    public:
        HeliceSuperior();
};

class Cuerpo : public NodoGrafoEscena{
    // Constructor
    public:
        Cuerpo();
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

class HelicopteroP4 : public NodoGrafoEscena{
        
    protected:
        glm::mat4 * giro_helices_superiores = nullptr, * giro_helices_traseras = nullptr, * altura_helicoptero = nullptr, * orientacion_helicoptero = nullptr;
        float giro_sup;
        float giro_at;
        float altura;
        float orientacion;
    public:
        /*
            Animaciones:
                -Giro Hélices Superiores (0)
                -Giro Hélices Traseras  (1)
                -Elevar Helicóptero (2)
        */
        HelicopteroP4(const float giro_superior, const float giro_atras, const float h, const float orient);
        unsigned leerNumParametros() const ;
        void actualizarEstadoParametro( const unsigned iParam, const float t_sec );
        void girar_helices_superiores( const float giro_superior_nuevo );
        void girar_helices_traseras( const float giro_atras_nuevo);
        void elevar_helicoptero( const float h_nuevo );
        void orientar_helicoptero( const float orientacion_nueva );
        float calcula_lineal_superior(const float t_sec);
        float calcula_lineal_atras(const float t_sec);
        float calcula_oscilante_eleva(const float t_sec);
        float calcula_oscilante_orienta(const float t_sec);
};

class HeliceSuperiorP4 : public NodoGrafoEscena{
    // Constructor
    public:
        HeliceSuperiorP4();
};

class CuerpoP4 : public NodoGrafoEscena{
    // Constructor
    public:
        CuerpoP4();
};

class HeliceTraseraP4 : public NodoGrafoEscena{
    // Constructor
    public:
        HeliceTraseraP4();
};

class BaseP4 : public NodoGrafoEscena{
    // Constructor
    public:
        BaseP4();
};

class HelicopteroP5 : public NodoGrafoEscena{
        
    protected:
        glm::mat4 * giro_helices_superiores = nullptr, * giro_helices_traseras = nullptr, * altura_helicoptero = nullptr, * orientacion_helicoptero = nullptr;
        float giro_sup;
        float giro_at;
        float altura;
        float orientacion;
    public:
        /*
            Animaciones:
                -Giro Hélices Superiores (0)
                -Giro Hélices Traseras  (1)
                -Elevar Helicóptero (2)
        */
        HelicopteroP5(const float giro_superior, const float giro_atras, const float h, const float orient);
        unsigned leerNumParametros() const ;
        void actualizarEstadoParametro( const unsigned iParam, const float t_sec );
        void girar_helices_superiores( const float giro_superior_nuevo );
        void girar_helices_traseras( const float giro_atras_nuevo);
        void elevar_helicoptero( const float h_nuevo );
        void orientar_helicoptero( const float orientacion_nueva );
        float calcula_lineal_superior(const float t_sec);
        float calcula_lineal_atras(const float t_sec);
        float calcula_oscilante_eleva(const float t_sec);
        float calcula_oscilante_orienta(const float t_sec);
};

class HeliceSuperiorP5 : public NodoGrafoEscena{
    // Constructor
    public:
        HeliceSuperiorP5();
};

class CuerpoP5 : public NodoGrafoEscena{
    // Constructor
    public:
        CuerpoP5();
};

class HeliceTraseraP5 : public NodoGrafoEscena{
    // Constructor
    public:
        HeliceTraseraP5();
};

class BaseP5 : public NodoGrafoEscena{
    // Constructor
    public:
        BaseP5();
};

#endif
