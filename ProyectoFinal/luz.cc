#include "aux.h"
#include "luz.h"

// *****************************************************************************
//
// Clase Luz
//
// *****************************************************************************

/*
Luz::Luz(GLenum _id, Tupla4f _colorAmbiente,
                     Tupla4f _colorEspecular,
                     Tupla4f _colorDifuso     )
{
	id             = _id;
	colorAmbiente  = _colorAmbiente ;
	colorEspecular = _colorEspecular;
	colorDifuso    = _colorDifuso   ;
}
*/

void Luz::Activar()
{
	glEnable(GL_LIGHTING);
	glEnable(id);

	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, colorAmbiente);
	glLightfv(id, GL_AMBIENT , colorAmbiente );
	glLightfv(id, GL_DIFFUSE , colorDifuso   );
	glLightfv(id, GL_SPECULAR, colorEspecular);

}

void Luz::desactivar()
{
	glDisable(id);
}