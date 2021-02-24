// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: modelo_jerarquico.h

//
// #############################################################################

#ifndef MODELO_JERARQUICO_H
#define MODELO_JERARQUICO_H

#include "aux.h"
#include "malla.h"
#include "cubo.h"
#include "objply.h"
#include "objrevolucion.h"
#include "luzposicional.h"
#include "luzdireccional.h"
#include "material.h"
#include "modelo_jerarquico.h"

// *****************************************************************************
//
// clase derivada de Luz: LuzPosicional
//
// *****************************************************************************

class ModJerarquico
{
 protected:
	ObjPLY        * taza          = nullptr ;
	Cubo          * cubo          = nullptr ; 
	ObjRevolucion * cilindro_mad  = nullptr ;
	ObjRevolucion * cilindro_met  = nullptr ;
	Material      * mat_madera    = nullptr ;
	Material      * mat_metal     = nullptr ;
	Material      * mat_porcelana = nullptr ;

	void 

 public:
 	// Parámetros necesarios para mantener coherencia con escena
 	ModJerarquico(int tamCubo,int tamTetr,int muestreoObjRev); 
 
 	void draw(bool inmediato, tipoDibujado dibujado, tipoIluminacion iluminacion);
};


class ParteFuncional
{

}

class Fondo 
{

}

class Portafiltros
{

}

class Base
{
	
}

#endif