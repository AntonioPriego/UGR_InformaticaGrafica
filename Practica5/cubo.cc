#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{
	v.resize (8) ;
	f.resize (12);
	c.resize (8) ;
	cA.resize(8) ;

	// inicializar la tabla de vértices
	v[0] = (Tupla3f( lado,  lado, lado));
	v[1] = (Tupla3f(-lado,  lado, lado));	//    v6----- v5
	v[2] = (Tupla3f(-lado, -lado, lado));	//   /|      /|
	v[3] = (Tupla3f( lado, -lado, lado));	//  v1------v0|
	v[4] = (Tupla3f( lado, -lado,-lado));	//  | |     | |
	v[5] = (Tupla3f( lado,  lado,-lado));	//  | |v7---|-|v4
	v[6] = (Tupla3f(-lado,  lado,-lado));	//  |/      |/
	v[7] = (Tupla3f(-lado, -lado,-lado));	//  v2------v3


	// inicializar la tabla de caras o triángulos:
	// (es importante en cada cara ordenar los vértices en sentido contrario
	//  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
	f[0]  = (Tupla3i(3,0,2)); //1	
	f[1]  = (Tupla3i(0,1,2)); //2	Frente	
	f[2]  = (Tupla3i(0,3,4)); //3
	f[3]  = (Tupla3i(5,0,4)); //4	Frente Dcha
	f[4]  = (Tupla3i(7,6,5)); //5
	f[5]  = (Tupla3i(4,7,5)); //6	Atras
	f[6]  = (Tupla3i(7,2,1)); //7
	f[7]  = (Tupla3i(6,7,1)); //8	Frente izda
	f[8]  = (Tupla3i(2,7,3)); //9
	f[9]  = (Tupla3i(7,4,3)); //10	Arriba
	f[10] = (Tupla3i(6,1,0)); //11
	f[11] = (Tupla3i(5,6,0)); //12	Abajo

	
	setColor(Tupla3f(0.1,0.1,0.5));
	setColoresAjedrez(Tupla3f(0,0,0), Tupla3f(1,1,1));
}

void Cubo::setMaterial(Material _m)
{
	m.set (_m);
}