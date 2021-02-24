// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: material.h
// -- declaraciones de clase Material
//
// #############################################################################

#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include "aux.h"

class Material {
 private:
 	Tupla4f emision;
	Tupla4f difuso;
	Tupla4f especular;
	Tupla4f ambiente;
	float brillo;

 public:
	Material (Tupla4f _emision  = Tupla4f(0.5,0.5,0.5,1),
              Tupla4f _difuso   = Tupla4f(0.5,0.5,0.5,1),
              Tupla4f _especular= Tupla4f(0.5,0.5,0.5,1),
              Tupla4f _ambiente = Tupla4f(0.5,0.5,0.5,1),
              float   _brillo   = 0.5 );
	void aplicar();

	Tupla4f getEmision  ();
	Tupla4f getDifuso   ();
	Tupla4f getEspecular();
	Tupla4f getAmbiente ();
	float   getBrillo   ();

	void setEmision  (Tupla4f _emision)  ;
	void setDifuso   (Tupla4f _difuso)   ;
	void setEspecular(Tupla4f _especular);
	void setAmbiente (Tupla4f _ambiente) ;
	void setBrillo   (float   _brillo)   ;
	void set (Material _m);
	void set (Tupla4f _emision, Tupla4f _difuso,
              Tupla4f _especular, Tupla4f _ambiente,float _brillo);
};


#endif
