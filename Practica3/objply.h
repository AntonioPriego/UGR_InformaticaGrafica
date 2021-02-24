// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: objply.h

//
// #############################################################################

#ifndef OBJPLY_H_INCLUDED
#define OBJPLY_H_INCLUDED

#include "aux.h"
#include "ply_reader.h"
#include "malla.h"

 

// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************
class ObjPLY: public Malla3D {
public:
	ObjPLY( const std::string & nombre_archivo ) ;
	void generaColor(Tupla3f color=Tupla3f(0.5,0.5,0.5)); 
};

#endif


