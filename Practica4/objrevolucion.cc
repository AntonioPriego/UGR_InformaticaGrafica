#include "aux.h"
#include "objrevolucion.h"
#include "ply_reader.h"



// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)


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

	generaColor();
}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int _num_instancias, bool Tsup, bool Tinf, Eje eje)
{
	ply::read_vertices( archivo, vPerfil );
	ply::read_vertices( archivo, v );

	ejeRotacion = eje;

	num_instancias = _num_instancias;

	if (eje==X) DetectaTapasX();
	if (eje==Y) DetectaTapasY();
	if (eje==Z) DetectaTapasZ();

	crearMalla(Tsup,Tinf);

	generaColor();
}

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
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos) 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int _num_instancias, bool Tsup, bool Tinf, Eje eje)
{
	vPerfil = archivo;
	v       = archivo;

	ejeRotacion = eje;

	num_instancias = _num_instancias;

	crearMalla(Tsup, Tinf);

	generaColor();
}

void ObjRevolucion::crearMalla(bool Tsup, bool Tinf)
{
	double angulo = (2*3.141592) / num_instancias;

	for (int i=0; i<num_instancias; i++) {
		std::vector<Tupla3f> perfsig(vPerfil.size());
		// Generamos los puntos rotados
		for (int k=0; k<vPerfil.size(); k++)
			perfsig[k] = Rota(vPerfil[k], angulo);

		// Añadimos los vertices al final del vector
		v.insert(v.end(), perfsig.begin(), perfsig.end() );


		//Generación de caras
		int iniPerfil, finPerfil;
		iniPerfil = i * vPerfil.size();
		finPerfil = iniPerfil + vPerfil.size();

		for (int i = iniPerfil+1, k = finPerfil+1; i < finPerfil; i++, k++) {
			f.push_back(Tupla3i(i-1, k-1, k));
			f.push_back(Tupla3i(i-1, k  , i));
		}

		vPerfil = perfsig;
	}

	numf = numfTapas = f.size();


	if (hayTapaSup && Tsup)
		CreaTapaSup();	//Solo crea las tapa superior si se ha detectado que existen en DetectaTapas() y se indica en Tsup
	if (hayTapaInf && Tinf)
		CreaTapaInf();	//Solo crea las tapa inferior si se ha detectado que existen en DetectaTapas() y se indica en Tinf
}


void ObjRevolucion::CreaTapaSup()
{	
    Tupla3f vTapaSup;	//Vértice de la tapa superior

	if (v[vPerfil.size() - 1][0]) {
		if      (ejeRotacion == ejeX) 
			vTapaSup = Tupla3f( v[vPerfil.size() - 1][0], 0.0, 0.0); // Vértice central (tapa superior)
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
			//CarasTapaSup.push_back(Tupla3i(v.size()-1, perfilactu, perfsig));
		}
	}
}

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
			//CarasTapaInf.push_back(Tupla3i(v.size()-1, perfsig, perfilactu));
		}
	}
}


// Metodo para rotar los puntos en función del eje de rotacion
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

/*
void ObjRevolucion::muestraTapas(bool sup, bool inf)
{
	EliminaTapas();

	if (hayTapaSup && sup) {
		for (int i=0; i<CarasTapaSup.size(); i++)
			f.push_back(CarasTapaSup[i]);

		tapaSupActiva=true;
	}


	if (hayTapaInf && inf) {
		for (int i=0; i<CarasTapaInf.size(); i++)
			f.push_back(CarasTapaInf[i]);

		tapaInfActiva=true;
	}

}

void ObjRevolucion::EliminaTapas()
{
	if (tapaSupActiva) {
		f.resize(f.size()-CarasTapaSup.size());
		tapaSupActiva=false;
	}

	if (tapaInfActiva) {
		f.resize(f.size()-CarasTapaInf.size());
		tapaInfActiva=false;
	}
}
*/

void ObjRevolucion::cambiaTapas()
{
	if (strideFinal!=0)	strideFinal = 0;				//No hay salto de caras
	else                strideFinal = numf-numfTapas;	//Salta las caras de las tapas
}

void ObjRevolucion::generaColor(Tupla3f color)
{
	c.resize(f.size());

	for (int i=0; i<f.size(); i++)
		c[i] = color;
}