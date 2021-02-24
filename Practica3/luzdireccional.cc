#include "aux.h"
#include "luz.h"
#include "luzdireccional.h"

LuzDireccional::LuzDireccional(Tupla4f _direccion      ,
                               GLenum  _id             ,
                               Tupla4f _colorAmbiente  ,
                               Tupla4f _colorEspecular ,
                               Tupla4f _colorDifuso     )
{
	direccion      = _direccion     ;
	id             = _id            ;
	colorAmbiente  = _colorAmbiente ;
	colorEspecular = _colorEspecular;
	colorDifuso    = _colorDifuso   ;
}

void LuzDireccional::activar()
{
	Activar();

	glLightfv(id, GL_POSITION, direccion);
}

void LuzDireccional::variarAnguloAlpha(float incremento)
{
}

void LuzDireccional::variarAnguloBeta (float incremento)
{
}