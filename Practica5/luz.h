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
 	
	void Activar   ();
	void desactivar();

 protected:
	GLenum id;					// ID de luz
	Tupla4f colorAmbiente ;	// Tupla con color para modo ambiental
	Tupla4f colorDifuso   ;	// Tupla con color para modo difuso
	Tupla4f colorEspecular;	// Tupla con color para modo especular
} ;


#endif
