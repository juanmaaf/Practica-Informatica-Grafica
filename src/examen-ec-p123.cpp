// Nombre: Juan Manuel, Apellidos: Aneas Franco, Titulación: (GIADE).
// email: juanmanuelaf@correo.ugr.es, DNI o pasaporte: 74542495R

#include "examen-ec-p123.h"
#include "malla-revol.h"

// Clase P1MallaCubo

P1MallaCubo::P1MallaCubo()
:  MallaInd( "cubo 10 vértices (2 son los centros de cara sup e inferior) y 4 triángulos en ls caras superior e inferior (2 en el resto)" )
{

   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0 Inferior
         { -1.0, -1.0, +1.0 }, // 1 Inferior
         { -1.0, +1.0, -1.0 }, // 2 Superior
         { -1.0, +1.0, +1.0 }, // 3 Superior
         { +1.0, -1.0, -1.0 }, // 4 Inferior
         { +1.0, -1.0, +1.0 }, // 5 Inferior
         { +1.0, +1.0, -1.0 }, // 6 Superior
         { +1.0, +1.0, +1.0 }, // 7 Superior
         { 0.0, -1.0, 0.0}, //   8 Centro Inferior
         { 0.0, +1.0, 0.0}  //   9 Centro Superior
      } ;

   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,1,8}, {0,4,8}, {1,5,8}, {4,5,8}, // 4 triángulos cara Inferior
         {2,3,9}, {2,6,9}, {3,7,9}, {6,7,9}, // 4 triángulos cara Superior

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)
      } ;

   for(unsigned i = 0; i < vertices.size()-2; ++i){
      float r = (vertices[i].x + 1.0) / 2.0;
      float g = (vertices[i].y + 1.0) / 2.0;
      float b = (vertices[i].z + 1.0) / 2.0;

      col_ver.push_back({r, g, b});
   }

   col_ver.push_back({0,1,1}); // Color vértice inferior
   col_ver.push_back({1,0,0}); // Colo vértice superior
}

//Clase P2Rejilla

P2Rejilla::P2Rejilla(unsigned n, unsigned m)
: MallaInd( "rejilla ejercicio examen 2" )
{
   assert(n > 1 && m > 1);
   
   // Y siempre 0
   //Colores igual coordenadas (x,y,z)

   // Generar vértices
     
   for(unsigned j = 0; j < m; ++j){
      float index_j = 1.4/(m-1) * j;   // Max Z -> 1.4
      for(unsigned i = 0; i < n; ++i){
         float index_i = (1.0+index_j*2/1.4)/(n-1) * i;    // Max X -> En función de Z. Inicialmente 1  para z = 0. 3 para z = 1.4

         vertices.push_back({index_i, 0.0, index_j});
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

// Clase P3Cuadrado

P3Cuadrado::P3Cuadrado()
:  MallaInd( "cuadrado ejercicio 3 examen" )
{

   vertices =
      {  { -1.0, 0.0, -1.0 }, // 0
         { -1.0, 0.0, +1.0 }, // 1
         { +1.0, 0.0, -1.0 }, // 2
         { +1.0, 0.0, +1.0 }, // 3
      } ;

   triangulos =
      {  
         {0,1,3}, {0,3,2},
      } ;
}

// Clase P3Caja

P3Caja::P3Caja(){
   NodoGrafoEscena * caja = new NodoGrafoEscena();
   caja->agregar(glm::translate(glm::vec3(0.0, 0.0, 0.0) ));
   caja->agregar(new P3Cuadrado()); // Base Caja
   agregar(caja);

   // // Como ya tenemos el objeto compuesto que se va a repetir ,agregamos 4 caras de nuestro 
   // // objeto compuesto rotando cada objeto 90 grados sobre el eje X
   for(int i = 0; i < 4; i++){
      caja->agregar(rotate(float(glm::radians(-90.0)), glm::vec3{0.0, 0.0, 1.0}));
      agregar(caja);
   }

   NodoGrafoEscena * esfera = new NodoGrafoEscena();

   unsigned ind1 = esfera->agregar(glm::scale(glm::vec3( 1.0, 1.0, 1.0)));
   movimiento_esfera = esfera->leerPtrMatriz(ind1);

   esfera->agregar(glm::translate(glm::vec3(0.0, 0.3, 0.0)));
   esfera->agregar(glm::scale(glm::vec3(0.2, 0.2, 0.2)));
   esfera->agregar(new Esfera(30,30));
   
   agregar(esfera);
}

void P3Caja::abre_caja(const float alpha_nuevo){
   *abrir_caja = glm::rotate( alpha_nuevo, glm::vec3(1.0, 0, 0.0));
}

void P3Caja::elevar_esfera(const float alpha_nuevo){
   *movimiento_esfera = glm::translate( glm::vec3(0.0, alpha_nuevo, 0.0));
}


float P3Caja::calcula_oscilante_eleva_esfera(const float t_sec){
    // a = (vmax + vmin)/2
    // b = (vmin - vmax)/2
    // v = a + b*sin(2pint)

    float vmax = 2.0f;
    float vmin = 0.0f;
    float n = 1.0f;

    float a = (vmax + vmin)/2.0;
    float b = (vmin - vmax)/2.0;

    return a+b*(sin(2*M_PI*n*t_sec));
}

float P3Caja::calcula_oscilante_abre_caja(const float t_sec){
    // a = (vmax + vmin)/2
    // b = (vmin - vmax)/2
    // v = a + b*sin(2pint)

    float vmax = 90.0f;
    float vmin = 0.0f;
    float n = 1.0f;

    float a = (vmax + vmin)/2.0;
    float b = (vmin - vmax)/2.0;

    return a+b*(sin(2*M_PI*n*t_sec));
}



unsigned P3Caja::leerNumParametros() const{
    return 2;
} 


void P3Caja::actualizarEstadoParametro( const unsigned iParam, const float t_sec ){

   switch (iParam)
   {
      case 0: // Abrir Caja
         //abre_caja(calcula_oscilante_abre_caja(t_sec));
      case 1:  // Subir esfera
         elevar_esfera(calcula_oscilante_eleva_esfera(t_sec));
      default:
         break;
   }
}

