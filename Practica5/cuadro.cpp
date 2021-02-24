#include "aux.h"
#include "malla.h"
#include "cuadro.h"

Cuadro::Cuadro(const std::string &archivo,
	           float ladox, float ladoy   )
{
	v.resize (4) ;
	f.resize (2) ;
	c.resize (4);
	cA.resize(4);
	ct.resize(4);

	// inicializar la tabla de vértices
	v[0] = (Tupla3f(-ladox, ladoy, 0));
	v[1] = (Tupla3f(-ladox,-ladoy, 0));
	v[2] = (Tupla3f( ladox,-ladoy, 0));
	v[3] = (Tupla3f( ladox, ladoy, 0));


	// inicializar la tabla de caras o triángulos:
	// (es importante en cada cara ordenar los vértices en sentido contrario
	//  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
	f[0] = (Tupla3i(0,1,2));	
	f[1] = (Tupla3i(2,3,0));	

	setColor(Tupla3f(0.5,0.5,0.5));
	setColoresAjedrez(Tupla3f(0,0,0), Tupla3f(1,1,1));

	
	setTextura(archivo);

	ct[0] = (Tupla2f(0.0,0.0));
	ct[1] = (Tupla2f(0.0,1.0));
	ct[2] = (Tupla2f(1.0,1.0));
	ct[3] = (Tupla2f(1.0,0.0));

	coordtex_calculadas=true;
}
