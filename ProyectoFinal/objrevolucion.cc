#include "aux.h"
#include "objrevolucion.h"
#include <cstring>
#include "ply_reader.h"



// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************

// Para constructor por defecto, he optado por utilizar:
//	-La figura peon
//	-Con 36 meridianos
//	-Ambas caras
ObjRevolucion::ObjRevolucion()
{
	ply::read_vertices( "peon", vPerfil );
	ply::read_vertices( "peon", v );

	num_instancias = 36;

	crearMalla();

	setColor();
	setMaterial();
}

// *****************************************************************************
// Constructor de ObjRevolucion obtenido a partir de un perfil (archivo de puntos)
ObjRevolucion::ObjRevolucion(const std::string &archivo, int _num_instancias, bool Tsup, bool Tinf, Eje eje)
{
	ply::read_vertices( archivo, vPerfil );
	ply::read_vertices( archivo, v );

	ejeRotacion = eje;

	num_instancias = _num_instancias;

	DetectaOrden();

	if (eje==X) DetectaTapasX();
	if (eje==Y) DetectaTapasY();
	if (eje==Z) DetectaTapasZ();

/*
	//Eliminamos el último vértice, ya que no lo queremos (parametro constructor)
	if (!Tinf && hayTapaInf) {
		vPerfil.erase(vPerfil.end());
		v.erase(v.end());
	}
	//Adelanta vertice de tapa superior, ya que no la queremos (parametro constructor)
	if (!Tsup && hayTapaSup) {
		vPerfil.erase(vPerfil.begin());
		v.erase(v.begin());
	}
*/

	crearMalla(Tsup,Tinf);
	setColor();
	setMaterial();
}

// *****************************************************************************
// Constructor de ObjRevolucion obtenido a partir de un perfil (en un vector de puntos)
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int _num_instancias, bool Tsup, bool Tinf, Eje eje)
{
	vPerfil = archivo;
	v       = archivo;

	ejeRotacion = eje;

	num_instancias = _num_instancias;

	DetectaOrden();

	if (eje==X) DetectaTapasX();
	if (eje==Y) DetectaTapasY();
	if (eje==Z) DetectaTapasZ();


	crearMalla(Tsup,Tinf);
	setColor();
	setMaterial();
}

// *****************************************************************************
// Detecta si hay tapas para ejeX
void ObjRevolucion::DetectaTapasX()
{
	int pos_superior = 0,
	    pos_inferior = 0;

	// Barrido para buscar el punto más alto y bajo
	for (int i=1; i<vPerfil.size(); i++) {
		if (vPerfil[i][0]>pos_superior) pos_superior=vPerfil[i][0];
		if (vPerfil[i][0]<pos_inferior) pos_inferior=vPerfil[i][0];
	}

	if (vPerfil[pos_superior][1] == 0  &&  vPerfil[pos_superior][2] == 0)
		hayTapaSup=true;

	if (vPerfil[pos_inferior][1] == 0  &&  vPerfil[pos_inferior][2] == 0)
		hayTapaInf=true;
}

// *****************************************************************************
// Detecta si hay tapas para ejeY
void ObjRevolucion::DetectaTapasY()
{
	int pos_superior=0,
	    pos_inferior=0;

	// Barrido para buscar el punto más alto y bajo
	for (int i=1; i<vPerfil.size(); i++) {
		if (vPerfil[i][1]>pos_superior) pos_superior=vPerfil[i][1];
		if (vPerfil[i][1]<pos_inferior) pos_inferior=vPerfil[i][1];
	}

	if (vPerfil[pos_superior][0] == 0  &&  vPerfil[pos_superior][2] == 0)
		hayTapaSup=true;

	if (vPerfil[pos_inferior][0] == 0  &&  vPerfil[pos_inferior][2] == 0)
		hayTapaInf=true;
}

// *****************************************************************************
// Detecta si hay tapas para ejeZ
void ObjRevolucion::DetectaTapasZ()
{
	int pos_superior=0,
	    pos_inferior=0;

	// Barrido para buscar el punto más alto y bajo
	for (int i=1; i<vPerfil.size(); i++) {
		if (vPerfil[i][2]>pos_superior) pos_superior=vPerfil[i][2];
		if (vPerfil[i][2]<pos_inferior) pos_inferior=vPerfil[i][2];
	}

	if (vPerfil[pos_superior][0] == 0  &&  vPerfil[pos_superior][1] == 0)
		hayTapaSup=true;

	if (vPerfil[pos_inferior][0] == 0  &&  vPerfil[pos_inferior][1] == 0)
		hayTapaInf=true;
}

// *****************************************************************************
// Detecta el orden de la topología. 
// En caso de orden ascendente (contrario al programado), llama a OrientarOrden de su eje
void ObjRevolucion::DetectaOrden()
{
	if      (ejeRotacion==ejeX) {
		if (vPerfil[0][0] > vPerfil[1][0]) OrientarOrden();
	}
	else if (ejeRotacion==ejeY) {
		if (vPerfil[0][1] > vPerfil[1][1]) OrientarOrden();
	}
	else if (ejeRotacion==ejeZ) {
		if (vPerfil[0][2] > vPerfil[1][2]) OrientarOrden();
	}
}

// *****************************************************************************
// Cambia el orden de la topología a ascendente (Como se implementa en crearMalla)
void ObjRevolucion::OrientarOrden()
{
	int cota_fin = vPerfil.size()-1;

	for (int cota_ini=0 ; cota_ini<cota_fin; cota_ini++,cota_fin--) {
		Tupla3f tmp = vPerfil[cota_ini];

		vPerfil[cota_ini] = vPerfil[cota_fin];
		v[cota_ini]       = vPerfil[cota_fin];
		vPerfil[cota_fin] = tmp;
		v[cota_fin]       = tmp;
	}
}


// *****************************************************************************
// Crea la malla. Revoluciona el perfil.
void ObjRevolucion::crearMalla(bool Tsup, bool Tinf)
{
	double angulo = (2*PI) / num_instancias;


	for (int i=0; i<num_instancias; i++) {
		std::vector<Tupla3f> perfsig(vPerfil.size());
		// Generamos los puntos rotados
		for (int k=0; k<vPerfil.size(); k++) 
			perfsig[k] = Rota(vPerfil[k], angulo);

		// Añadimos los vertices al final del vector
		v.insert( v.end(), perfsig.begin(), perfsig.end() );


		//Generación de caras
		int iniPerfil, finPerfil;
		iniPerfil = i * vPerfil.size();
		finPerfil = iniPerfil + vPerfil.size();

		for (int i=iniPerfil+1, k=finPerfil+1; i<finPerfil; i++, k++) {
			f.push_back(Tupla3i(i-1, k-1, k));
			f.push_back(Tupla3i(i-1, k  , i));
		}

		vPerfil = perfsig;
	}

	numf = numfsinTapas = f.size();


	if (hayTapaSup && Tsup)
		CreaTapaSup();	//Solo crea las tapa superior si se ha detectado que existen en DetectaTapas() y se indica en Tsup
	if (hayTapaInf && Tinf)
		CreaTapaInf();	//Solo crea las tapa inferior si se ha detectado que existen en DetectaTapas() y se indica en Tinf
}

// *****************************************************************************
// Crea la tapa superior (eje correspondiente)
void ObjRevolucion::CreaTapaSup()
{
    Tupla3f vTapaSup;	//Vértice de la tapa superior

	if (v[vPerfil.size()-1][0]) {
		if      (ejeRotacion == ejeX) 
			vTapaSup = Tupla3f( v[vPerfil.size() - 1][0], 0.0, 0.0);// Vértice central (tapa superior)
		else if (ejeRotacion == ejeY) 
			vTapaSup = Tupla3f(0.0, v[vPerfil.size() - 1][1], 0.0); // Vértice central (tapa superior)
		else if (ejeRotacion == ejeZ) 
			vTapaSup = Tupla3f(0.0, 0.0, v[vPerfil.size() - 1][2]); // Vértice central (tapa superior)
	
		v.push_back(vTapaSup);


		int perfilactu, perfsig;

		for (int i=0; i<num_instancias; i++, numf++) {
			perfilactu = (i+1) * vPerfil.size() -1;
			perfsig    = perfilactu + vPerfil.size();
			f.push_back(Tupla3i(v.size()-1, perfilactu, perfsig));
		}
	}
}


// *****************************************************************************
// Crea la tapa inferior (eje correspondiente)
void ObjRevolucion::CreaTapaInf()
{
	Tupla3f vTapaInf;	//Vértice de la tapa inferior

	if (v.data()[0]) {
		if      (ejeRotacion == ejeX) 
			vTapaInf = Tupla3f(v.data()[0][0], 0.0, 0.0); // Vertice central (tapa inferior)
		else if (ejeRotacion == ejeY) 
			vTapaInf = Tupla3f(0.0, v.data()[0][1], 0.0); // Vertice central (tapa inferior)
		else if (ejeRotacion == ejeZ) 
			vTapaInf = Tupla3f(0.0, 0.0, v.data()[0][2]); // Vertice central (tapa inferior)
		
		v.push_back(vTapaInf);


		int perfilactu, perfsig;
		
		for (int i=0; i<num_instancias; i++, numf++) {
			perfilactu = i * vPerfil.size();
			perfsig    = perfilactu + vPerfil.size();
			f.push_back(Tupla3i(v.size()-1, perfsig, perfilactu));
		}
	}
}


// *****************************************************************************
// Método para rotar los puntos en función del eje de rotacion
Tupla3f ObjRevolucion::Rota(Tupla3f a_rotar, float alfa)
{
	Tupla3f puntoRotado;


	if      (ejeRotacion == X) {
		puntoRotado[0] = a_rotar[0];
		puntoRotado[1] = cos(alfa)  * a_rotar[1]-sin(alfa) * a_rotar[2];                
		puntoRotado[2] = sin(alfa)  * a_rotar[1]+cos(alfa) * a_rotar[2];
	}
	else if (ejeRotacion == Y) {
		puntoRotado[0] = cos(alfa)  * a_rotar[0] + sin(alfa) * a_rotar[2]; //x
		puntoRotado[1] = a_rotar[1];									   //y
		puntoRotado[2] = -sin(alfa) * a_rotar[0] + cos(alfa) * a_rotar[2]; //z
	}
	else if (ejeRotacion == Z) {
		puntoRotado[0] = cos(alfa) * a_rotar[0]-sin(alfa) * a_rotar[1];
		puntoRotado[1] = sin(alfa) * a_rotar[0]+cos(alfa) * a_rotar[1];
		puntoRotado[2] = a_rotar[2];
	}

	return puntoRotado;
}


// *****************************************************************************
// Establece strideFinal para que draw lea las tapas(si existen) o no lo haga
void ObjRevolucion::cambiaTapas()
{
	if (strideFinal!=0)	strideFinal = 0;				//No hay salto de caras
	else                strideFinal = numf-numfsinTapas;//Salta las caras de las tapas
}

