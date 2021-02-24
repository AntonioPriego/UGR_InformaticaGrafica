#ifndef _ESCENA_H
#define _ESCENA_H

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
#include "textura.h"
#include "modelo_jerarquico.h"
#include "cuadro.h"


typedef enum {NADA,SELOBJETO,SELVISUALIZACION,SELDIBUJADO,SELELUZ} menu;


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
	ObjPLY        * ply_obj   = nullptr ;
	ObjPLY        * barra_cafe= nullptr ;
	ObjPLY        * taburete  = nullptr ;
	ObjPLY        * taza      = nullptr ;
	ObjPLY        * pared     = nullptr ;
	ObjPLY        * techo     = nullptr ;
	ObjPLY        * suelo     = nullptr ;
	ObjPLY        * mesa1     = nullptr ;
	ObjPLY        * mesa2     = nullptr ;
	ObjPLY        * silla     = nullptr ;
	Cuadro        * ventana1  = nullptr ;
	Cuadro        * ventana2  = nullptr ;
	Cuadro        * puerta    = nullptr ;
	Cubo          * cubo      = nullptr ; 
	Tetraedro     * tetraedro = nullptr ; 
	ObjRevolucion * objrev    = nullptr ;
	ObjRevolucion * lata      = nullptr ;
	ModJerarquico * mod_jer   = nullptr ;
	Material      * mat1      = nullptr ;
	Material      * mat2      = nullptr ;
	Material      * mat3      = nullptr ;

	tipoIluminacion iluminacion = DESACTIVADO;  // iluminacion activa
	 
	LuzPosicional  *luzPosi1= nullptr;
	LuzPosicional  *luzPosi2= nullptr;
	LuzDireccional *luzDire = nullptr;
	// Aunque el bool este a true, necesitamos que 'iluminacion'!=DESACTIVADO
	bool luz0=true;	// Luz 0 encendida:true - apagada:false
	bool luz1=true;	// Luz 1 encendida:true - apagada:false
	bool luz2=true;	// Luz 2 encendida:true - apagada:false

	bool modjerPlano=false;  // el modelo jerarquico está en primer plano
	bool tapaSup=true ;      // tapa superior del ovjrev
	bool tapaInf=true ;      // tapa superior del ovjrev
	bool modoParalelo=false; // visualización simultánea de LINEAS, PUNTOS y SOLIDO

	int tamCubo=30;
	int tamTetr=60;

	int muestreoObjRev=36; // número de meridianos del ObjRevolucion

	int instanciasEnParalelo=0; // Número de instancias que hacen uso del dibujado en paralelo
								// sirve para espaciar los objetos que acceden a la función	 

	int gradoL=0;	// Elemento del ModJerarquico señalado (0:todos)
	int animAuto=1;	// 1:La animación no es automática
					// 2:La animación es automática
 public:

	Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;
	void dibujarAtrezzo();
	void dibujarParedes();

	void dibujadoParalelo(Malla3D *malla);

	void animarModeloJerarquico();

	// Interacción con la escena
	int teclaPulsada( unsigned char Tecla1, int x, int y ) ;
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
