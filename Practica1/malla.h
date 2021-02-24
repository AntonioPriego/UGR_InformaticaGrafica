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

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

typedef enum {PUNTOS, LINEAS, SOLIDO, AJEDREZ} tipoDibujado;

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
	void draw_ModoAjedrez(); 	// Función no operativa
								// Uso draw_inmediato implementando manualmente los colores

	// función que redibuja el objeto
	// está función llama a 'draw_ModoInmediato' (modo inmediato)
	// o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
	void draw(bool inmediato=true, tipoDibujado dibujado=SOLIDO) ;

	void setColorPuntos(/*parametros*/);	//
	void setColorLineas(/*parametros*/);	// Establece el color para cada modo 
	void setColorSolido(/*parametros*/);	//

	protected:

	void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)

	std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
	std::vector<Tupla3i> f ;   // una terna de 3 enteros por cada cara o triángulo
	std::vector<Tupla3f> c ;   // una terna de 3 enteros por cada color de vertice
	std::vector<Tupla3i> n ;   // tabla de coordenadas de normales (tupla por normal) 

	GLuint id_vbo_ver = 0 ;
	GLuint id_vbo_tri = 0 ;
} ;


#endif
