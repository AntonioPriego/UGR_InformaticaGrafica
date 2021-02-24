// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: luzdireccional.h

//
// #############################################################################

#ifndef LUZDIRECCIONAL_H_INCLUDED
#define LUZDIRECCIONAL_H_INCLUDED

#include "aux.h"

// *****************************************************************************
//
// clase derivada de Luz: LuzDireccional
//
// *****************************************************************************


class LuzDireccional : public Luz
{
  public:
	LuzDireccional(Tupla4f _direccion      = Tupla4f(0,0,1,0),
                   GLenum  _id             = GL_LIGHT1       ,
                   Tupla4f _colorAmbiente  = Tupla4f(0.3,0.9,0.3,1),
                   Tupla4f _colorEspecular = Tupla4f(0.7,0.4,0.5,1),
                   Tupla4f _colorDifuso    = Tupla4f(0.7,0.5,0.2,1) );

   	void activar();
   	void variarAnguloAlpha(float incremente);
   	void variarAnguloBeta (float incremento);

  protected:
	Tupla4f direccion; // Tupla con la dirección de la luz (direccional)
  	float alpha;
  	float beta ;
};




#endif
