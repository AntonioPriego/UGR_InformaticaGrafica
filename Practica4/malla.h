// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"
#include "material.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

typedef enum {PUNTOS, LINEAS, SOLIDO, AJEDREZ} tipoDibujado;
typedef enum {DESACTIVADO, SUAVE, PLANA} tipoIluminacion;

class Malla3D
{
 public:

	// Crea VBO y le atribuye un identificador
	GLuint CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid *puntero_ram);

	// dibuja el objeto en modo inmediato
	void draw_ModoInmediato();

	// dibuja el objeto en modo diferido (usando VBOs)
	void draw_ModoDiferido();

	// Visualización en modo Ajedrez (inmediato)
	void draw_ModoAjedrez();

	// Visualización Iluminado
	void draw_Iluminado();

	// función que redibuja el objeto
	// está función llama a 'draw_ModoInmediato' (modo inmediato)
	// o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
	void draw(bool inmediato=true, tipoDibujado dibujado=SOLIDO,
                                   tipoIluminacion iluminacion=DESACTIVADO);

	// Establece color principal y secundario
	void setColor          (Tupla3f color =Tupla3f(0,0,0));
	void setColoresAjedrez (Tupla3f color1=Tupla3f(1,1,1),
                            Tupla3f color2=Tupla3f(0,0,0));
	void setMaterial (Material _m);
	void setMaterial (Tupla4f _emision  = Tupla4f(0.5,0.5,0.5,1),
                      Tupla4f _difuso   = Tupla4f(0.5,0.5,0.5,1),
                      Tupla4f _especular= Tupla4f(0.5,0.5,0.5,1),
                      Tupla4f _ambiente = Tupla4f(0.5,0.5,0.5,1),
                      float   _brillo   = 0.5 );


 protected:
	bool calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)

	Material m;
	std::vector<Tupla3f> v ;	// tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
	std::vector<Tupla3i> f ;	// una terna de 3 enteros por cada cara o triángulo
	std::vector<Tupla3f> c ;	// una terna de 3 enteros por cada color de vertice
	std::vector<Tupla3f> cA1;	// una terna de 3 enteros por cada color de vertice modoAjedrez (1)
	std::vector<Tupla3f> cA2;	// una terna de 3 enteros por cada color de vertice modoAjedrez (2)
	std::vector<Tupla3f> nv;	// vector de normales de vértices (tupla por normal) 
	std::vector<Tupla3f> nc;	// vector de normales de caras
	GLuint id_vbo_ver = 0 ;
	GLuint id_vbo_tri = 0 ;
	bool normales_calculadas=false; // Si se han calculado las normales (se ha dibujado al menos una vez)

							// para dibujado de tapas en objRevolucion
	int strideFinal = 0;	// 0 indica que se pinta todo el vector de caras
							// 1 indicaría que se pinta todo el vector de caras excepto la útlima
							// n indicaría que se pinta todo el vector de caras excepto las n útlimas

} ;


#endif
