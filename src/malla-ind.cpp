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
// **        + MallaInd: malla indexada de triángulos (derivada de Objeto3D)
// **        + MallaPLY: malla indexada de triángulos, leída de un PLY (derivada de MallaInd)
// **        + algunas clases derivadas de MallaInd.
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
#include "aplicacion-ig.h"
#include "malla-ind.h"   // declaración de 'ContextoVis'
#include "lector-ply.h"
#include "seleccion.h"   // para 'ColorDesdeIdent' 
#include "cmath"


// *****************************************************************************
// funciones auxiliares

// *****************************************************************************
// métodos de la clase MallaInd.

MallaInd::MallaInd()
{
   // nombre por defecto
   ponerNombre("malla indexada, anónima");
}
// -----------------------------------------------------------------------------

MallaInd::MallaInd( const std::string & nombreIni )
{
   // 'identificador' puesto a 0 por defecto, 'centro_oc' puesto a (0,0,0)
   ponerNombre(nombreIni) ;
}

//-----------------------------------------------------------------------------
// calcula la tabla de normales de triángulos una sola vez, si no estaba calculada

void MallaInd::calcularNormalesTriangulos()
{

   
   // si ya está creada la tabla de normales de triángulos, no es necesario volver a crearla
   const unsigned nt = triangulos.size() ;
   assert( 1 <= nt );
   if ( 0 < nor_tri.size() )
   {
      assert( nt == nor_tri.size() );
      return ;
   }

   // COMPLETAR: Práctica 4: creación de la tabla de normales de triángulos
   // ....

   // Creación de la tabla de normales de triángulos
   nor_tri.resize(nt);

   for (unsigned i = 0; i < nt; ++i)
   {
      // Obtener los índices de los vértices del triángulo
      unsigned p = triangulos[i].x;
      unsigned q = triangulos[i].y;
      unsigned r = triangulos[i].z;

      // Obtener las posiciones de los vértices
      glm::vec3 vertice_p = vertices[p];
      glm::vec3 vertice_q = vertices[q];
      glm::vec3 vertice_r = vertices[r];

      // Calcular vectores de las aristas
      glm::vec3 a = vertice_q - vertice_p;
      glm::vec3 b = vertice_r - vertice_p;

      // Calcular el vector normal mc (producto vectorial)
      glm::vec3 mc = glm::cross(a, b);

      // Verificar si el vector es degenerado (longitud nula)
      if (glm::length(mc) > 0.0f)
      {
         // Normalizar el vector y asignarlo a la tabla de normales
         nor_tri[i] = glm::normalize(mc);
      }
      else
      {
         // Asignar el vector nulo como vector normal
         nor_tri[i] = glm::vec3(0.0f);
      }
   }

}


// -----------------------------------------------------------------------------
// calcula las dos tablas de normales

void MallaInd::calcularNormales()
{
   using namespace glm ;
   // COMPLETAR: en la práctica 4: calculo de las normales de la malla
   // se debe invocar en primer lugar 'calcularNormalesTriangulos'
   // .......

   // Calcular normales de triángulos (si no se han calculado)
   calcularNormalesTriangulos();

   // Crear un vector para almacenar temporales de normales de vértices
   std::vector<vec3> nor_vert_temp(vertices.size(), vec3(0.0f));

   // Recorrer la lista de triángulos para acumular las normales de caras a los vértices correspondientes
   for (unsigned i = 0; i < triangulos.size(); ++i)
   {
      // Obtener índices de vértices del triángulo
      unsigned p = triangulos[i].x;
      unsigned q = triangulos[i].y;
      unsigned r = triangulos[i].z;

      // Acumular la normal del triángulo al vértice correspondiente
      nor_vert_temp[p] += nor_tri[i];
      nor_vert_temp[q] += nor_tri[i];
      nor_vert_temp[r] += nor_tri[i];
   }

   nor_tri.clear();

   // Normalizar las normales de vértices y asignarlas a la tabla de normales de vértices (nor_vert)
   nor_ver.resize(vertices.size());
   for (unsigned i = 0; i < vertices.size(); ++i)
   {
      // Verificar si el vector es degenerado (longitud nula)
      if (glm::length(nor_vert_temp[i]) > 0.0f)
      {
         // Normalizar el vector y asignarlo a la tabla de normales de vértices
         nor_ver[i] = glm::normalize(nor_vert_temp[i]);
      }
      else
      {
         // Asignar el vector nulo como vector normal
         nor_ver[i] = glm::vec3(0.0f);
      }
   }
}

// --------------------------------------------------------------------------------------------

void MallaInd::visualizarGL( )
{
   // comprobar algunas precondiciones básicas
   using namespace std ;
   assert( apl != nullptr );
   Cauce * cauce = apl->cauce ; assert( cauce != nullptr );
   CError();

   // si la malla no vértices o no tiene triángulos, imprimir advertencia y salir.
   if ( triangulos.size() == 0 || vertices.size() == 0 )
   {  cout << "advertencia: intentando dibujar malla vacía '" << leerNombre() << "'" << endl << flush ;
      return ;
   }

   // COMPLETAR: práctica 1: cambiar color del cauce
   //
   // Si el objeto tiene un color asignado (se comprueba con 'tieneColor')
   //    - hacer push del color actual del cauce
   //    - fijar el color en el cauce usando el color del objeto (se lee con 'leerColor()')
   if(tieneColor()){
      cauce->pushColor();
      cauce->fijarColor(leerColor());
   }

   // COMPLETAR: práctica 1: crear el descriptor de VAO, si no está creado
   //  Si el puntero 'dvao' es nulo, crear el descriptor de VAO
   //   * en primer lugar se crea el descriptor de VAO, con su constructor 
   //     (se le pasa como parámetro la tabla de posiciones y el número de atributos del cauce). 
   //   * se añade el descriptor de VBO con la tabla de índices (la tabla de triángulos),
   //   * finalmente se añaden al VAO los descriptores VBOs con tablas de atributos 
   //     que no estén vacías
   //  Si el VAO ya está creado, (dvao no nulo), no hay que hacer nada.
   //
   if(dvao == nullptr){
      DescrVBOAtribs * vbo_vertices = new DescrVBOAtribs(0, vertices);
      dvao = new DescrVAO(numero_atributos_cauce, vbo_vertices);
      DescrVBOInds * vbo_triangl = new DescrVBOInds(triangulos);
      
      dvao->agregar(vbo_triangl);
 
      if(col_ver.size() > 0){
         DescrVBOAtribs * vbo_col_ver = new DescrVBOAtribs(ind_atrib_colores, col_ver);
         dvao->agregar(vbo_col_ver);
      }
      if(nor_ver.size() > 0){
         DescrVBOAtribs * vbo_nor_ver = new DescrVBOAtribs(ind_atrib_normales, nor_ver);
         dvao->agregar(vbo_nor_ver);
      }
      if(nor_tri.size() > 0){
         DescrVBOAtribs * vbo_nor_tri = new DescrVBOAtribs(ind_atrib_normales, nor_tri);
         dvao->agregar(vbo_nor_tri);
      }
      if(cc_tt_ver.size() > 0){
         DescrVBOAtribs * vbo_cc_tt_ver = new DescrVBOAtribs(ind_atrib_coord_text, cc_tt_ver);
         dvao->agregar(vbo_cc_tt_ver);
      }
      if(segmentos_normales.size() > 0){
         DescrVBOAtribs * vbo_seg_norm = new DescrVBOAtribs(ind_atrib_normales, segmentos_normales);
         dvao->agregar(vbo_seg_norm);
      }
   }

   // COMPLETAR: práctica 1: visualizar el VAO usando el método 'draw' de 'DescrVAO'
   dvao->draw(GL_TRIANGLES);

   // COMPLETAR: práctica 1: restaurar color anterior del cauce 
   //
   // Si el objeto tiene un color asignado (se comprueba con 'tieneColor')
   //    - hacer 'pop' del color actual del cauce
   if(tieneColor()){
      cauce->popColor();
   }

}


// -----------------------------------------------------------------------------
// Visualizar el objeto con OpenGL
// usa las tablas de normales, colores y coordenadas de textura, si no están vacías.
      
void MallaInd::visualizarGeomGL( )
{
   // Comprobar que el descriptor de VAO ya está creado
   // (es decir, este método únicamente se podrá invocar después de que 
   // se haya llamado a 'visualizaGL')
   
   assert( dvao != nullptr );

   // COMPLETAR: práctica 1: visualizar únicamente la geometría del objeto 
   // 
   //    1. Desactivar todas las tablas de atributos del VAO (que no estén vacías)
   //    2. Dibujar la malla (únicamente visualizará los triángulos)
   //    3. Volver a activar todos los atributos para los cuales la tabla no esté vacía
   // ....
   
   // 1-Colores
   // 2-Normales
   // 3-CoordText

   if(col_ver.size() > 0){
      dvao->habilitarAtrib(1, false);
   }
   if(nor_ver.size() > 0 || nor_tri.size() > 0 || segmentos_normales.size() > 0){
      dvao->habilitarAtrib(2, false);
   }
   if(cc_tt_ver.size() > 0){
      dvao->habilitarAtrib(3, false);
   }
   
   dvao->draw(GL_TRIANGLES);
   
   if(col_ver.size() > 0){
      dvao->habilitarAtrib(1, true);
   }
   if(nor_ver.size() > 0 || nor_tri.size() > 0 || segmentos_normales.size() > 0){
      dvao->habilitarAtrib(2, true);
   }
   if(cc_tt_ver.size() > 0){
      dvao->habilitarAtrib(3, true);
   }
}

// -----------------------------------------------------------------------------
// Visualizar las normales del objeto, si no tiene tabla de normales imprime 
// advertencia y no hace nada.

void MallaInd::visualizarNormalesGL(  )
{
   using namespace std ;
   assert( apl != nullptr );
   Cauce * cauce = apl->cauce ; assert( cauce != nullptr );

   if ( nor_ver.size() == 0 )
   {
      cout << "Advertencia: intentando dibujar normales de una malla que no tiene tabla (" << leerNombre() << ")." << endl ;
      return ;
   }  

   if( nor_ver.size() != vertices.size() )
   {
      cout << "Error visu. normales: tabla de normales no vacía y de tamaño distinto a la de vértices." << endl ;
      cout << "Nombre del objeto        : " << leerNombre() << endl ;
      cout << "Tamaño tabla vértices    : " << vertices.size() << endl ;
      cout << "Tamaño tabla de normales : " << nor_ver.size() << endl ;
      exit(1);
   }
   CError();

   // COMPLETAR: práctica 4: visualizar las normales del objeto MallaInd
   // 
   // *1* Si el puntero al descriptor de VAO de normales ('dvao_normales') es nulo, 
   //    debemos de crear dicho descriptor, con estos pasos:
   //
   //       * Para cada posición 'v_i' de un vértice en el vector 'vertices':
   //             - Leer la correspondiente normal 'n_i' del vector de normales ('nor_ver').
   //             - Añadir 'v_i' al vector 'segmentos_normales'.
   //             - Añadir 'v_i+a*n_i' al vector 'segmentos_normales'.
   //
   //       * Crear el objeto descriptor del VAO de normales, para ello se usa el vector 
   //          'segmentos_normales' y se tiene en cuenta que esa descriptor únicamente gestiona 
   //          una tabla de atributos de vértices (la de posiciones, ya que las otras no se 
   //          necesitan).
   // 
   // *2* Visualizar el VAO de normales, usando el método 'draw' del descriptor, con el 
   //       tipo de primitiva 'GL_LINES'.

   //  ..........

    // Comprobar si el VAO de normales ya ha sido creado
    if (dvao_normales == nullptr)
    {
        // Dar valores al vector de segmentos de normales

        for (unsigned i = 0; i < vertices.size(); ++i)
        {
            // Obtener la posición del vértice y su normal
            glm::vec3 vi = vertices[i];
            glm::vec3 ni = nor_ver[i];

            // Añadir el vértice y su normal al vector de segmentos
            segmentos_normales.push_back(vi);
            segmentos_normales.push_back(vi + 0.35f*ni);
        }

        // Crear el objeto descriptor del VAO de normales
        DescrVBOAtribs * dvbo_segmentos = new DescrVBOAtribs(0, segmentos_normales);
        dvao_normales = new DescrVAO(numero_atributos_cauce, dvbo_segmentos);

        // Vaciar la tabla de segmentos de normales
        segmentos_normales.clear();
    }

    // Visualizar el VAO de normales
    dvao_normales->draw(GL_LINES);

}

// -----------------------------------------------------------------------------
// visualizar el objeto en 'modo seleccion', es decir, sin iluminación y con los colores 
// basados en los identificadores de los objetos
void MallaInd::visualizarModoSeleccionGL() 
{

   using namespace std ;
   assert( apl != nullptr );
   Cauce * cauce = apl->cauce ; assert( cauce != nullptr );

   // COMPLETAR: práctica 5: visualizar la malla en modo selección 
   //
   // Se debe escribir código para visualizar únicamente la geometría, pero usando el color 
   // obtenido a partir del identificador. El código da estos pasos:
   // 
   // 1. Leer el identificador del objeto (con 'leerIdentificador'). Si el objeto tiene 
   //    identificador (es decir, si su identificador no es -1)
   //       + Hacer push del color del cauce, con 'pushColor'.
   //       + Fijar el color del cauce (con 'fijarColor') usando un color obtenido a 
   //         partir del identificador (con 'ColorDesdeIdent'). 
   // 2. Invocar 'visualizarGeomGL' para visualizar la geometría.
   // 3. Si tiene identificador: hacer pop del color, con 'popColor'.
   //

   int identificador = leerIdentificador();

   if (identificador != -1) {
      // 1. Hacer push del color del cauce y fijar el color
      apl->cauce->pushColor();
      apl->cauce->fijarColor(ColorDesdeIdent(identificador));
   }

   // 2. Invocar 'visualizarGeomGL' para visualizar la geometría.
   visualizarGeomGL();

   if (identificador != -1) {
      // 3. Hacer pop del color del cauce
      apl->cauce->popColor();
   }
}


// ****************************************************************************
// Clase 'MallaPLY'

MallaPLY::MallaPLY( const std::string & nombre_arch )
{
   ponerNombre( std::string("malla leída del archivo '") + nombre_arch + "'" );

   // COMPLETAR: práctica 2: leer archivo PLY e inicializar la malla
   // ..........................
   LeerPLY(nombre_arch, vertices, triangulos);

   // COMPLETAR: práctica 4: invocar  a 'calcularNormales' para el cálculo de normales
   // .................

   calcularNormales();

}

// ****************************************************************************
// Clase 'Cubo

Cubo::Cubo()
:  MallaInd( "cubo 8 vértices" )
{

   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, +1.0, -1.0 }, // 2
         { -1.0, +1.0, +1.0 }, // 3
         { +1.0, -1.0, -1.0 }, // 4
         { +1.0, -1.0, +1.0 }, // 5
         { +1.0, +1.0, -1.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7
      } ;



   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,5,1}, {0,4,5}, // Y-
         {2,3,7}, {2,7,6}, // Y+ (+2)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)
      } ;

   calcularNormales();
}

//Clase Tetraedro

Tetraedro::Tetraedro()
: MallaInd( "tetraedro 4 vértices" )
{
   vertices = {
      {0.0, 1.0, 0.0}, // Vértice 0
      {1.0, -1.0, -1.0}, // Vértice 1
      {-1.0, -1.0, -1.0}, // Vértice 2
      {0.0, -1.0, 1.0}  // Vértice 3
   };

   ponerColor({ 0.2, 0.5, 0.7 });

   triangulos = {
      {0, 1, 2}, // Cara 0
      {0, 1, 3}, // Cara 1
      {1, 2, 3}, // Cara 2
      {0, 2, 3} // Cara 3
   };

   calcularNormales();
}

// Clase 'CuboColores

CuboColores::CuboColores()
:  MallaInd( "cubo 8 vértices" )
{

   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, +1.0, -1.0 }, // 2
         { -1.0, +1.0, +1.0 }, // 3
         { +1.0, -1.0, -1.0 }, // 4
         { +1.0, -1.0, +1.0 }, // 5
         { +1.0, +1.0, -1.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7
      } ;

   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,5,1}, {0,4,5}, // Y-
         {2,3,7}, {2,7,6}, // Y+ (+2)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)
      } ;

   for(unsigned i = 0; i < vertices.size(); ++i){
      float r = (vertices[i].x + 1.0) / 2.0;
      float g = (vertices[i].y + 1.0) / 2.0;
      float b = (vertices[i].z + 1.0) / 2.0;

      col_ver.push_back({r, g, b});
   }
   calcularNormales();
}

// Clase EstrellaZ

EstrellaZ::EstrellaZ(unsigned n)
:  MallaInd( "estrella opcional 1 n puntas" )
{
   assert (n > 1);

   float radio = 0.5;
   float centroX = 0.5;
   float centroY = 0.5;
   float centroZ = 0.0;

   // Crear vértice central
   vertices.push_back({centroX, centroY, centroZ});
   col_ver.push_back({1.0, 1.0, 1.0}); // Color blanco para el vértice central

   // Crear los vértices de las puntas
   for (unsigned i = 0; i < n; ++i)
   {
      float angulo = 2.0 * M_PI * i / n;
      float x = centroX + radio * cos(angulo);
      float y = centroY + radio * sin(angulo);
      float z = centroZ;

      vertices.push_back({x, y, z});
      col_ver.push_back({x, y, z}); // Color basado en las coordenadas X, Y y Z
   }

   // Crear los vértices interiores
   for (unsigned i = 0; i < n; ++i)
   {
      float angulo = 2.0 * M_PI * i / n + M_PI / n;
      float x = centroX + radio/2.0 * cos(angulo);
      float y = centroY + radio/2.0 * sin(angulo);
      float z = centroZ;

      vertices.push_back({x, y, z});
      col_ver.push_back({x, y, z}); // Color basado en las coordenadas X, Y y Z
   }

   // Crear los triángulos
   for (unsigned i = 0; i < 2*n-1; ++i)
   {
      if(i < n){
         triangulos.push_back({0, i+1, (n+1+i)%(2*n+1)});
      }
      else{
         triangulos.push_back({0, i+1, (n+1+i)%(2*n-1)});
      }
   }
   triangulos.push_back({0,1,2*n});
};


CasaX::CasaX()
:  MallaInd( "casa 10 vértices" )
{

   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, +0.5, -1.0 }, // 2
         { -1.0, +0.5, +1.0 }, // 3
         { +1.0, -1.0, -1.0 }, // 4
         { +1.0, -1.0, +1.0 }, // 5
         { +1.0, +0.5, -1.0 }, // 6
         { +1.0, +0.5, +1.0 }, // 7
         { 0.0, +1.0, +1.0 }, // 8
         { 0.0, +1.0, -1.0 }  // 9
      } ;



   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         /*{0,5,1}, {0,4,5}, // Y-
         {2,3,7}, {2,7,6},*/ // Y+ (+2)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}, // Z+ (+1)

         {3,7,8},{2,6,9},
         {2,3,8},{2,8,9},
         {6,7,8},{6,8,9}
      } ;

   for (unsigned i = 0; i < vertices.size(); ++i)
   {
      col_ver.push_back({vertices[i].x, vertices[i].y, vertices[i].z});
   }
}

// Clase MallaTriangulo

MallaTriangulo::MallaTriangulo()
:  MallaInd( "triángulo 3 vértices" )
{

   vertices =
      {  { -0.5, 0.0, 0.0 }, // 0
         { +0.5, 0.0, 0.0 }, // 1
         { 0.0, +sqrt(2.0), 0.0 }, // 2
      } ;

   triangulos =
      { 
         {0,1,2}
      } ;
}


// Clase MallaCuadrado

MallaCuadrado::MallaCuadrado()
:  MallaInd( "cuadrado 4 vértices" )
{

   vertices =
      {  { +1.0, +1.0, 0.0 }, // 0
         { -1.0, +1.0, 0.0 }, // 1
         { -1.0, -1.0, 0.0 }, // 2
         { +1.0, -1.0, 0.0 }, // 3
      } ;



   triangulos =
      {
         {0,1,2}, {0,2,3}
      } ;
}


// Clase MallaPiramideL

MallaPiramideL::MallaPiramideL()
:  MallaInd( "cubo 8 vértices" )
{

   vertices =
      {
         { +0.5, 0.0, +1.0 }, // 0
         { -0.5, 0.0, +1.0 }, // 1
         { -0.5, 0.0, -1.0 }, // 2
         { +1.5, 0.0, 0.0 }, // 3
         { +1.5, 0.0, -1.0 }, // 4
         { +0.5, 0.0, 0.0 }, // 5
         { 0.0, +2.0, 0.0 }, // 6
      } ;



   triangulos =
      {
         {0,1,6}, {3,4,6},
         {0,5,6}, {1,2,6},
         {2,4,6}, {3,5,6},

         {0,1,5}, {1,4,2},
         {3,4,5}
      } ;
}


// Clase PiramideEstrellaZ

PiramideEstrellaZ::PiramideEstrellaZ(unsigned n)
:  MallaInd( "piramide estrella opcional 1 n puntas" )
{
   assert(n > 1);

   float radio = 0.5;
   float centroX = 0.5;
   float centroY = 0.5;
   float centroZ = 0.0;

   // Crear vértice central
   vertices.push_back({centroX, centroY, centroZ});
   col_ver.push_back({1.0, 1.0, 1.0}); // Color blanco para el vértice central

   // Crear los vértices de las puntas
   for (unsigned i = 0; i < n; ++i)
   {
      float angulo = 2.0 * M_PI * i / n;
      float x = centroX + radio * cos(angulo);
      float y = centroY + radio * sin(angulo);
      float z = centroZ;

      vertices.push_back({x, y, z});
      col_ver.push_back({x, y, z}); // Color basado en las coordenadas X, Y y Z
   }

   // Crear los vértices interiores
   for (unsigned i = 0; i < n; ++i)
   {
      float angulo = 2.0 * M_PI * i / n + M_PI / n;
      float x = centroX + radio/2.0 * cos(angulo);
      float y = centroY + radio/2.0 * sin(angulo);
      float z = centroZ;

      vertices.push_back({x, y, z});
      col_ver.push_back({x, y, z}); // Color basado en las coordenadas X, Y y Z
   }

   // Crear vértice cúspide
   vertices.push_back({centroX, centroY, 0.5});
   col_ver.push_back({1.0, 1.0, 1.0}); // Color blanco para la cúspide
   unsigned index_cuspide = vertices.size()-1;

   // Crear los triángulos Base
   for (unsigned i = 0; i < 2*n-1; ++i)
   {
      if(i < n){
         triangulos.push_back({0, i+1, (n+1+i)%(2*n+1)});
      }
      else{
         triangulos.push_back({0, i+1, (n+1+i)%(2*n-1)});
      }
   }
   triangulos.push_back({0,1,2*n});

   // Crear los triángulos Laterales
   for (unsigned i = 0; i < 2*n-1; ++i)
   {
      if(i < n){
         triangulos.push_back({index_cuspide, i+1, (n+1+i)%(2*n+1)});
      }
      else{
         triangulos.push_back({index_cuspide, i+1, (n+1+i)%(2*n-1)});
      }
   }
   triangulos.push_back({index_cuspide,1,2*n});
};


//Clase RejillaY

RejillaY::RejillaY(unsigned n, unsigned m)
: MallaInd( "rejilla opcional 2" )
{
   assert(n > 1 && m > 1);
   
   // Y siempre 0
   //Colores igual coordenadas (x,y,z)

   // Generar vértices
   for(unsigned i = 0; i < n; ++i){
      float index_i = 1.0/(n-1) * i;
      for(unsigned j = 0; j < m; ++j){
         float index_j = 1.0/(m-1) * j;

         vertices.push_back({index_i, 0.0, index_j});
         col_ver.push_back({index_i, 0.0, index_j});
      }
   }
   // Generar triángulos
   for (unsigned i = 0; i < n - 1; ++i) {
      for (unsigned j = 0; j < m - 1; ++j) {
        int index_actual = i * m + j;
        int index_siguiente = (i + 1) * m + j;

        triangulos.push_back({index_actual, index_siguiente, index_actual + 1});

        triangulos.push_back({index_actual + 1, index_siguiente, index_siguiente + 1});
      }
   }
}

//Clase MallaTorre

MallaTorre::MallaTorre(unsigned n)
: MallaInd( "mallatorre opcional 3" )
{
   // n plantas
   // 4 caras por planta -> Cuadrado lado 1 unidad
   // 4(n+1) vértices y 8n triángulo

   /*
      EH   HG    GF    FE    
      AD   DC    CB    BA    

      A  0  i
      B  1  i+1
      C  2  i+2
      D  3  i+3
      E  4  i+4
      F  5  i+5
      G  6  i+6
      H  7  i+7
   */

   assert(n > 0);
   
   // Crear base
   vertices.push_back({0,0,0});  //A
   vertices.push_back({1,0,0});  //B
   vertices.push_back({1,0,1});  //C
   vertices.push_back({0,0,1});  //D

   // Crear vértices superiores de cada
   for(unsigned i = 0; i < n; ++i){
      vertices.push_back({0,i+1,0});   //E
      vertices.push_back({1,i+1,0});   //F
      vertices.push_back({1,i+1,1});   //G
      vertices.push_back({0,i+1,1});   //H
   }
   
   // Crear triángulos por planta  BUCLE 8 Push
   for(unsigned i = 0; i < 4*n; i += 4){
      triangulos.push_back({i,i+3,i+4});
      triangulos.push_back({i+3,i+7,i+4});
      triangulos.push_back({i+3,i+2,i+7});
      triangulos.push_back({i+2,i+6,i+7});
      triangulos.push_back({i+2,i+1,i+6});
      triangulos.push_back({i+1,i+5,i+6});
      triangulos.push_back({i+1,i,i+5});
      triangulos.push_back({i,i+4,i+5});
   }
}

// -----------------------------------------------------------------------------------------------

Cubo24::Cubo24(){
   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0.0 
         { -1.0, -1.0, -1.0 }, // 0.1 
         { -1.0, -1.0, -1.0 }, // 0.2
         { -1.0, -1.0, +1.0 }, // 1.3 
         { -1.0, -1.0, +1.0 }, // 1.4 
         { -1.0, -1.0, +1.0 }, // 1.5 
         { -1.0, +1.0, -1.0 }, // 2.6 
         { -1.0, +1.0, -1.0 }, // 2.7
         { -1.0, +1.0, -1.0 }, // 2.8
         { -1.0, +1.0, +1.0 }, // 3.9
         { -1.0, +1.0, +1.0 }, // 3.10
         { -1.0, +1.0, +1.0 }, // 3.11 
         { +1.0, -1.0, -1.0 }, // 4.12
         { +1.0, -1.0, -1.0 }, // 4.13
         { +1.0, -1.0, -1.0 }, // 4.14
         { +1.0, -1.0, +1.0 }, // 5.15
         { +1.0, -1.0, +1.0 }, // 5.16
         { +1.0, -1.0, +1.0 }, // 5.17
         { +1.0, +1.0, -1.0 }, // 6.18
         { +1.0, +1.0, -1.0 }, // 6.19
         { +1.0, +1.0, -1.0 }, // 6.20
         { +1.0, +1.0, +1.0 }, // 7.21
         { +1.0, +1.0, +1.0 }, // 7.22
         { +1.0, +1.0, +1.0 }, // 7.23
      } ;

   triangulos =
      {  {9,0,3}, {0,9,6}, // X-
         {10,4,15}, {15,21,10}, // X+ (+4)

         {22,16,18}, {16,12,18}, // Y-
         {13,1,19}, {1,7,19}, // Y+ (+2)

         {8,11,20}, {11,23,20}, // Z-
         {17,5,2}, {17,2,14}  // Z+ (+1)
      };
      
   cc_tt_ver = 
   {  {0.0, 1.0},     // 1 
      {1.0, 1.0},     // 4 
      {1.0, 0.0},     // 6 
      {1.0, 1.0},     // 1 
      {0.0, 1.0},     // 2
      {1.0, 1.0},     // 6
      {0.0, 0.0},     // 1 
      {1.0, 0.0},     // 4
      {1.0, 0.0},     // 5  
      {1.0, 0.0},     // 1
      {0.0, 0.0},     // 2 
      {0.0, 0.0},     // 5
      {1.0, 1.0},     // 3
      {0.0, 1.0},     // 4   
      {0.0, 0.0},     // 6
      {1.0, 1.0},     // 2  
      {0.0, 1.0},     // 3
      {0.0, 1.0},     // 6
      {1.0, 0.0},     // 3 
      {0.0, 0.0},     // 4 
      {1.0, 1.0},     // 5
      {1.0, 0.0},     // 2 
      {0.0, 0.0},     // 3 
      {0.0, 1.0},     // 5  
   };

   calcularNormales();
}

// -----------------------------------------------------------------------------------------------

Cubo24SinMap::Cubo24SinMap(){
   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0.0 
         { -1.0, -1.0, -1.0 }, // 0.1 
         { -1.0, -1.0, -1.0 }, // 0.2
         { -1.0, -1.0, +1.0 }, // 1.3 
         { -1.0, -1.0, +1.0 }, // 1.4 
         { -1.0, -1.0, +1.0 }, // 1.5 
         { -1.0, +1.0, -1.0 }, // 2.6 
         { -1.0, +1.0, -1.0 }, // 2.7
         { -1.0, +1.0, -1.0 }, // 2.8
         { -1.0, +1.0, +1.0 }, // 3.9
         { -1.0, +1.0, +1.0 }, // 3.10
         { -1.0, +1.0, +1.0 }, // 3.11 
         { +1.0, -1.0, -1.0 }, // 4.12
         { +1.0, -1.0, -1.0 }, // 4.13
         { +1.0, -1.0, -1.0 }, // 4.14
         { +1.0, -1.0, +1.0 }, // 5.15
         { +1.0, -1.0, +1.0 }, // 5.16
         { +1.0, -1.0, +1.0 }, // 5.17
         { +1.0, +1.0, -1.0 }, // 6.18
         { +1.0, +1.0, -1.0 }, // 6.19
         { +1.0, +1.0, -1.0 }, // 6.20
         { +1.0, +1.0, +1.0 }, // 7.21
         { +1.0, +1.0, +1.0 }, // 7.22
         { +1.0, +1.0, +1.0 }, // 7.23
      } ;

   triangulos =
      {  {9,0,3}, {0,9,6}, // X-
         {10,4,15}, {15,21,10}, // X+ (+4)

         {22,16,18}, {16,12,18}, // Y-
         {13,1,19}, {1,7,19}, // Y+ (+2)

         {8,11,20}, {11,23,20}, // Z-
         {17,5,2}, {17,2,14}  // Z+ (+1)
      };

   calcularNormales();
}

// -----------------------------------------------------------------------------------------------

MallaDiscoP4::MallaDiscoP4(int ejr) {
   ponerColor({1.0, 1.0, 1.0});

   const unsigned ni = 23, nj = 31 ;

   for( unsigned i= 0 ; i < ni ; i++ )
      for( unsigned j= 0 ; j < nj ; j++ ) {
         const float
            fi = float(i)/float(ni-1),
            fj = float(j)/float(nj-1),
            ai = 2.0*M_PI*fi,
            x = fj * cos( ai ),
            y = fj * sin( ai ),
            z = 0.0 ;
         vertices.push_back({ x, y, z });
         // Ejercicio Adicional 1 de la P4
         if(ejr == 1)                     
            cc_tt_ver.push_back({float(x/2.0 + 0.5), float(y/2.0 + 0.5)});
         // Ejercicio Adicional 2 de la P4
         if(ejr == 2)
            cc_tt_ver.push_back({fi, fj});
      }

   for( unsigned i= 0 ; i < ni-1 ; i++ )
      for( unsigned j= 0 ; j < nj-1 ; j++ ) {
         triangulos.push_back({ i*nj+j, i*nj+(j+1), (i+1)*nj+(j+1) });
         triangulos.push_back({ i*nj+j, (i+1)*nj+(j+1), (i+1)*nj+j });
      }
}