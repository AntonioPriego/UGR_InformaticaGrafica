// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cuadro.h

//
// #############################################################################

#ifndef CUADRO_H_INCLUDED
#define CUADRO_H_INCLUDED

#include "aux.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

class Cuadro : public Malla3D
{
   public:
   Cuadro(const std::string &archivo="ventana1",
   	      float lx=49.92, float ly=28.08         ) ;
};

#endif
