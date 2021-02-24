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
	visual->setColor(Tupla3f(0.2,0.2,0.2));
	visual->setMaterial(Tupla4f(0.0, 1.0, 0.6, 1), Tupla4f(0.7, 0.3, 0.3, 1),
                        Tupla4f(0.7, 0.3, 0.3, 1), Tupla4f(0.0, 0.0, 0.6, 1), 0.1);
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

