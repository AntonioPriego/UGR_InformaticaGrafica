#ifndef _ESCENA_H
#define _ESCENA_H

#include "espacio.h"
#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "objply.h"
#include "objrevolucion.h"
#include "luz.h"
#include "luzposicional.h"
#include "luzdireccional.h"
#include "material.h"

typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO} menu;


class Escena
{
 private:
	// ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)
	// variables que definen la posicion de la camara en coordenadas polares
	GLfloat Observer_distance;
	GLfloat Observer_angle_x;
	GLfloat Observer_angle_y;

	// variables que controlan la ventana y la transformacion de perspectiva
	GLfloat Width, Height, Front_plane, Back_plane;

	// Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();
	

	void clear_window();

	menu modoMenu=NADA;
	tipoDibujado dibujado=SOLIDO;
	bool dibujadoInmediato=true;

	 // Objetos de la escena
	Ejes ejes;
	Espacio   * espacio   = nullptr ;
	ObjPLY    * ply_obj   = nullptr ;
	ObjPLY    * barra_cafe= nullptr ;
	ObjPLY    * taburete  = nullptr ;
	Cubo      * cubo      = nullptr ; // es importante inicializarlo a 'nullptr'
	Tetraedro * tetraedro = nullptr ; // es importante inicializarlo a 'nullptr'
	ObjRevolucion *objrev = nullptr ;
	Material      *mat1   = nullptr ;

	tipoIluminacion iluminacion=DESACTIVADO;  // iluminacion activa
	 
	LuzPosicional  *luzPosi = nullptr;
	LuzDireccional *luzDire = nullptr;

	bool tapaSup=true ;      // tapa superior del ovjrev
	bool tapaInf=true ;      // tapa superior del ovjrev
	bool modoParalelo=false; // visualización simultánea de LINEAS, PUNTOS y SOLIDO

	int tamCubo=30;
	int tamTetr=60;

	int muestreoObjRev=36; // número de meridianos del ObjRevolucion

	int instanciasEnParalelo=0; // Número de instancias que hacen uso del dibujado en paralelo
								// sirve para espaciar los objetos que acceden a la función	 
 public:

	Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;
	void dibujarAtrezzo();

	void dibujadoParalelo(Malla3D *malla);

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

	// Mostrar en consola el proceso en ejecución
	void coutMenu(char *mensaje);

	// Funcion que devuelve la cadena de char del 'modoMenu'
	char* modoMenutoChar();

	// Muestra en terminal comandos disponibles
	void AyudaComandos();

	//Funcion debug para crear vector de vertices
	//Para probar constructor de objRevolucion
	std::vector<Tupla3f> debugVectorObjRev();
};
#endif
