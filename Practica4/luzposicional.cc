#include "aux.h"
#include "luzposicional.h"

LuzPosicional::LuzPosicional(Tupla4f _posicion       ,
                             GLenum  _id             ,
                             Tupla4f _colorAmbiente  ,
                             Tupla4f _colorEspecular ,
                             Tupla4f _colorDifuso     )
{
	posicion       = _posicion      ;
	id             = _id            ;
	colorAmbiente  = _colorAmbiente ;
	colorEspecular = _colorEspecular;
	colorDifuso    = _colorDifuso   ;

	visual = new ObjPLY("esfera");
}

void LuzPosicional::activar() 
{

	Activar();
	
	glLightfv(id, GL_POSITION, posicion);


	glPushMatrix();
		glTranslatef(posicion[0],posicion[1],posicion[2]);
		glScalef(0.04,0.04,0.04);
		visual->draw (true, SOLIDO);
	glPopMatrix();
}

