// Nombre: Juan Manuel, Apellidos: Aneas Franco, Titulación: (GIADE).
// email: juanmanuelaf@correo.ugr.es, DNI o pasaporte: 74542495R

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
void MallaRevol::inicializar(const std::vector<glm::vec3> & perfil, const unsigned num_copias)
{
   // using namespace glm;

   // // Cálculo de normales

   // // Cálculo normales aristas
   // std::vector<glm::vec3> normales_aristas(0);

   // for (int i = 0; i < perfil.size() - 1; ++i)
   // {
   //    glm::vec3 nor_arista = perfil[i + 1] - perfil[i];
   //    nor_arista = glm::vec3(nor_arista.y, -nor_arista.x, nor_arista.z);
   //    nor_arista = glm::normalize(nor_arista);
   //    normales_aristas.push_back(nor_arista);
   // }

   // // Cálculo normales vértices
   // std::vector<glm::vec3> normales_vertices(0);

   // normales_vertices.push_back(normales_aristas[0]);

   // for (unsigned i = 1; i < perfil.size() - 1; ++i)
   // {
   //    glm::vec3 nor_vertice = normales_aristas[i - 1] + normales_aristas[i];
   //    glm::vec3 normal_vertice = glm::normalize(nor_vertice);
   //    normales_vertices.push_back(normal_vertice);
   // }

   // normales_vertices.push_back(normales_aristas[normales_aristas.size() - 1]);

   // // Cálculo de coordenadas de textura
   // std::vector<float> distancias(0);
   // std::vector<float> t_values(0);

   // for (unsigned i = 0; i < perfil.size() - 1; ++i)
   // {
   //    float distancia = glm::length(perfil[i + 1] - perfil[i]);
   //    distancias.push_back(distancia);
   // }

   // float total_distancia = std::accumulate(distancias.begin(), distancias.end(), 0.0f);

   // float acumulado = 0.0f;

   // for (unsigned i = 0; i < distancias.size(); ++i)
   // {
   //    acumulado += distancias[i];
   //    t_values.push_back(acumulado / total_distancia);
   // }

   // // Creación Tabla vértices, normales y textura
   // unsigned n = num_copias;
   // unsigned m = perfil.size();

   // for (unsigned i = 0; i < n; ++i)
   // {
   //    for (unsigned j = 0; j < m; ++j)
   //    {
   //       float angulo = 2 * M_PI * i / (n - 1);
   //       float r = perfil[j].x;

   //       // Rotar el vértice alrededor del eje Y
   //       float x_rotado = r * cos(angulo);
   //       float z_rotado = -r * sin(angulo);

   //       float r_normales = normales_vertices[j].x;

   //       float x_normales_rotado = r_normales * cos(angulo);
   //       float z_normales_rotado = -r_normales * sin(angulo);

   //       // Agregar el vértice a la tabla de vértices como un vector [x, 0, z]
   //       vertices.push_back({x_rotado, perfil[j].y, z_rotado});

   //       // Agregar normal vértice
   //       nor_ver.push_back({x_normales_rotado, normales_vertices[j].y, z_normales_rotado});

   //       // Calcular coordenadas de textura
   //       float coord_s = static_cast<float>(j) / (m - 1);
   //       float coord_t = 1.0f - t_values[j];

   //       // Agregar coordenadas de textura a la tabla cc_tt_ver
   //       cc_tt_ver.push_back({coord_s, coord_t});
   //    }
   // }

   // // Creación Tabla triángulos
   // for (unsigned i = 0; i < n - 1; ++i)
   // {
   //    for (unsigned j = 0; j < m - 1; ++j)
   //    {
   //       int k = i * m + j;

   //       // Añadir triángulo formado por los índices k, k + m y k + m + 1
   //       triangulos.push_back({k, k + m, k + m + 1});

   //       // Añadir triángulo formado por los índices k, k + m + 1 y k + 1
   //       triangulos.push_back({k, k + m + 1, k + 1});
   //    }
   // }


   using namespace glm ;
   
   // COMPLETAR: práctica 2: implementar algoritmo de creación de malla de revolución
   //
   // Escribir el algoritmo de creación de una malla indexada por revolución de un 
   // perfil, según se describe en el guion de prácticas.
   //
   //1ºCalculamos normales de las aristas
   vector<glm::vec3> nor_ari_per(0);
   for(unsigned int i=0; i<perfil.size()-1; ++i) {
      glm::vec3 nor_ari = perfil[i+1] - perfil[i];
      nor_ari = glm::vec3(nor_ari.y, -nor_ari.x,nor_ari.z);
      nor_ari = normalize(nor_ari);
      nor_ari_per.push_back(nor_ari);
   }

   //2ºCalculamos las normales de los vertices
   vector<glm::vec3> nor_vert_per(0);
   nor_vert_per.push_back(nor_ari_per[0]);
   for(unsigned int i=1; i<nor_ari_per.size()-1; ++i){
      glm::vec3 nor_vert = nor_ari_per[i] + nor_ari_per[i-1];
      nor_vert = normalize(nor_ari_per[i] + nor_ari_per[i-1]);
      nor_vert_per.push_back(nor_vert);
   }
   nor_vert_per.push_back(nor_ari_per[nor_ari_per.size()-1]);

   //3ºCalculamos coordenadas de textura
   vector<float> d;
   vector<float> t;

   // Cálculo de d
   for(unsigned int i=0; i < perfil.size()-1; ++i){
      d.push_back(length((perfil[i+1] - perfil[i])));
   }

   // Calculamos el normalizador
   float sum = 0.0f;
   for(uint i = 0; i < d.size(); ++i){
      sum += d[i];
   }

   // Inicializamos t para simplificar el algoritmo
   for(unsigned int i = 0; i < perfil.size(); ++i)
      t.push_back(0.0);

   // Cálculo de t
   for(unsigned int i=0; i<perfil.size(); ++i) {
      for(unsigned int j=0; j<i; ++j){
         t[i] += d[j];
      }
      t[i] = t[i]/sum*1.0f;
   }

   //COMPLETAR:Practica2 añadiendo cosas de la Practica4
   for (unsigned int i=0; i<num_copias; ++i){
      float angulo = (2*M_PI*i)/(num_copias-1);
      for (float j=0; j<perfil.size(); ++j){
         float radio = perfil[j].x;
         float radio_nor = nor_vert_per[j].x;
         vertices.push_back(glm::vec3{radio *cos(angulo), perfil[j].y, -1*radio *sin(angulo)});
         nor_ver.push_back(glm::vec3{radio_nor *cos(angulo), nor_vert_per[j].y, -1*radio_nor *sin(angulo)});
         cc_tt_ver.push_back(glm::vec2{i/(num_copias-1.0),1-t[j]});
      }
   }


   for(unsigned i=0; i<num_copias-1; ++i){
      for(float j=0; j<perfil.size()-1; ++j){
         int k = i*perfil.size() +j;
         triangulos.push_back({k,k+perfil.size(),k+perfil.size()+1});
         triangulos.push_back({k,k+perfil.size()+1,k+1});
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
      float angulo = M_PI * i / (num_verts_per - 1) - M_PI/2;
      float x = 1.0 * cos(angulo);
      float y = 1.0 * sin(angulo);
      perfil.push_back( {x, y, 0.0});
   }

   // Llama a la función de inicialización de MallaRevol utilizando el perfil creado
   inicializar(perfil, nperfiles);
}

// Clase EjercicioPerfil

EjercicioPerfil::EjercicioPerfil(const int num_verts_per, const unsigned nperfiles)
:  MallaRevol()
{
   // Crear el perfil de la esfera (un círculo en el plano XY)
   std::vector<glm::vec3> perfil;
   
   for(int i = 0; i < num_verts_per/2; ++i){
      float angulo = M_PI/2 * i / ((num_verts_per - 1)/2);
      perfil.push_back(glm::vec3(0.6*glm::sin(angulo), -0.6*glm::cos(angulo), 0.0));
   }

   for(int i = 0; i < num_verts_per/2; ++i){
      float angulo = M_PI/2 * i / ((num_verts_per - 1)/2);
      perfil.push_back(glm::vec3(0.6 + 0.4*glm::sin(angulo), 0.4 - 0.4*glm::cos(angulo), 0.0));
   }

   perfil.push_back(glm::vec3(0.0, 0.4, 0.0));
   
   // Llama a la función de inicialización de MallaRevol utilizando el perfil creado
   inicializar(perfil, nperfiles);
}

