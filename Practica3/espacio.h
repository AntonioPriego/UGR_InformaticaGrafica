#ifndef _ESPACIO
#define _ESPACIO


#include "aux.h"
#include "malla.h"

class Espacio : public Malla3D
{
 private:
	float axisSize;
	float risePoint;

 public:
	Espacio();
};
#endif
