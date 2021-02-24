#include "aux.h"

#ifndef _ESPACIO
#define _ESPACIO

class Espacio {

private:
	float axisSize;
	float risePoint;
	std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
	std::vector<Tupla3i> f ;   // una terna de 3 enteros por cada cara o triángulo
	std::vector<Tupla3f> c ;   // una terna de 3 enteros por cada color de vertice


public:
	Espacio();
	void draw();
	
};
#endif
