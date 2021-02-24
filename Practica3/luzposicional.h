// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: luzposicional.h

//
// #############################################################################

#ifndef LUZPOSICIONAL_H_INCLUDED
#define LUZPOSICIONAL_H_INCLUDED

#include "aux.h"
#include "luz.h"
#include "malla.h"
#include "objply.h"

// *****************************************************************************
//
// clase derivada de Luz: LuzPosicional
//
// *****************************************************************************


class LuzPosicional : public Luz
{
  public:
	LuzPosicional(Tupla4f _posicion       = Tupla4f(  0, 50, 80,1),
                  GLenum  _id             = GL_LIGHT0        ,
                  Tupla4f _colorAmbiente  = Tupla4f(0.9,0.1,0.3,1),
                  Tupla4f _colorEspecular = Tupla4f(0.9,0.1,0.3,1),
                  Tupla4f _colorDifuso    = Tupla4f(0.9,0.1,0.3,1) );
   void activar();

  protected:
  	ObjPLY *visual = nullptr;
	Tupla4f posicion      ;	// Tupla con posición física de luz (posicional)

};




#endif
