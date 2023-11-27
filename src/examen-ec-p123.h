// Nombre: Juan Manuel, Apellidos: Aneas Franco, Titulación: (GIADE).
// email: juanmanuelaf@correo.ugr.es, DNI o pasaporte: 74542495R

#ifndef EXAMEN_EC_P123_HPP
#define EXAMEN_EC_P123_HPP

#include "malla-ind.h"
#include "grafo-escena.h"

class P1MallaCubo : public MallaInd
{
   public:
        P1MallaCubo();
};

class P2Rejilla : public MallaInd
{
   public:
      P2Rejilla(unsigned n, unsigned m);
};

class P3Cuadrado : public MallaInd
{
   public:
      P3Cuadrado();
};

class P3Caja : public NodoGrafoEscena
{
   protected:
      glm::mat4 * abrir_caja = nullptr, * movimiento_esfera = nullptr;
   public:
      P3Caja();
      unsigned leerNumParametros() const ;
      void actualizarEstadoParametro( const unsigned iParam, const float t_sec );
      float calcula_oscilante_eleva_esfera(const float t_sec);
      float calcula_oscilante_abre_caja(const float t_sec);
      void elevar_esfera( const float giro_superior_nuevo );
      void abre_caja( const float giro_atras_nuevo);
};

#endif