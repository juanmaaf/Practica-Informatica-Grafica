// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Gestión de grafos de escena (implementación)
// ** Copyright (C) 2016-2023 Carlos Ureña
// **
// ** Implementación de: 
// **     + Clase 'NodoGrafoEscena' (derivada de 'Objeto3D')
// **     + Clase 'EntradaNGE' (una entrada de un nodo del grafo de escena)
// **     + Tipo enumerado 'TipoEntNGE' (tipo de entradas del nodo del grafo de escena)
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
#include "grafo-escena.h"
#include "aplicacion-ig.h"
#include "seleccion.h"   // para 'ColorDesdeIdent' 
#include <malla-revol.h>

using namespace std;

// *********************************************************************
// Entrada del nodo del Grafo de Escena

// ---------------------------------------------------------------------
// Constructor para entrada de tipo sub-objeto

EntradaNGE::EntradaNGE( Objeto3D * pObjeto )
{
   assert( pObjeto != nullptr );
   tipo   = TipoEntNGE::objeto ;
   objeto = pObjeto ;
}
// ---------------------------------------------------------------------
// Constructor para entrada de tipo "matriz de transformación"

EntradaNGE::EntradaNGE( const glm::mat4 & pMatriz )
{
   tipo    = TipoEntNGE::transformacion ;
   matriz  = new glm::mat4() ; // matriz en el heap, puntero propietario
   *matriz = pMatriz ;
}

// ---------------------------------------------------------------------
// Constructor para entrada de tipo "matriz de transformación"

EntradaNGE::EntradaNGE( Material * pMaterial )
{
   assert( pMaterial != nullptr );
   tipo     = TipoEntNGE::material ;
   material = pMaterial ;
}

// -----------------------------------------------------------------------------
// Destructor de una entrada

EntradaNGE::~EntradaNGE()
{
   /**  no fnciona debido a que se hacen copias (duplicados) de punteros
   if ( tipo == TipoEntNGE::transformacion )
   {
      assert( matriz != NULL );
      delete matriz ;
      matriz = NULL ;
   }
   * **/
}

// *****************************************************************************
// Nodo del grafo de escena: contiene una lista de entradas
// *****************************************************************************

NodoGrafoEscena::NodoGrafoEscena()
{

}

// -----------------------------------------------------------------------------
// Visualiza usando OpenGL

void NodoGrafoEscena::visualizarGL(  )
{
   using namespace std ;
   assert( apl != nullptr );

    // comprobar que hay un cauce y una pila de materiales y recuperarlos.
   Cauce *          cauce           = apl->cauce ;           assert( cauce != nullptr );
   PilaMateriales * pila_materiales = apl->pila_materiales ; assert( pila_materiales != nullptr );

   // COMPLETAR: práctica 3: implementar la visualización del nodo
   //
   // Se deben de recorrer las entradas y llamar recursivamente de visualizarGL, pero 
   // teniendo en cuenta que, al igual que el método visualizarGL de las mallas indexadas,
   // si el nodo tiene un color, debemos de cambiar el color del cauce (y hacer push/pop). 
   // Además, hay que hacer push/pop de la pila de modelado. 
   // Así que debemos de dar estos pasos:
   //
   // 1. Si el objeto tiene un color asignado (se comprueba con 'tieneColor')
   //     - hacer push del color actual del cauce (con 'pushColor') y después
   //     - fijar el color en el cauce (con 'fijarColor'), usando el color del objeto (se lee con 'leerColor()')
   if(tieneColor()){
      cauce->pushColor();
      cauce->fijarColor(leerColor());
   }

   // 2. Guardar copia de la matriz de modelado (con 'pushMM'),
   cauce->pushMM();

   // 3. Para cada entrada del vector de entradas:
   //     - si la entrada es de tipo objeto: llamar recursivamente a 'visualizarGL'
   //     - si la entrada es de tipo transformación: componer la matriz (con 'compMM')
   for(unsigned i = 0; i < entradas.size(); ++i ){
      switch (entradas[i].tipo){
         case TipoEntNGE::objeto:
            entradas[i].objeto->visualizarGL();
         break;

         case TipoEntNGE::transformacion:
            cauce->compMM( *(entradas[i].matriz) );
         break;

         default:
         break;
      }
   }

   // 4. Restaurar la copia guardada de la matriz de modelado (con 'popMM')
   cauce->popMM() ;

   // 5. Si el objeto tiene color asignado:
   //     - restaurar el color original a la entrada (con 'popColor')
   if(tieneColor()){
      cauce->popColor();
   }

   // COMPLETAR: práctica 4: añadir gestión de los materiales cuando la iluminación está activada    
   //
   // Si 'apl->iluminacion' es 'true', se deben de gestionar los materiales:
   //
   //   1. al inicio, hacer 'push' de la pila de materiales (guarda material actual en la pila)
   //   2. si una entrada es de tipo material, activarlo usando a pila de materiales
   //   3. al finalizar, hacer 'pop' de la pila de materiales (restaura el material activo al inicio)

   // ......


}

// *****************************************************************************
// visualizar pura y simplemente la geometría, sin colores, normales, coord. text. etc...

void NodoGrafoEscena::visualizarGeomGL(  )
{
   using namespace std ;
   // comprobar que hay un cauce 
   assert( apl != nullptr );
   Cauce * cauce = apl->cauce; assert( cauce != nullptr );
  
   // COMPLETAR: práctica 3: implementar la visualización del nodo (ignorando colores)
   //
   // Este método hace un recorrido de las entradas del nodo, parecido a 'visualizarGL', pero más simple,
   // Se dan estos pasos:
   //
   // 1. Guardar copia de la matriz de modelado (con 'pushMM'), 
   cauce->pushMM();

   // 2. Para cada entrada del vector de entradas:
   //         - Si la entrada es de tipo objeto: llamar recursivamente a 'visualizarGeomGL'.
   //         - Si la entrada es de tipo transformación: componer la matriz (con 'compMM').
   for(unsigned i = 0; i < entradas.size(); ++i ){
      switch (entradas[i].tipo){
         case TipoEntNGE::objeto:
            entradas[i].objeto->visualizarGeomGL();
         break;

         case TipoEntNGE::transformacion:
            cauce->compMM( *(entradas[i].matriz) );
         break;

         default:
         break;
      }
   }

   //   3. Restaurar la copia guardada de la matriz de modelado (con 'popMM')
   cauce->popMM() ;

   // .......

}

// -----------------------------------------------------------------------------
// Visualizar las normales de los objetos del nodo

void NodoGrafoEscena::visualizarNormalesGL(  )
{
   using namespace std ;

   // comprobar que hay un cauce 
   assert( apl != nullptr );
   Cauce * cauce = apl->cauce; assert( cauce != nullptr );
  

   // COMPLETAR: práctica 4: visualizar las normales del nodo del grafo de escena
   //
   // Este método hace un recorrido de las entradas del nodo, parecido a 'visualizarGL', teniendo 
   // en cuenta estos puntos:
   //
   // - usar push/pop de la matriz de modelado al inicio/fin (al igual que en visualizatGL)
   // - recorrer las entradas, llamando recursivamente a 'visualizarNormalesGL' en los nodos u objetos hijos
   // - ignorar el color o identificador del nodo (se supone que el color ya está prefijado antes de la llamada)
   // - ignorar las entradas de tipo material, y la gestión de materiales (se usa sin iluminación)

   // .......

}

// -----------------------------------------------------------------------------
// visualizar el objeto en 'modo seleccion', es decir, sin iluminación y con los colores 
// basados en los identificadores de los objetos
void NodoGrafoEscena::visualizarModoSeleccionGL()
{
   using namespace std ;
   assert( apl != nullptr );
   Cauce * cauce = apl->cauce ; assert( cauce != nullptr );

   // COMPLETAR: práctica 5: visualizar este nodo en modo selección.
   //
   // Se debe escribir código para dar estos pasos:
   // 
   // 2. Leer identificador (con 'leerIdentificador'), si el identificador no es -1 
   //      + Guardar una copia del color actual del cauce (con 'pushColor')
   //      + Fijar el color del cauce de acuerdo al identificador, (usar 'ColorDesdeIdent'). 
   // 3. Guardar una copia de la matriz de modelado (con 'pushMM')
   // 4. Recorrer la lista de nodos y procesar las entradas transformación o subobjeto:
   //      + Para las entradas subobjeto, invocar recursivamente a 'visualizarModoSeleccionGL'
   //      + Para las entradas transformación, componer la matriz (con 'compMM')
   // 5. Restaurar la matriz de modelado original (con 'popMM')   
   // 6. Si el identificador no es -1, restaurar el color previo del cauce (con 'popColor')
   //
   // ........


}

// -----------------------------------------------------------------------------
// Añadir una entrada (al final).
// genérica (de cualqiuer tipo de entrada)

unsigned NodoGrafoEscena::agregar( const EntradaNGE & entrada )
{
   // COMPLETAR: práctica 3: agregar la entrada al nodo, devolver índice de la entrada agregada
   // ........
   entradas.push_back(entrada);
   return entradas.size()-1 ;

}
// -----------------------------------------------------------------------------
// construir una entrada y añadirla (al final)
// objeto (copia solo puntero)

unsigned NodoGrafoEscena::agregar( Objeto3D * pObjeto )
{
   return agregar( EntradaNGE( pObjeto ) );
}
// ---------------------------------------------------------------------
// construir una entrada y añadirla (al final)
// matriz (copia objeto)

unsigned NodoGrafoEscena::agregar( const glm::mat4 & pMatriz )
{
   return agregar( EntradaNGE( pMatriz ) );
}
// ---------------------------------------------------------------------
// material (copia solo puntero)
unsigned NodoGrafoEscena::agregar( Material * pMaterial )
{
   return agregar( EntradaNGE( pMaterial ) );
}

// devuelve el puntero a la matriz en la i-ésima entrada
glm::mat4 * NodoGrafoEscena::leerPtrMatriz( unsigned indice )
{
   // COMPLETAR: práctica 3: leer un puntero a una matriz en una entrada de un nodo
   //
   // Devolver el puntero a la matriz en la entrada indicada por 'indice'. 
   // Debe de dar error y abortar si: 
   //   - el índice está fuera de rango
   assert( indice < entradas.size() );

   //   - la entrada no es de tipo transformación
   assert( entradas[indice].tipo == TipoEntNGE::transformacion );

   //   - el puntero a la matriz es nulo
   assert( entradas[indice].matriz != nullptr );

   //
   // Sustituir 'return nullptr' por lo que corresponda.
   //
   return entradas[indice].matriz ;
   
}
// -----------------------------------------------------------------------------
// si 'centro_calculado' es 'false', recalcula el centro usando los centros
// de los hijos (el punto medio de la caja englobante de los centros de hijos)

void NodoGrafoEscena::calcularCentroOC()
{
   using namespace std ;
   using namespace glm ;

   // COMPLETAR: práctica 5: calcular y guardar el centro del nodo
   //    en coordenadas de objeto (hay que hacerlo recursivamente)
   //   (si el centro ya ha sido calculado, no volver a hacerlo)
   // ........

}
// -----------------------------------------------------------------------------
// método para buscar un objeto con un identificador y devolver un puntero al mismo

bool NodoGrafoEscena::buscarObjeto
(
   const int          ident_busc, // identificador a buscar
   const glm::mat4 &  mmodelado,  // matriz de modelado
   Objeto3D       **  objeto,     // (salida) puntero al puntero al objeto
   glm::vec3 &        centro_wc   // (salida) centro del objeto en coordenadas del mundo
)
{
   using namespace std ;
   using namespace glm ;
   
   assert( 0 < ident_busc );

   // COMPLETAR: práctica 5: buscar un sub-objeto con un identificador
   // Se deben de dar estos pasos:

   // 1. calcula el centro del objeto, (solo la primera vez)
   // ........


   // 2. si el identificador del nodo es el que se busca, ya está (terminar)
   // ........


   // 3. El nodo no es el buscado: buscar recursivamente en los hijos
   //    (si alguna llamada para un sub-árbol lo encuentra, terminar y devolver 'true')
   // ........


   // ni este nodo ni ningún hijo es el buscado: terminar
   return false ;
}

GrafoEstrellaX::GrafoEstrellaX(const int n, const float alpha){

   velocidad_giro = alpha;

   unsigned ind1 = agregar(glm::scale(glm::vec3( 1.0, 1.0, 1.0)));
   matriz_giro = leerPtrMatriz(ind1);
   
   NodoGrafoEscena * estrella = new NodoGrafoEscena();
   estrella->agregar( glm::scale(glm::vec3(0.0, 2.6, 2.6) )); // 0.5 radio inicial * 2.6 = 1.3 radio buscado. Perpendicular eje X -> Está en Y,Z
   estrella->agregar( glm::rotate( float(glm::radians(90.0)), glm::vec3( 0.0, 1.0, 0.0)));
   estrella->agregar( glm::translate( glm::vec3(-0.5, -0.5, 0.0) ));
   estrella->agregar(new EstrellaZ(n));

   for(int i = 0; i < n; ++i){
      float angulo = 2.0 * M_PI * i / n;
      float x = 1.3 * cos(angulo);
      float y = 1.3 * sin(angulo);
      float z = 0.0;

      NodoGrafoEscena * cono = new NodoGrafoEscena();
      
      
      cono->agregar(glm::rotate(float(glm::radians(90.0)), glm::vec3(0.0, 1.0, 0.0)));
      cono->agregar( glm::translate(glm::vec3(x, y, z) ));
      cono->agregar( glm::scale(glm::vec3(0.14, 0.15, 0.14) ));
      cono->agregar(glm::rotate(float(angulo - glm::radians(90.0f)), glm::vec3(0.0, 0.0, 1.0)));
      cono->agregar( new Cono(6, 15) );

      agregar(cono);
   }
   
   agregar(estrella);
}

void GrafoEstrellaX::girar_respecto_X(const float alpha_nuevo){
   *matriz_giro = glm::rotate( alpha_nuevo, glm::vec3(1.0, 0.0, 0.0));
}

float GrafoEstrellaX::calcula_lineal(const float t_sec){
   // a = vinicial
   // b = 2pi*w
   // w = velocidad angulan (ciclos/s)
   unsigned w = velocidad_giro;
   unsigned a = 0;
   unsigned b = 2 * M_PI * w;

   return a+b*t_sec;
}


unsigned GrafoEstrellaX::leerNumParametros() const{
    return 1;
} 


void GrafoEstrellaX::actualizarEstadoParametro( const unsigned iParam, const float t_sec ){

   switch (iParam)
   {
      case 0: // Girar Helices Sup
         girar_respecto_X(calcula_lineal(t_sec));
      default:
         break;
   }
}

GrafoCubos::GrafoCubos(const float alpha){

   velocidad_giro = alpha;

   // Rejilla
   NodoGrafoEscena * rejilla= new NodoGrafoEscena();
   rejilla->agregar(glm::translate(glm::vec3((-0.5,-0.5,-0.5))));
   rejilla->agregar(new RejillaY(10,10)); // Base Cubo Central

   // Cubo
   NodoGrafoEscena * cubo = new NodoGrafoEscena();
   unsigned ind1 = cubo->agregar(rotate(0.0f,glm::vec3(0,1,0)));  // Animación: Cada cubo pequeño rota entorno al eje que pasa por su centro y el origen
   cubo->agregar(translate(glm::vec3{0,-0.75,0}));               
   cubo->agregar(scale(glm::vec3(0.15,0.25,0.15)));
   cubo->agregar(new Cubo());                        // eSTO DA LUGAR AL CUBO DEL SUELO

   // Como ya tenemos el objeto compuesto que se va a repetir ,agregamos 4 caras de nuestro 
   // objeto compuesto rotando cada objeto 90 grados sobre el eje X
   for(int i = 0; i < 4; i++){
      agregar(rotate(float(glm::radians(90.0)), glm::vec3{1,0,0}));
      agregar(rejilla);
      agregar(cubo);
   }

   // 2 caras restantes  rotando cada objeto 90 grados en Z
   agregar(rotate(float(glm::radians(90.0)), glm::vec3{0,0,1}));
   agregar(rejilla);
   agregar(cubo);
   agregar(rotate(float(glm::radians(180.0)), glm::vec3{1,0,0}));
   agregar(rejilla);
   agregar(cubo);

   matriz_giro = cubo->leerPtrMatriz(ind1);
}


void GrafoCubos::rotacion_cubos(const float alpha_nuevo){
   *matriz_giro = glm::rotate( alpha_nuevo, glm::vec3(0.0, 1.0, 0.0));
}

float GrafoCubos::calcula_lineal(const float t_sec){
   // a = vinicial
   // b = 2pi*w
   // w = velocidad angulan (ciclos/s)
   unsigned w = velocidad_giro;
   unsigned a = 0;
   unsigned b = 2 * M_PI * w;

   return a+b*t_sec;
}


unsigned GrafoCubos::leerNumParametros() const{
    return 1;
} 


void GrafoCubos::actualizarEstadoParametro( const unsigned iParam, const float t_sec ){

   switch (iParam)
   {
      case 0: // Girar Helices Sup
         rotacion_cubos(calcula_lineal(t_sec));
      default:
         break;
   }
}






