#ifndef IG_MODELOJER_HPP
#define IG_MODELOJER_HPP

#include "grafo-escena.h"

class C : public NodoGrafoEscena{
    // Constructor
    C();

    // métodos virtuales, relativos a los parámetros del objeto

    // Devuelve el número de parámetros de este objeto
    // (por defecto no hay ningún parámetro: devuelve 0)
    // (virtual: redefinir en clases derivadas)
    //
    // @return (unsigned) -- número de parámetros del objeto.
    //
    virtual unsigned leerNumParametros() const ;

    // Actualiza el valor de un parámetro a un instante de tiempo
    // (por defecto produce un error: número de parámetro fuera de rango, esto se debe
    // a que por defecto un objeto 3D declara tener 0 parámetros, y esta función no se
    // debe llamar, a no ser que se declaren tener más parámetros).
    // (virtual: redefinir en clases derivadas)
    //
    //  @param iParam (unsigned) -- índice del parámetro (entre 0 y numParametros()-1 )
    //  @param t_sec  (float)    -- tiempo en segundos desde el estado inicial
    //
    virtual void actualizarEstadoParametro( const unsigned iParam, const float t_sec );
};

#endif
