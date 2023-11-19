// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Mallas indexadas (implementación)
// ** Copyright (C) 2016-2023 Carlos Ureña
// **
// ** Implementación de las clases 
// **    + MallaRevol: malla indexada de triángulos obtenida por 
// **      revolución de un perfil (derivada de MallaInd)
// **    + MallaRevolPLY: malla indexada de triángulos, obtenida 
// **      por revolución de un perfil leído de un PLY (derivada de MallaRevol)
// **    + algunas clases derivadas de MallaRevol
// **
// ** This program is free software: you can redistribute it and/or modify
// ** it under the terms of the GNU General Public License as published by
// ** the Free Software Foundation, either version 3 of the License, or
// ** (at your option) any later version.
// **
// ** This program is distributed in the hope that it will be useful,
// ** but WITHOUT ANY WARRANTY; without even the implied warranty of
// ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// ** GNU General Public License for more details.
// **
// ** You should have received a copy of the GNU General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **
// *********************************************************************

#include "ig-aux.h"
#include "lector-ply.h"
#include "malla-revol.h"

using namespace std ;

// *****************************************************************************




// Método que crea las tablas de vértices, triángulos, normales y cc.de.tt.
// a partir de un perfil y el número de copias que queremos de dicho perfil.
void MallaRevol::inicializar
(
   const std::vector<glm::vec3> & perfil,     // tabla de vértices del perfil original
   const unsigned               num_copias  // número de copias del perfil
)
{
   using namespace glm ;
   
   // COMPLETAR: práctica 2: implementar algoritmo de creación de malla de revolución
   //
   // Escribir el algoritmo de creación de una malla indexada por revolución de un 
   // perfil, según se describe en el guion de prácticas.
   //
   // ............................... 

   //Creación Tabla vértices
   unsigned n = num_copias;
   unsigned m = perfil.size();

   for (unsigned i = 0; i < n; ++i){
      for(unsigned j = 0; j < m; ++j){
         float angulo = 2 * M_PI * i / (n - 1);
         float r = perfil[j].x;

         // Rotar el vértice alrededor del eje Y
         float x_rotado = r * cos(angulo);
         float z_rotado = -r * sin(angulo);

         // Agregar el vértice a la tabla de vértices como un vector [x, 0, z]
         vertices.push_back({x_rotado, perfil[j].y, z_rotado});
      }
   }

   //Creación Tabla triángulos
   for(unsigned i = 0; i < n-1; ++i){
      for(unsigned j = 0; j < m-1; ++j){
         int k = i * m + j;

         // Añadir triángulo formado por los índices k, k + m y k + m + 1
         triangulos.push_back({k, k + m, k + m + 1});

         // Añadir triángulo formado por los índices k, k + m + 1 y k + 1
         triangulos.push_back({k, k + m + 1, k + 1});
      }
   }
}

// -----------------------------------------------------------------------------
// constructor, a partir de un archivo PLY

MallaRevolPLY::MallaRevolPLY
(
   const std::string & nombre_arch,
   const unsigned      nperfiles
)
{
   ponerNombre( std::string("malla por revolución del perfil en '"+ nombre_arch + "'" ));
   // COMPLETAR: práctica 2: crear la malla de revolución
   // Leer los vértice del perfil desde un PLY, después llamar a 'inicializar'
   // ...........................

   std::vector<glm::vec3> perfil;

   LeerVerticesPLY(nombre_arch, perfil);
   inicializar(perfil,nperfiles);
}

// Clase Cilindro

Cilindro::Cilindro(const int num_verts_per, const unsigned nperfiles)
:  MallaRevol()
{
   std::vector<glm::vec3> perfil;
   float altura = 1.0f;
   float radio = 1.0f;
   float altura_norm = altura / (num_verts_per - 3);


   perfil.push_back({0.0,0.0,0.0});

   for(int i = 0; i < num_verts_per - 2; ++i){
      perfil.push_back({radio, altura_norm * i, 0.0});
   }

   perfil.push_back({0.0, altura,0.0});

   inicializar(perfil, nperfiles);
}


// Clase Cono

Cono::Cono(const int num_verts_per, const unsigned nperfiles)
:  MallaRevol()
{
   std::vector<glm::vec3> perfil;
   float altura = 1.0f;
   float radio = 1.0f;
   float altura_norm = altura / (num_verts_per - 2);
   float radio_norm = radio / (num_verts_per - 2);

   perfil.push_back({0.0,0.0,0.0});

   for(int i = 0; i < num_verts_per - 2; ++i){
      perfil.push_back({radio - radio_norm * i, altura_norm * i, 0.0});
   }

   perfil.push_back({0.0, altura,0.0});

   inicializar(perfil, nperfiles);
}

// Clase Esfera

Esfera::Esfera(const int num_verts_per, const unsigned nperfiles)
:  MallaRevol()
{
   // Crear el perfil de la esfera (un círculo en el plano XY)
   std::vector<glm::vec3> perfil;
   for (int i = 0; i < num_verts_per; ++i) {
      float angulo = 2 * M_PI * i / (num_verts_per - 1);
      float x = 1.0 * sin(angulo);
      float y = -1.0 * cos(angulo);
      perfil.push_back( {x, y, 0.0});
   }

   // Llama a la función de inicialización de MallaRevol utilizando el perfil creado
   inicializar(perfil, nperfiles);
}

