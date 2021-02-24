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

	crearMalla(true, true);
}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int _num_instancias, bool tapa_sup, bool tapa_inf, Eje eje)
{
	ply::read_vertices( archivo, vPerfil );
	ply::read_vertices( archivo, v );

	ejeRotacion = eje;

	num_instancias = _num_instancias;

	crearMalla(tapa_sup, tapa_inf);
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int _num_instancias, bool tapa_sup, bool tapa_inf, Eje eje)
{
	vPerfil = archivo;
	v       = archivo;

	ejeRotacion = eje;

	num_instancias = _num_instancias;

	crearMalla(tapa_sup, tapa_inf);
}

//void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias)
	// yo he implementado perfil_original como la primera instancia de vertices de la propia malla
void ObjRevolucion::crearMalla(bool tapa_sup, bool tapa_inf)
{
	double angulo = (2*3.141592) / num_instancias;

	for (int i=0; i<num_instancias; i++) {
		std::vector<Tupla3f> perfsig(vPerfil.size());
		// Generamos los puntos rodaso
		for (unsigned int k=0; k<vPerfil.size(); k++)
			perfsig[k] = Rota(vPerfil[k], angulo);

		// Añadimos los vertices al final del vector
		v.insert(v.end(), perfsig.begin(), perfsig.end() );


		//Generación de caras
		unsigned int iniPerfil, finPerfil;
		iniPerfil = i * vPerfil.size();
		finPerfil = iniPerfil + vPerfil.size();

		for (unsigned int i = iniPerfil+1, k = finPerfil+1; i < finPerfil; i++, k++) {
			f.push_back(Tupla3i(i-1, k-1, k));
			f.push_back(Tupla3i(i-1, k,   i));
		}

		vPerfil = perfsig;
	}

	numf = f.size();
	numv = v.size();

	//Creación de tapas si así se especifica en los bools
	if (tapa_sup) CreaTapaSup();
	if (tapa_inf) CreaTapaInf();

}


void ObjRevolucion::CreaTapaSup()
{
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
			fTapaSup.push_back(Tupla3i(v.size()-1, perfilactu, perfsig));
		}
	}
}

void ObjRevolucion::CreaTapaInf()
{
	if (v.front()[0]) {
		if      (ejeRotacion == ejeX) 
			vTapaInf = Tupla3f(v.front()[0], 0.0, 0.0); // Vertice central (tapa inferior)
		else if (ejeRotacion == ejeY) 
			vTapaInf = Tupla3f(0.0, v.front()[1], 0.0); // Vertice central (tapa inferior)
		else if (ejeRotacion == ejeZ) 
			vTapaInf = Tupla3f(0.0, 0.0, v.front()[2]); // Vertice central (tapa inferior)
		
		v.push_back(vTapaInf);


		int perfilactu, perfsig;
		
		for (int i=0; i<num_instancias; i++, numf++) {
			perfilactu = i * vPerfil.size();
			perfsig    = perfilactu + vPerfil.size();
			f.push_back(Tupla3i(v.size()-1, perfsig, perfilactu));
			fTapaInf.push_back(Tupla3i(v.size()-1, perfsig, perfilactu));
		}
	}
}

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


/////////////////////////////// cambiaTapas /////////////////////////////////////
// Mi solución para poder usar ambas tapas, alguna de ellas o ninguna,
// ha sido almacenar como atributo los valores de las tapas, y usarlos
// solo si así se indica.
// En caso de que no se use, tamaré como valores
// de las caras que deberían formar la tapa, la cara justamente anterior
// al inicio de las caras de la tapa. De esta forma, no modifico la estructura
// del vector de caras. Es una forma poco ortodoxa, pero efectiva

void ObjRevolucion::cambiaTapas(bool tapa_sup, bool tapa_inf)
{

////////////////////////////////////// RESET DE TAPAS
	f.resize(numf-2*num_instancias);			//Eliminamos todo registro anterior de las tapas


////////////////////////////////////// TAPA SUPERIOR
	if (tapa_sup)								// Introducimos las caras de la tapa
		for (int i=0; i<num_instancias; i++)
			f.push_back(fTapaSup[i]);
	else 										// Introducimos reiterativamente
		for (int i=0; i<num_instancias; i++)	// la última cara anterior a la tapa, para no mostrar la tapa
			f.push_back(f[i-1]);
	
////////////////////////////////////// TAPA INFERIOR
	if (tapa_inf)								// Introducimos las caras de la tapa
		for (int i=0; i<num_instancias; i++)
			f.push_back(fTapaInf[i]);
	else 										// Introducimos reiterativamente
		for (int i=0; i<num_instancias; i++)	// la última cara anterior a la tapa, para no mostrar la tapa
			f.push_back(f[i-1]);

}