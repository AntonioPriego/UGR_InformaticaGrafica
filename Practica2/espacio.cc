

#include "aux.h"
#include "espacio.h"

// -----------------------------------------------------------------------------

Espacio::Espacio()
{
    axisSize  = 120;
    risePoint = -30 ; 

    v.resize(8);
    f.resize(6);
    c.resize(1);

   	// inicializar la tabla de vértices
	v[0] = (Tupla3f( axisSize, risePoint, axisSize));
	v[1] = (Tupla3f(-axisSize, risePoint, axisSize));
	v[2] = (Tupla3f(-axisSize, risePoint,-axisSize));
	v[3] = (Tupla3f( axisSize, risePoint,-axisSize));		//suelo

	v[4] = (Tupla3f( axisSize, risePoint, axisSize/2));
	v[5] = (Tupla3f(-axisSize, risePoint, axisSize/2));		//paredes laterales

	v[6] = (Tupla3f(-axisSize, -1.8*risePoint,-axisSize));
	v[7] = (Tupla3f( axisSize, -1.8*risePoint,-axisSize));	//pared trasera

	// inicializar la tabla de caras
	f[0] = Tupla3i(2,1,0);
	f[1] = Tupla3i(3,2,0);
	f[2] = Tupla3i(2,6,5);
	f[3] = Tupla3i(7,3,4);
	f[4] = Tupla3i(7,2,3);
	f[5] = Tupla3i(7,6,2);


   	// inicializar la tabla de colores
   		// solo utilziaremos el vertice 0 (GL_FLAT)
	c[0] = (Tupla3f( 0.4, 0.4, 0.4));

}

// -----------------------------------------------------------------------------

void Espacio::draw()	//Comentarios activan uso de color
{
	glPolygonMode(GL_FRONT, GL_FILL);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, v.data());
	//glEnableClientState(GL_COLOR_ARRAY);
	//glColorPointer (3, GL_FLOAT, 0, c.data());
	glShadeModel(GL_FLAT);
	for (int i=0; i<f.size(); i++)
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, f[i]);
	//glDisableClientState(GL_COLOR_ARRAY);
	glShadeModel(GL_SMOOTH);
}
