// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Luz.h
// -- declaraciones de clase Luz 
//
// #############################################################################

#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include "aux.h"

// *****************************************************************************
//
// clase para luces
//
// *****************************************************************************

class Luz
{
 public:
/*	Luz(Tupla2f _direccion      = Tupla2f(0,0)    ,
		GLenum  _id             = GL_LIGHT1       ,
        Tupla4f _colorAmbiente  = Tupla4f(0,0,0,1),
        Tupla4f _colorEspecular = Tupla4f(1,1,1,1),
        Tupla4f _colorDifuso    = Tupla4f(1,1,1,1)  );
*/
 	
	void Activar   ();
	void Desactivar();

 protected:
	GLenum id;				// ID de luz
	Tupla4f colorAmbiente ;	// Tupla con color para modo ambiental
	Tupla4f colorDifuso   ;	// Tupla con color para modo difuso
	Tupla4f colorEspecular;	// Tupla con color para modo especular
} ;


#endif
