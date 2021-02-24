#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro(float lado)
{
	v.resize(4);
	f.resize(4);
	c.resize(4);

	// inicializar la tabla de vértices
	v[0] = (Tupla3f(-lado/2 , -lado/2 , -lado/2));
	v[1] = (Tupla3f( 0      , -lado/2 ,  lado/2));
	v[2] = (Tupla3f( lado/2 , -lado/2 , -lado/2));
	v[3] = (Tupla3f( 0      ,  lado/2 ,  0     ));
		
	// inicializar la tabla de caras o triángulos:
	// (es importante en cada cara ordenar los vértices en sentido contrario
	//  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
	f[0] = (Tupla3i(0,1,3));
	f[1] = (Tupla3i(1,2,3));
	f[2] = (Tupla3i(2,0,3));
	f[3] = (Tupla3i(0,2,1));


	// inicializar la tabla de colores
	// cada vertice tiene un color
	c[0] = (Tupla3f(1,1,1));
	c[1] = (Tupla3f(0,0,0));
	c[2] = (Tupla3f(1,1,1));
	c[3] = (Tupla3f(1,1,1));


}
