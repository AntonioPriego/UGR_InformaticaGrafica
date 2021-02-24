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

// *****************************************************************************
//
// Clase Modelo Jerárquico
//
// *****************************************************************************
	
	static Material *mat_metal = new Material(Tupla4f(0.3, 0.3, 0.3, 1), Tupla4f(0.3, 0.3, 0.3, 1),
                              Tupla4f(0.2, 0.4, 0.3, 1), Tupla4f(0.3, 0.1, 0.3, 1), 0.8);

	static Material *mat_madera = new Material(Tupla4f(0.1, 0.1, 0.1, 1), Tupla4f(0.1, 0.1, 0.1, 1),
                              Tupla4f(0.1, 0.1, 0.1, 1), Tupla4f(0.1, 0.1, 0.1, 1), 0.4);

	static Material *mat_porcelana = new Material(Tupla4f(0.1, 0.1, 0.1, 1), Tupla4f(0.1, 0.1, 0.1, 1),
                                 Tupla4f(0.1, 0.1, 0.1, 1), Tupla4f(0.1, 0.1, 0.1, 1), 0.1);

class ParteFuncional
{
 public:
 	ParteFuncional(int tamCubo, int muestreoObjRev);
	void draw(bool dibujadoInmediato, tipoDibujado dibujado, tipoIluminacion iluminacion);
	void animar();
 	void masVelocidad();	// Más velocidad en animación de portafiltros
 	void menosVelocidad();	// Menos velocidad en animación de portafiltros

 protected:
 	Cubo          *cubo         = nullptr;
 	ObjRevolucion *cilindro_met = nullptr;
 	bool   ida=true;		// Indica si la animación está en ida o en vuelta
 	double anim_rotacion=0;	// Progreso en animación de rotación
 	double velocidad=0.0015;// Velocidad de la animación
};


class Portafiltros
{
 public:
 	Portafiltros(int muestreoObjRev);
	void draw(bool dibujadoInmediato, tipoDibujado dibujado, tipoIluminacion iluminacion);
	void animar();
 	void masVelocidad();	// Más velocidad en animación de portafiltros
 	void menosVelocidad();	// Menos velocidad en animación de portafiltros


 protected:
 	ObjRevolucion *cilindro_mad = nullptr;
 	ObjRevolucion *cilindro_met = nullptr;
 	bool   ida=true;			// Indica si la animación está en ida o en vuelta
 	double anim_traslacion_y=0;	// Progreso en animación de traslacion
 	double anim_traslacion_x=0;	// Progreso en animación de rotación
 	double anim_rotacion=0;		// Progreso en animación de rotación
 	double velocidad=0.0015;	// Velocidad de la animación
};


class Fondo
{
 public:
 	Fondo(int tamCubo);
	void draw(bool dibujadoInmediato, tipoDibujado dibujado, tipoIluminacion iluminacion);

 protected:
 	Cubo *cubo = nullptr;
};


class Base
{
 public:
 	Base(int tamCubo, int muestreoObjReva);
	void draw(bool dibujadoInmediato, tipoDibujado dibujado, tipoIluminacion iluminacion);
	void animar();
 	void masVelocidad();	// Más velocidad en animación de base
 	void menosVelocidad();	// Menos velocidad en animación de base


 protected:
	ObjPLY        *taza         = nullptr;
	Cubo          *cubo         = nullptr;
	ObjRevolucion *cilindro_mad = nullptr;
	ObjRevolucion *cilindro_met = nullptr;
 	bool   ida=true;			// Indica si la animación está en ida o en vuelta
 	double anim_rotacion=0;		// Progreso en animación de rotación
 	double velocidad=0.00015;	// Velocidad de la animación
};



class ModJerarquico
{
 protected:
	ParteFuncional *parteFuncional= nullptr ;
	Fondo          *fondo         = nullptr ;
	Portafiltros   *portafiltros  = nullptr ;
	Base           *base          = nullptr ;

 public:
 	// Parámetros necesarios para mantener coherencia con escena
 	ModJerarquico(int tamCubo, int muestreoObjRev); 
 
 	void draw(bool dibujadoInmediato, tipoDibujado dibujado, tipoIluminacion iluminacion, bool primerplano=false);
 	void animar(bool dibujadoInmediato, tipoDibujado dibujado, tipoIluminacion iluminacion, bool primerPlano=false, int gradoL=0);
 	void masVelocidad(int gradoL=0);	// Más velocidad en animación
 	void menosVelocidad(int gradoL=0);	// Menos velocidad en animación
};


#endif